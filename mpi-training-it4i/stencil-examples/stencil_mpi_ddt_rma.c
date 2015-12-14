/*
 * Copyright (c) 2012 Torsten Hoefler. All rights reserved.
 *
 * Author(s): Torsten Hoefler <htor@illinois.edu>
 *
 */

#include "stencil_par.h"

void setup(int rank, int proc, int argc, char **argv,
           int *n_ptr, int *energy_ptr, int *niters_ptr, int *px_ptr, int *py_ptr,
           int *final_flag);

void init_sources(int bx, int by, int offx, int offy, int n,
                  const int nsources, int sources[][2],
                  int *locnsources_ptr, int locsources[][2]);

void update_grid(int bx, int by, double *aold, double *anew, double *heat_ptr);

int main(int argc, char **argv)
{
    int r,p;
    int n, energy, niters, px, py;

    int rx, ry;
    int north, south, west, east;
    int bx, by, offx, offy;

    /* three heat sources */
    const int nsources = 3;
    int sources[nsources][2];
    int locnsources;             /* number of sources in my area */
    int locsources[nsources][2]; /* sources local to my rank */

    double t1, t2;

    int iter, i, j;

    double *aold, *anew, *tmp;

    double heat, rheat;

    int final_flag;

    int win_size;     /* window size */
    double *win_mem;  /* window memory */
    MPI_Win win;      /* RMA window */

    MPI_Datatype north_south_type, east_west_type;

    /* initialize MPI envrionment */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    /* argument checking and setting */
    setup(r, p, argc, argv,
          &n, &energy, &niters, &px, &py, &final_flag);

    if (final_flag == 1) {
        MPI_Finalize();
        exit(0);
    }

    /* determine my coordinates (x,y) -- r=x*a+y in the 2d processor array */
    rx = r % px;
    ry = r / px;

    /* determine my four neighbors */
    north = (ry - 1) * px + rx; if (ry-1 < 0)   north = MPI_PROC_NULL;
    south = (ry + 1) * px + rx; if (ry+1 >= py) south = MPI_PROC_NULL;
    west = ry * px + rx - 1;    if (rx-1 < 0)   west = MPI_PROC_NULL;
    east = ry * px + rx + 1;    if (rx+1 >= px) east = MPI_PROC_NULL;

    /* decompose the domain */
    bx = n / px;    /* block size in x */
    by = n / py;    /* block size in y */
    offx = rx * bx; /* offset in x */
    offy = ry * by; /* offset in y */

    /* printf("%i (%i,%i) - w: %i, e: %i, n: %i, s: %i\n", r, ry,rx,west,east,north,south); */

    /* allocate RMA window */
    win_size = (bx + 2) * (by + 2);/* process-local grid (including halos (thus +2))*/

    /* allocate working arrays */
    MPI_Alloc_mem(2*win_size*sizeof(double), MPI_INFO_NULL, &win_mem);
    memset(win_mem, 0, 2*win_size*sizeof(double));

    /* create RMA window upon working array */
    MPI_Win_create(win_mem, 2*win_size*sizeof(double), sizeof(double), MPI_INFO_NULL,
                   MPI_COMM_WORLD, &win);
    /* MPI_Win_allocate(2*win_size*sizeof(double), sizeof(double), MPI_INFO_NULL,
                        MPI_COMM_WORLD, &win_mem, &win); */

    anew = win_mem;               /* each rank's offset */
    aold = win_mem + win_size;    /* second half is aold! */

    /* initialize three heat sources */
    init_sources(bx, by, offx, offy, n,
                 nsources, sources, &locnsources, locsources);

    /* create north-south datatype */
    MPI_Type_contiguous(bx, MPI_DOUBLE, &north_south_type);
    MPI_Type_commit(&north_south_type);

    /* create east-west datatype */
    MPI_Type_vector(by, 1, bx+2, MPI_DOUBLE, &east_west_type);
    MPI_Type_commit(&east_west_type);
    
    t1 = MPI_Wtime(); /* take time */

    for (iter = 0; iter < niters; ++iter) {

        int offset;

        /* refresh heat sources */
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, r, 0, win); /* lock myself for local load/store */
        for (i = 0; i < locnsources; ++i) {
            aold[ind(locsources[i][0],locsources[i][1])] += energy; /* heat source */
        }
        MPI_Win_unlock(r, win);

        /* exchange data with neighbors */
        MPI_Win_fence(MPI_MODE_NOPRECEDE, win);

        offset = win_size * ((iter + 1) % 2);

        MPI_Put(&aold[ind(1,1)], 1, north_south_type, north,
                ind(1,by+1)+offset, 1, north_south_type, win);

        MPI_Put(&aold[ind(1,by)], 1, north_south_type, south,
                ind(1,0)+offset, 1, north_south_type, win);

        MPI_Put(&aold[ind(bx,1)], 1, east_west_type, east,
                ind(0,1)+offset, 1, east_west_type, win);

        MPI_Put(&aold[ind(1,1)], 1, east_west_type, west,
                ind(bx+1,1)+offset, 1, east_west_type, win);

        MPI_Win_fence(MPI_MODE_NOSUCCEED, win);

        /* update grid points */
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, r, 0, win); /* lock myself for local load/store*/
        update_grid(bx, by, aold, anew, &heat);
        MPI_Win_unlock(r, win);

        /* swap working arrays */
        tmp = anew; anew = aold; aold = tmp;

        /* optional - print image */
        if (iter == niters-1) {
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, r, 0, win); /* lock myself for local load/store*/
            printarr_par(iter, anew, n, px, py, rx, ry,
                         bx, by, offx, offy, MPI_COMM_WORLD);
            MPI_Win_unlock(r, win);
        }
    }

    t2 = MPI_Wtime();

    /* get final heat in the system */
    MPI_Allreduce(&heat, &rheat, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    if (!r) printf("[%i] last heat: %f time: %f\n", r, rheat, t2-t1);

    MPI_Type_free(&east_west_type);
    MPI_Type_free(&north_south_type);
    MPI_Win_free(&win);
    MPI_Free_mem(win_mem);

    MPI_Finalize();
}

