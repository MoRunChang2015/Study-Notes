#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define BUFFSIZE 1024

int main(void) {
    int fd;
    int status;
    int var = 10;
    pid_t pid;

    /*fd = open("examplefiles", O_RDWR);*/

    printf("before fork\n");

    printf("pid = %d\n", getpid());
    if ((pid = fork()) < 0)
        perror("fork error\n");
    else if (0 == pid)  // child
    {
        printf("pid = %d, ppid = %d, var = %d\n", getpid(), getppid(), var);
        sleep(2);  //等待父进程终止，然后子进程被init进程领养
    } else         // parent
    {
        /*abort();  //父进程异常终止*/
        sleep(1);
        exit(0);
    }
    printf("pid = %d, ppid = %d, var = %d\n", getpid(), getppid(), var);

    return 0;
}
