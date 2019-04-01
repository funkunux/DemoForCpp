#include "Demo.h"
#include "WebAPI.h"
#include "Logging.h"

#define SERVER_PORT     5002
#define BUFFSIZE        1024



void EchoServerWorkRoutine(int fd)
{
    char buff[BUFFSIZE] = {0};
    int n = 0;
    while((n = Read_n(fd, buff, BUFFSIZE)) > 0)
    {
        Write_n(fd, buff, n);
    }
    Close(fd);
}

void demo_echo_server()
{
    int serFd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serAddr = {0};
    Signal(SIGCLD, HandlerSigCld);
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(SERVER_PORT);
    serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(serFd, reinterpret_cast<struct sockaddr*>(&serAddr), sizeof(serAddr));
    Listen(serFd, 1);
    while(true)
    {
        struct sockaddr_in cliAddr = {0};
        socklen_t addrSize = sizeof(cliAddr);
        int cliFd = Accept(serFd, reinterpret_cast<struct sockaddr*>(&cliAddr), &addrSize);
        if(0 == fork())
        {
            Close(serFd);
            EchoServerWorkRoutine(cliFd);
            exit(0);
        }
        Close(cliFd);
    }
}


void demo_echo_client()
{
    char buff[BUFFSIZE] = {0};
    int cliFd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serAddr = {0};
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(SERVER_PORT);
    Inet_pton(AF_INET, "127.0.0.1", &serAddr.sin_addr.s_addr);
    Connect(cliFd, reinterpret_cast<struct sockaddr*>(&serAddr), sizeof(serAddr));
    Write(cliFd, "HELLO", 5);
    Shutdown(cliFd, SHUT_WR);
    Read_n(cliFd, buff, BUFFSIZE);
    buff[BUFFSIZE - 1] = 0;
    DEMO_INFO("echo: %s\n", buff);
    Close(cliFd);
}
