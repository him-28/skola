#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
   printf("Enter path:");
   char buf[100];
   scanf("%s", buf);

    DIR *dir;
    struct dirent *dir_ent;

    dir = opendir(buf);   //this part
    if(dir != NULL)
    {
        while((dir_ent = readdir(dir)) != NULL)
        {   
            if(strcmp(".", dir_ent->d_name) == 0)
               continue;
            if(strcmp("..", dir_ent->d_name) == 0)
               continue;

            char path[sizeof(dir) + sizeof(dir_ent->d_name) +2];
            strcpy(path, buf);
            strcat(path, "/");
            strcat(path, dir_ent->d_name);
            //printf("%s \n", path);

            struct stat info;
            stat(path, &info);

            printf("%15s %s \n", dir_ent->d_name, S_ISDIR(info.st_mode) == 0 ? "soubor" : "adresar" );
        }
    }

    return EXIT_SUCCESS;
}
