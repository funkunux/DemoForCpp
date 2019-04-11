#include "Demo.h"
#include "WebAPI.h"
#include "Logging.h"
#include <string.h>     //strnlen
#include <sys/select.h>


#define SERVER_PORT     5002
#define BUFFSIZE        1024
#define PATH            "./build.sh"

void EchoServerWorkRoutine(int fd)
{
    char buff[BUFFSIZE] = {0};
    int n = 0;
    while((n = Read(fd, buff, BUFFSIZE)) > 0)
    {
        Write_n(fd, buff, n);
    }
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
            Close(cliFd);
            exit(0);
        }
        Close(cliFd);
    }
}


void demo_echo_client()
{
    char sendLine[BUFFSIZE] = {0};
    char readLine[BUFFSIZE] = {0};
    int cliFd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serAddr = {0};
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(SERVER_PORT);
    Inet_pton(AF_INET, "127.0.0.1", &serAddr.sin_addr.s_addr);
    Connect(cliFd, reinterpret_cast<struct sockaddr*>(&serAddr), sizeof(serAddr));
    FILE* pfile = Fopen(PATH, "r");

    fd_set readSet;
    int fileFd = fileno(pfile);
    int maxfdp1 = (fileFd > cliFd ? fileFd : cliFd) + 1;
    bool endOfFile = false;
    while(true)
    {
        FD_ZERO(&readSet);
        if(!endOfFile)
            FD_SET(fileFd, &readSet);
        FD_SET(cliFd, &readSet);
        
        select(maxfdp1, &readSet, NULL, NULL, NULL);

        if(FD_ISSET(cliFd, &readSet))
        {
            if(0 == Read(cliFd, readLine, BUFFSIZE))
            {
                if(endOfFile)
                {
                    break;
                }
                else
                {
                    DEMO_ERROR("Unnormally reach EOF: %m\n");
                }
            }
            printf(readLine);
        }

        if(FD_ISSET(fileFd, &readSet))
        {
            assert(!endOfFile);
            if(Read(fileFd, sendLine, BUFFSIZE) == 0)
            {
                Shutdown(cliFd, SHUT_WR);
                Fclose(pfile);
                endOfFile = true;
                continue;
            }
            //DEMO_DEBUG(sendLine);
            Write(cliFd, sendLine, strnlen(sendLine, BUFFSIZE - 1));
        }
    }
    //Shutdown(cliFd, SHUT_WR);
    
    Close(cliFd);
}
