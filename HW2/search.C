#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
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
//Primary logic of search
void readDirectory(char **argv, int indent){
  if(Depth >= 0 && indent > Depth){
    return;
  }
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
    // Gets size of current file
    long size;
    if(S_ISDIR(sb.st_mode)){
      size = 0;
    }else{
      size = sb.st_size;
    }
    //Filters out files that are above the size filter if applicable
    if (SizeFilter && size > MaxSize){
      continue;
    }
    //Filters out files that don't contain a text string if applicable 
    if (SubstringFilter && strstr(dirent->d_name, StrFilter) == NULL){
      if(!S_ISDIR(sb.st_mode)){
        continue;
      }
    }
    // Set indention based on the depth of the current file
    for(i=0; i < indent; i++){
      printf("\t");
    }
    //Shows stats if applicable, and just the file name if not
    if(Showinfo){
      printf("%s (%ld bytes, %o, %ld)\n", dirent->d_name, size, sb.st_mode & 0777, sb.st_atime);
    }else{
      printf ("%s\n", (*dirent).d_name);
    }
    //recursion to check through a found directory.
    if(stat(path, &sb) == 0 && S_ISDIR(sb.st_mode) && strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
      char *tempArg[2];
      tempArg[0] = argv[0];
      tempArg[1] = path;
      readDirectory(tempArg, indent + 1); 
    }
    count++;
  } 
  closedir (parentDir); 
}

int main (int argc, char **argv, const char *optstring) { 
  //Check what option arguments were passed
  int opt;
  while((opt = getopt(argc, argv, "Ss:f:")) != -1){
    switch (opt)
    {
    case 'S':
      Showinfo = 1;
      break;
    case 's':
      SizeFilter = 1;
      MaxSize = atoi(optarg);
      break;
    case 'f':
      SubstringFilter = 1;
        StrFilter = optarg;
        if (optind < argc){
          Depth = atoi(argv[optind]);
          optind++;
        }
      break;
    
    default:
      break;
    }
  }
  //sStarts the search
  if (optind < argc) { 
    char *args[2];
    args[0] = argv[0];
    args[1] = argv[optind];
    readDirectory(args, 0);
  }else{
    //If no argument was given, start search from the current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        char *args[2];
        args[0] = "program"; 
        args[1] = cwd; 
        readDirectory(args, 0);
    }
  }
  return 0; 
}