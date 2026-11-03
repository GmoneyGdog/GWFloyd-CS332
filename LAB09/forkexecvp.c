/* Simple program to illustrate the use of fork-exec-wait pattern.
* This version uses execvp and command-line arguments to create a new process.
* To Compile: gcc -Wall forkexecvp.c
* To Run: ./a.out <command> [args]
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
void quit(int sig){
    exit(0);
}
int main(int argc, char **argv) {
    pid_t pid;
    int status;
    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, quit);
    pid = fork();
    if (pid== 0) { /* this is child process */
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        execvp(argv[1], &argv[1]);
        printf("If you see this statement then execl failed ;-(\n");
        perror("execvp");
        exit(-1);
    } else if (pid > 0) { /* this is the parent process */
        printf("Wait for the child process to terminate\n");
        while (1)
        {
            pid_t result = waitpid(pid, &status, WUNTRACED);

            if (result == -1){
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(status)){
                printf("Child exited with status %d\n",
                    WEXITSTATUS(status));
                break;
            }
            else if (WIFSIGNALED(status))
            {
                printf("Child terminated by signal %d\n",
                    WTERMSIG(status));
                break;
            }
            else if (WIFSTOPPED(status))
            {
                printf("Child suspended by signal %d\n",
                    WSTOPSIG(status));
            }
        }
    } else { /* we have an error */
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
    }
    printf("[%ld]: Exiting program .....\n", (long)getpid());
    return 0;
}