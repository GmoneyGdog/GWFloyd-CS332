#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include <sys/stat.h>

void readDirectory(char **argv){
    struct dirent *dirent; 
    DIR *parentDir; 

    parentDir = opendir (argv[1]); 
    if (parentDir == NULL) { 
        printf ("Error opening directory '%s'\n", argv[1]); 
        exit (-1);
    } 

    int count = 1; 
    while((dirent = readdir(parentDir)) != NULL){ 
        printf ("[%d] %s\n", count, (*dirent).d_name);
        char path[1024];
        struct stat sb;
        sprintf(path, "%s/%s", argv[1], dirent->d_name);
        if(stat(path, &sb) == 0 && S_ISDIR(sb.st_mode) && strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
          char *tempArg[2];
          tempArg[0] = argv[0];
          tempArg[1] = path;
          readDirectory(tempArg); 
        }
        count++;
    } 

    closedir (parentDir); 
}

int main (int argc, char **argv) { 

  if (argc < 2) { 
    printf ("Usage: %s <dirname>\n", argv[0]); 
    exit(-1);
  } 

  readDirectory(argv); 
  return 0; 
}