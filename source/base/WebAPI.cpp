#include "WebAPI.h"
#include "Logging.h"
#include <stdlib.h>

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
        if((n = write(fd, (char *)buf + len - left, left)) == -1)
        {
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
        if((n = read(fd, (char *)buf + len - left, left)) == -1)
        {
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
