#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 6665

int main(int argc, char **argv) {
    int ser_sockfd, cli_sockfd;
    int err, n, i;
    int addrlen;
    struct sockaddr_in ser_addr;
    struct sockaddr_in cli_addr;
    char recvline[200], sendline[200];

    // select
    fd_set readset, allset;
    int maxfd;
    int fdready;
    int fdnum;

    ser_sockfd = socket(AF_INET, SOCK_STREAM, 0);  //创建套接字
    if (ser_sockfd == -1) {
        printf("socket error:%s\n", strerror(errno));
        return -1;
    }

    bzero(&ser_addr, sizeof(ser_addr));

    /*在待捆绑到该TCP套接口（ser_）*/
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_addr.sin_port = htons(PORT);
    err = bind(ser_sockfd, (struct sockaddr *)&ser_addr,
               sizeof(ser_addr));  //捆绑

    if (err == -1) {
        printf("bind error:%s\n", strerror(errno));
        return -1;
    }

    err = listen(ser_sockfd, 5);  //监听地址

    if (err == -1) {
        printf("listen error\n");
        return -1;
    }

    printf("listen the port:\n");

    // select function
    FD_ZERO(&allset);
    FD_SET(ser_sockfd, &allset);
    int clientfds[FD_SETSIZE];
    maxfd = ser_sockfd;

    for (i = 0; i < FD_SETSIZE; ++i)  //多个客户端情况
    {
        clientfds[i] = -1;
    }

    while (1) {
        readset = allset;
        fdready = select(maxfd + 1, &readset, NULL, NULL,
                         NULL);  //这里的服务器端一开始是接收数据
        if (-1 == fdready) {
            perror("select error:");
            exit(1);
        }

        if (FD_ISSET(ser_sockfd, &readset))  //测试监听描述字是否已经准备好
        {
            addrlen = sizeof(struct sockaddr);  //准备好则进行连接
            cli_sockfd =
                accept(ser_sockfd, (struct sockaddr *)&cli_addr, &addrlen);

            if (-1 == cli_sockfd) {
                perror("accpet error:");
                exit(1);
            }

            for (i = 0; i < FD_SETSIZE; ++i) {
                if (clientfds[i] < 0)  //将客户端描述字添加到队列
                {
                    clientfds[i] = cli_sockfd;
                    break;
                }
            }

            fdnum = (i > fdnum ? i : fdnum);

            if (i == FD_SETSIZE) {
                perror("too many clients:");
                exit(1);
            }

            FD_SET(cli_sockfd, &allset);
            maxfd = (cli_sockfd > maxfd ? cli_sockfd : maxfd);
            //事实上这里select设置的是一直等待，如果不是这样，这里需要continue回去继续select
        }

        for (i = 0; i <= fdnum; ++i) {
            if (clientfds[i] < 0)  //找到连接后的描述字
                continue;

            if (FD_ISSET(clientfds[i], &readset))  //测试是否可读
            {
                printf("waiting for client...\n");
                n = recv(clientfds[i], recvline, 1024, 0);
                if (0 == n) {
                    close(clientfds[i]);
                    FD_CLR(clientfds[i], &allset);
                    clientfds[i] = -1;
                    continue;
                }
                recvline[n] = '\0';
                printf("recv data is:%s\n", recvline);
                printf("input your words:");
                scanf("%s", sendline);
                send(clientfds[i], sendline, strlen(sendline), 0);
            }
        }
    }
    return 0;
}
