#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

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
            char path[sizeof(dir) + sizeof(dir_ent->d_name) +2];
            strcpy(path, buf);
            strcat(path, "/");
            strcat(path, dir_ent->d_name);
            //printf("%s \n", path);

            printf("%20s %s\n", dir_ent->d_name, opendir(path) == 0 ? "soubor" : "adresar");
        }
    }
    close(dir);

    return EXIT_SUCCESS;
}
