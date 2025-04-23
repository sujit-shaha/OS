#include<bits/stdc++.h>
#include<sys/wait.h>
using namespace std;

int main()
{
    int fd[2];
    int n;
    pipe(fd);
    char buff[100];
    pid_t p = fork();

    char msg[] = "Hello from parent process";

    if(p<0)
    {
        cout<<"Error in fork"<<endl;
        exit(1);
    }
    else if(p > 0)
    {
        close(fd[0]);
        cout<<"Message sent to child"<<endl;
        write(fd[1],msg,sizeof(msg));
        wait(NULL);
    }
    else
    {
        close(fd[1]);
        n = read(fd[0],buff,100);
        cout<<"Message received from parent: "<<buff<<endl;
    }
    return 0;
}