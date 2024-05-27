#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(void)
{
    void *buff = malloc(1024);
    int r = 0;
    int s;
    int c;
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(8226),
        .sin_addr = {.s_addr = INADDR_ANY}};

    struct sockaddr_in client_addr;

    printf("Hello, World!\n");

    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0)
    {
        perror("socket");
        return 1;
    }

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 1;
    }

    r = listen(s, 5);

    if (r < 0)
    {
        perror("listen");
        return 1;
    }

    c = accept(s, NULL, NULL) ;

    if (c < 0)
    {
        printf("Error accepting connection: %d\n", c);
        perror("accept");
        return 1;
    }

    r = getpeername(c, (struct sockaddr *)&client_addr, (socklen_t[]){sizeof(client_addr)});

    if (r < 0)
    {
        perror("getpeername");
        return 1;
    }

    printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    r = recv(c, buff, 1024, 0);

    if (r < 0)
    {
        perror("recv");
        return 1;
    }

    printf("Received %d bytes\n", r);

    char *incoming = (char *)buff;

    printf("Received: ");
    for (int i = 0; i < r; i++)
    {
        printf("%02x", incoming[i]);
    }
    printf("\n");

    r = close(s);

    if (r < 0)
    {
        perror("close");
        return 1;
    }

    printf("Goodbye, World!\n");

    return r;
}
