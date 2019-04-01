#include "WebAPI.h"
#include "Logging.h"
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int Socket(int domain, int type, int protocol)
{
    int sfd = socket(domain, type, protocol);
    if(-1 == sfd)
    {
        DEMO_ERROR("Create socket: %m\n");
        exit(1);
    }
    return sfd;
}

int Inet_pton(int af, const char* src, void* dst)
{
    assert(src && dst);
    if(0 >= inet_pton(af, src, dst))
    {
        DEMO_ERROR("Failed to get addr[%s]\n", src);
        exit(1);
    }

    return 1;
}

char* Inet_ntop(int af, const void* src, char* dst, socklen_t len)
{
    assert(src && dst);
    if(dst != inet_ntop(af, src, dst, len))
    {
        DEMO_ERROR("Failed to get addr\n");
        exit(1);
    }

    return dst;
}

int Connect(int sfd, const struct sockaddr* addr, socklen_t size)
{
    assert(addr);
    if(0 != connect(sfd, addr, size))
    {
        DEMO_ERROR("connect failed: %m\n");
        exit(1);
    }
    return 0;
}

int Bind(int sfd, const struct sockaddr* addr, socklen_t len)
{
    assert(addr);
    if(0 != bind(sfd, addr, len))
    {
        DEMO_ERROR("bind error: %m\n");
        exit(1);
    }
    return 0;
}

int Listen(int sfd, int queueSize)
{
    if(0 != listen(sfd, queueSize))
    {
        DEMO_ERROR("listen error: %m\n");
        exit(1);
    }
    return 0;
}

int Accept(int sfd, struct sockaddr* addr, socklen_t* plen)
{
    assert(addr && plen);
    int peer_sfd = accept(sfd, addr, plen);
    if(-1 == peer_sfd)
    {
        DEMO_ERROR("accept error: %m\n");
        exit(1);
    }
    return peer_sfd;
}

int Send(int sfd, const void* buf, int len, int flags)
{
    int n = 0;
    if((n = send(sfd, buf, len, flags))== -1)
    {
        DEMO_ERROR("send error: %m\n");
        exit(1);
    }
    return n;
}

int Write(int fd, const void* buf, int len)
{
    int n = 0;
    if((n = write(fd, buf, len))== -1)
    {
        DEMO_ERROR("write error: %m\n");
        exit(1);
    }
    if(n < len)
    {
        DEMO_WARN("expect to write %d bytes, actually wrote %d bytes\n", len, n);
    }
    return n;
}

int Write_n(int fd, const void* buf, int len)
{
    int n = 0;
    int left = len;
    while(left > 0)
    {
        if((n = write(fd, (char *)buf + len - left, left)) <= 0)
        {
            if(EINTR == errno && n < 0)
            {
                continue;
            }
            DEMO_ERROR("write error: %m\n");
            exit(1);
        }
        left -= n;
    }
    return len - left;
}

int Read(int fd, void* buf, int len)
{
    int n = 0;
    if((n = read(fd, buf, len))== -1)
    {
        DEMO_ERROR("read error: %m\n");
        exit(1);
    }
    return n;
}

int Read_n(int fd, void* buf, int len)
{
    int n = 0;
    int left = len;
    while(left > 0)
    {
        if((n = read(fd, (char *)buf + len - left, left)) <= 0)
        {
            if(0 == n)
            {
                DEMO_DEBUG("Reach EOF\n");
                break;
            }
            if(EINTR == errno)
            {
                continue;
            }
            DEMO_ERROR("read error: %m\n");
            exit(1);
        }
        left -= n;
    }
    return len - left;
}

int Getsockopt(int sfd, int level, int optname, void* optval, socklen_t* len)
{
    assert(optval && len);
    if(0 != getsockopt(sfd, level, optname, optval, len))
    {
        DEMO_ERROR("getsockopt error: %m\n");
        exit(1);
    }
    return 0;
}

int Setsockopt(int sfd, int level, int optname, const void* optval, socklen_t len)
{
    assert(optval);
    if(0 != setsockopt(sfd, level, optname, optval, len))
    {
        DEMO_ERROR("setsockopt error: %m\n");
        exit(1);
    }
    return 0;
}

int Close(int fd)
{
    if(0 != close(fd))
    {
        DEMO_ERROR("close error: %m\n");
        exit(1);
    }
    return 0;
}

int Shutdown(int sockfd, int how)
{
    if(shutdown(sockfd, how) < 0)
    {
        DEMO_ERROR("shutdown error: %m\n");
        return -1;
    }
    return 0;
}

SignalHandler Signal(int signum, SignalHandler handler)
{
    struct sigaction newAct = {0};
    struct sigaction oldAct = {0};
    if(SIGALRM == signum)
    {
#ifdef SA_INTERRUPT
        newAct.sa_flags |= SA_INTERRUPT;
#endif
    }
    else
    {
#ifdef SA_RESTART
        newAct.sa_flags |= SA_RESTART;
#endif
    }
    newAct.sa_handler = handler;
    if(sigaction(signum, &newAct, &oldAct) < 0) 
    {
        DEMO_ERROR("sigaction error: %m\n");
        exit(1);
    }
    return oldAct.sa_handler;
}

void HandlerSigCld(int signum)
{
    assert(SIGCLD == signum);
    pid_t pid = 0;
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0)
    {
        DEMO_INFO("Child Pid[%d] terminate.\n", pid);
    }
    return;
}
