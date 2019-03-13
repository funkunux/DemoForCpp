#include "Demo.h"
#include "Logging.h"
#include "WebAPI.h"
#include <time.h>   //time, ctime
#include <string.h> //strnlen

#define MAXLINE 1024

void demo_time_client()
{
    char readLine[MAXLINE] = {0};
    int sfd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(13);
    Inet_pton(AF_INET, "127.0.0.1", static_cast<void *>(&serverAddr.sin_addr.s_addr));
    Connect(sfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    unsigned int n;
    while((n = Read(sfd, readLine, MAXLINE)) > 0)
    {
        readLine[n] = 0;
        printf("%s", readLine);
    }
    if(0 > n)
    {
        DEMO_ERROR("read error: %m\n");
        exit(1);
    }
    else
    {
        printf("\n");
    }

    exit(0);
}

void demo_time_server()
{
    int sfd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(13);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(sfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    Listen(sfd, 1);
    while(true)
    {
        struct sockaddr_in clientAddr = {0};
        socklen_t len = sizeof(clientAddr);
        int cli_sfd = Accept(sfd, (struct sockaddr*)&clientAddr, &len);
        time_t t = time(NULL);
        char* tStr = ctime(&t);
        assert(tStr);
        Write(cli_sfd, tStr, strnlen(tStr, MAXLINE));
        Close(cli_sfd);
    }
}
