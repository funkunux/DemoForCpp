#ifndef __WEB_API_AUTHOR_FUNKUNUX__
#define __WEB_API_AUTHOR_FUNKUNUX__

#include <assert.h>
#include <sys/socket.h>     //socket
#include <sys/types.h>  
#include <netinet/tcp.h>    //define TCP_*
#include <arpa/inet.h>      //sockaddr_in, htons, inet_pton
#include <strings.h>        //bzero
#include <unistd.h>         //read
#include <signal.h>
#include <stdio.h>

int Close(int fd);
int Shutdown(int sockfd, int how);
int Socket(int domain, int type, int protocol);
int Inet_pton(int af, const char* src, void* dst);
char* Inet_ntop(int af, const void* src, char* dst, socklen_t len);
int Connect(int sfd, const struct sockaddr* addr, socklen_t size);
int Bind(int sfd, const struct sockaddr* addr, socklen_t len);
int Listen(int sfd, int queueSize);
int Accept(int sfd, struct sockaddr* addr, socklen_t* plen);
int Send(int sfd, const void* buf, int len, int flags);
int Write(int sfd, const void* buf, int len);
int Read(int fd, void* buf, int len);
int ReadLine(int fd, void* buf, int len);
int Write_n(int sfd, const void* buf, int len);
int Read_n(int fd, void* buf, int len);
int Getsockopt(int sfd, int level, int optname, void* optval, socklen_t* len);
int Setsockopt(int sfd, int level, int optname, const void* optval, socklen_t len);
typedef void (*SignalHandler)(int);
SignalHandler Signal(int signum, SignalHandler handler);
void HandlerSigCld(int signum);
char* Fgets(char* s, int size, FILE* stream);
FILE* Fopen(const char* path, const char* mode);
int Fclose(FILE* stream);
#endif
