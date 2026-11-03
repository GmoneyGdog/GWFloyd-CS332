#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
Name: Gregoree Floyd
BlazerId: GWFloyd
Project #: 2
To compile: gcc -o search search.C
To run: ./search [See README for passable arguments]
*/
int Showinfo = 0;
int SizeFilter = 0;
int MaxSize;
int SubstringFilter = 0;
char *StrFilter;
int Depth = -1;
int WordCount(const char *filepath){
  FILE *path = fopen(filepath, "r");
  if(path == NULL){
    return -1;
  }
  int words = 0;
  char buffer[1024];
  while(fscanf(path, "%1023s", buffer) == 1){
    words++;
  }
  fclose(path);
  return words;
}
//Primary logic of search
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
    if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
      continue;
    }

    char path[1024];
    struct stat sb;
    int i;
    sprintf(path, "%s/%s", argv[1], dirent->d_name);
    if (stat(path, &sb) != 0) {
      continue;
    }
    long size;
    if(S_ISDIR(sb.st_mode)){
      continue;
    }
    size = sb.st_size;
    pid_t pid = fork();
    if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        char *extension = strchr(dirent->d_name, '.');
        if(extension != NULL && strcmp(extension, ".txt") == 0){
          int words = WordCount(path);
          printf("File: %s | Size: %ld bytes | Words:%d\n", dirent->d_name, size, words);
        }else{
          printf("File: %s | Size: %ld bytes\n", dirent->d_name, size);
        }
       
        exit(EXIT_SUCCESS);
    } 
  } 
  while(wait(NULL) > 0);
  closedir (parentDir); 
}

int main (int argc, char **argv) { 
  if(argc != 2){
    fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
    return 1;
  }
  DIR *dir = opendir(argv[1]);
  if (dir == NULL){
    fprintf(stderr, "Error: Directory not found\n");
    return 1;
  }
  readDirectory(argv);
  closedir(dir);
  return 0; 
}