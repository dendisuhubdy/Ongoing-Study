#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../bzero.h"
#include "../tcpip.h"

#define MAXLINE (1024)


int _tmain(int argc, _TCHAR **argv)
{
    socket_t sockfd;
    struct sockaddr_in6 servaddr;
    char recvline[MAXLINE];
    int n;
    int res;

#ifdef _WIN32
    _tsetlocale(LC_ALL, _T(""));
#endif

    if (argc != 2)
    {
        fprintf(stderr, "Usage:\n    a.out <IP>\n");
        return EXIT_FAILURE;
    }

    TCP_IP_INIT();

    if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        print_error_ex(_T("socket"));
        return EXIT_FAILURE;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(13); // daytime server

    res = inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr);
    if (res != 1)
    {
        if (res == 0)
            _ftprintf(stderr, _T("Invalid IPv4 address: %s\n"), argv[1]);
        else if (res == -1)
            print_error_ex(_T("inet_pton"));
        else
            fprintf(stderr, "Unexpected return value: %d.\n", res);

        return EXIT_FAILURE;
    }

    if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        print_error_ex(_T("connect"));
        closesock(sockfd);
        return EXIT_FAILURE;
    }

#ifdef _WIN32
    while ((n = recv(sockfd, recvline, MAXLINE, 0)) > 0)
#else
    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
#endif
    {
        recvline[n] = '\0';
        if (fputs(recvline, stdout) == EOF)
        {
            fprintf(stderr, "fputs failed(%d): %s\n", errno, strerror(errno));
            break;
        }
    }

    if (n < 0)
    {
#ifdef _WIN32
        print_error_ex(_T("recv"));
#else
        fprintf(stderr, "read failed(%d): %s\n", errno, strerror(errno));
#endif
    }

    closesock(sockfd);

    return 0;
}


// References:
// UNPv1, 3rd, Ch1.3
