MPICXX=mpicxx
MPICC=mpicc
OBJS=printarr_par.o
CFLAGS= -g
BINS=stencil_mpi_nonblocking stencil_mpi_ddt_rma stencil_mpi_ddt stencil_mpi_shmem stencil_mpi_ddt_funneled stencil_mpi_ddt_multiple stencil_mpi_carttopo stencil_mpi_carttopo_neighcolls

all: $(BINS)

%.o: %.c Makefile
	$(MPICC) $(CFLAGS) $< -c -lm -o $@

stencil_mpi_nonblocking: stencil_mpi_nonblocking.c Makefile $(OBJS)
	$(MPICC) $(CFLAGS) -o $@ $< $(OBJS) -lm

stencil_mpi_ddt: stencil_mpi_ddt.c Makefile $(OBJS)
	$(MPICC) $(CFLAGS) -o $@ $< $(OBJS) -lm

stencil_mpi_shmem: stencil_mpi_shmem.c Makefile $(OBJS)
	$(MPICC) $(CFLAGS) -o $@ $<  $(OBJS) -lm

stencil_mpi_ddt_rma: stencil_mpi_ddt_rma.c Makefile $(OBJS)
	$(MPICC) $(CFLAGS) -o $@ $< $(OBJS) -lm

stencil_mpi_ddt_funneled: stencil_mpi_ddt_funneled.c Makefile $(OBJS)
	$(MPICC) $(CFLAGS) -fopenmp -o $@ $< $(OBJS) -lm

stencil_mpi_ddt_multiple: stencil_mpi_ddt_multiple.c Makefile $(OBJS)
	$(MPICC) $(CFLAGS) -fopenmp -o $@ $< $(OBJS) -lm

stencil_mpi_carttopo: stencil_mpi_carttopo.c Makefile $(OBJS)
	$(MPICC) $(CFLAGS) -o $@ $< $(OBJS) -lm

stencil_mpi_carttopo_neighcolls: stencil_mpi_carttopo_neighcolls.c Makefile $(OBJS)
	$(MPICC) $(CFLAGS) -o $@ $< $(OBJS) -lm

clean:
	rm -f $(BINS) $(OBJS)
	rm -fr output*.bmp *.dSYM
