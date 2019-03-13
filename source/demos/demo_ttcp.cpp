#include "Demo.h"
#include "Logging.h"
#include "WebAPI.h"
#include <time.h>

class SessionMessage
{
public:
    unsigned int size;
    unsigned int count;
    SessionMessage(int s, int c) : size(s), count(c){}
};

class PayloadMessage
{
public:
    unsigned int size;
    char* content;
    PayloadMessage(int s) : size(s)
    {
        content = new char[size];
        for(unsigned int i = 0, j = 0; i < size;)
        {
            if(10 == j) j = 0;
            content[i++] = '0' + j;
        }
    }
    ~PayloadMessage()
    {
        delete [] content;
        content = NULL;
    }
};

const char *ipAddr = "127.0.0.1";
int port = 5001;

void demo_ttcp_client()
{
    clock_t start, end;
    SessionMessage session(65000, 40960);
    PayloadMessage payload(session.size);
    
    int sfd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    Inet_pton(AF_INET, ipAddr, &addr.sin_addr.s_addr);

    printf("TTCP CLIENT:\n");
    printf("Send %d x %d to %s:%d\n", session.size, session.count, ipAddr, port);
    Connect(sfd, (struct sockaddr*)&addr, sizeof(addr));

    Write(sfd, &session, sizeof(session));
    unsigned int ack;
    start = clock();
    for(unsigned int i = 0; i < session.count; i++)
    {
        Write_n(sfd, payload.content, payload.size);
        Read_n(sfd, &ack, sizeof(ack));
        if(payload.size != ack)
        {
            DEMO_ERROR("ack[%d] != payload.size[%d]\n");
            break;
        }
    }
    end = clock();
    double totalMib = 1.0 * session.size * session.count / 1024 / 1024;
    double timeUsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total: %fMib, Spend: %fs, Speed: %fMib/s\n", totalMib, timeUsed, totalMib / timeUsed);
    Close(sfd);
}

void demo_ttcp_server()
{
    int sfd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    Listen(sfd, 1);
    while(true)
    {
        int cli_sfd;
        sockaddr_in cli_addr;
        int cli_addr_len = sizeof(cli_addr);
        cli_sfd = Accept(sfd, (struct sockaddr*)&cli_addr, (socklen_t*)&cli_addr_len);
        SessionMessage session(0, 0);
        Read_n(cli_sfd, &session.size, sizeof(session.size));
        Read_n(cli_sfd, &session.count, sizeof(session.count));
        char *addrStr = new char[32];
        cli_addr.sin_addr.s_addr = ntohl(cli_addr.sin_addr.s_addr);
        DEMO_INFO("Recieve %d x %d from %s\n", session.size, session.count, Inet_ntop(AF_INET, &cli_addr, addrStr, sizeof(cli_addr)));
        char *payload = new char[session.size];
        for(unsigned int i = 0; i < session.count; i++)
        {
            int n;
            n = Read_n(cli_sfd, payload, session.size);
            Write_n(cli_sfd, &n, sizeof(n));
        }
        Close(cli_sfd);
    }
}