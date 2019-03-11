#ifndef __WEB_API_AUTHOR_FUNKUNUX__
#define __WEB_API_AUTHOR_FUNKUNUX__

#include <assert.h>
#include <sys/socket.h> //socket
//#include <sys/types.h>  
#include <arpa/inet.h>  //sockaddr_in, htons, inet_pton
#include <strings.h>    //bzero
#include <unistd.h>     //read

int Close(int fd);
int Socket(int domain, int type, int protocol);
int Inet_pton(int af, const char* src, void* dst);
int Connect(int sfd, const struct sockaddr* addr, socklen_t size);
int Bind(int sfd, const struct sockaddr* addr, socklen_t len);
int Listen(int sfd, int queueSize);
int Accept(int sfd, struct sockaddr* addr, socklen_t* plen);
int Send(int sfd, const void* buf, int len, int flags);
int Write(int sfd, const void* buf, int len);
int Read(int fd, void* buf, int len);

#endif
