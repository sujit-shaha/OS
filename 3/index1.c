#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
    int fd[2];

    pid_t pid;

    int filedes = open("file.txt",O_RDONLY);
    dup2(filedes,fileno(stdin));
    close(filedes);

    if(filedes < 0)
    {
        perror("Error opening file");
        exit(1);
    }
    if(pipe(fd) < 0)
    {
        perror("Pipe failed");
        exit(1);
    }


    pid  = fork();

    if(pid < 0)
    {
        perror("Unable to fork");
        return 1;
    }
    else if(pid > 0)
    {
        dup2(fd[1],fileno(stdout));
        close(fd[0]);
        close(fd[1]);
        execl("/usr/bin/sort","sort",NULL);
    }
    else{
        dup2(fd[0],fileno(stdin));
        close(fd[0]);
        close(fd[1]);
        execl("/usr/bin/uniq","uniq",NULL);
    }

}
