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
    int sockfd, fdready;
    int err, n;
    struct sockaddr_in addr_ser;
    char sendline[20], recvline[20];
    fd_set writeset;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);  //创建套接字

    if (sockfd == -1) {
        printf("socket error\n");
        return -1;
    }

    bzero(&addr_ser, sizeof(addr_ser));

    /**/
    addr_ser.sin_family = AF_INET;
    addr_ser.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_ser.sin_port = htons(PORT);

    err = connect(sockfd, (struct sockaddr *)&addr_ser, sizeof(addr_ser));

    if (err == -1) {
        printf("connect error\n");
        return -1;
    }

    printf("connect with server...\n");

    FD_ZERO(&writeset);
    while (1) {
        printf("sockfd = %d\n", sockfd);
        FD_SET(sockfd, &writeset);
        fdready =
            select(sockfd + 1, NULL, &writeset, NULL, NULL);  //此处是写描述符集
        if (-1 == fdready) {
            perror("select error:");
            exit(1);
        }
        if (FD_ISSET(sockfd, &writeset)) {
            printf("Input your words:");
            scanf("%s", sendline);

            send(sockfd, sendline, strlen(sendline), 0);  //客户端-->服务端

            printf("waiting for server...\n");

            n = recv(sockfd, recvline, 100, 0);  //客户端<--服务端
            recvline[n] = '\0';

            printf("recv data is:%s\n", recvline);
        }
    }

    return 0;
}
