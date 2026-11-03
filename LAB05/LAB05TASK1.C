#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void printstat(struct stat statbuf);
void printstat(struct stat sb) {
/* copied from the lstat man page example as is */
printf("File type: ");
switch (sb.st_mode & S_IFMT) {
case S_IFBLK: printf("block device\n"); break;
case S_IFCHR: printf("character device\n"); break;
case S_IFDIR: printf("directory\n"); break;
case S_IFIFO: printf("FIFO/pipe\n"); break;
case S_IFLNK: printf("symlink\n"); break;
case S_IFREG: printf("regular file\n"); break;
case S_IFSOCK: printf("socket\n"); break;
default: printf("unknown?\n"); break;
}
printf("I-node number: %ld\n", (long) sb.st_ino);
printf("Mode: %lo (octal)\n",
(unsigned long) sb.st_mode);
printf("Link count: %ld\n", (long) sb.st_nlink);
printf("Ownership: UID=%ld GID=%ld\n",
(long) sb.st_uid, (long) sb.st_gid);
printf("Preferred I/O block size: %ld bytes\n",
(long) sb.st_blksize);
printf("File size: %lld bytes\n",
(long long) sb.st_size);
printf("Blocks allocated: %lld\n",
(long long) sb.st_blocks);
printf("Last status change: %s", ctime(&sb.st_ctime));
printf("Last file access: %s", ctime(&sb.st_atime));
printf("Last file modification: %s", ctime(&sb.st_mtime));
}

int main(int argc, char **argv) { 
    int i; 
    struct stat buf; 
    char *ptr; 

    for (i = 1; i < argc; i++) { 
        printf("%s: ", argv[i]); 
        if (lstat(argv[i], &buf) < 0) { 
            printf("lstat error"); 
            continue; 
        } 

        if (S_ISREG(buf.st_mode)) 
            ptr = "regular"; 
        else if (S_ISDIR(buf.st_mode)) 
            ptr = "directory"; 
        else if (S_ISCHR(buf.st_mode)) 
            ptr = "character special"; 
        else if (S_ISBLK(buf.st_mode)) 
            ptr = "block special"; 
        else if (S_ISFIFO(buf.st_mode)) 
            ptr = "fifo"; 
        else if (S_ISLNK(buf.st_mode)) 
            ptr = "symbolic link"; 
        else if (S_ISSOCK(buf.st_mode)) 
            ptr = "socket"; 
        else 
            ptr = "** unknown mode **"; 
        printf("%s\n", ptr); 
    } 
    printstat(buf);

    exit(0); 
}