void setup(int rank, int proc, int argc, char **argv,
           int *n_ptr, int *energy_ptr, int *niters_ptr, int *px_ptr, int *py_ptr,
           int *final_flag)
{
    int n, energy, niters, px, py;

    (*final_flag) = 0;

    if (argc < 6) {
        if (!rank)
            printf("usage: stencil_mpi <n> <energy> <niters> <px> <py>\n");
        (*final_flag) = 1;
        return;
    }

    n = atoi(argv[1]);      /* nxn grid */
    energy = atoi(argv[2]); /* energy to be injected per iteration */
    niters = atoi(argv[3]); /* number of iterations */
    px = atoi(argv[4]);     /* 1st dim processes */
    py = atoi(argv[5]);     /* 2nd dim processes */

    if (px * py != proc)
        MPI_Abort(MPI_COMM_WORLD, 1);  /* abort if px or py are wrong */
    if (n % py != 0)
        MPI_Abort(MPI_COMM_WORLD, 2);  /* abort px needs to divide n */
    if (n % px != 0)
        MPI_Abort(MPI_COMM_WORLD, 3);  /* abort py needs to divide n */

    (*n_ptr) = n;
    (*energy_ptr) = energy;
    (*niters_ptr) = niters;
    (*px_ptr) = px;
    (*py_ptr) = py;
}

void init_sources(int bx, int by, int offx, int offy, int n,
                  const int nsources, int sources[][2],
                  int *locnsources_ptr, int locsources[][2])
{
    int i, locnsources = 0;

    sources[0][0] = n / 2;
    sources[0][1] = n / 2;
    sources[1][0] = n / 3;
    sources[1][1] = n / 3;
    sources[2][0] = n * 4 / 5;
    sources[2][1] = n * 8 / 9;

    for (i = 0; i < nsources; ++i) { /* determine which sources are in my patch */
        int locx = sources[i][0] - offx;
        int locy = sources[i][1] - offy;
        if (locx >= 0 && locx < bx && locy >= 0 && locy < by) {
            locsources[locnsources][0] = locx+1; /* offset by halo zone */
            locsources[locnsources][1] = locy+1; /* offset by halo zone */
            locnsources++;
        }
    }

    (*locnsources_ptr) = locnsources;
}

void update_grid(int bx, int by, double *aold, double *anew, double *heat_ptr)
{
    int i, j;
    double heat = 0.0;

    for (i = 1; i < bx+1; ++i) {
        for (j = 1; j < by+1; ++j) {
            anew[ind(i,j)] = anew[ind(i,j)]/2.0 + (aold[ind(i-1,j)] + aold[ind(i+1,j)] + aold[ind(i,j-1)] + aold[ind(i,j+1)])/4.0/2.0;
            heat += anew[ind(i,j)];
        }
    }

    (*heat_ptr) = heat;
}