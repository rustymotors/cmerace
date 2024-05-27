#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>


int main(void)
{
    int r = 0;
    int s;
    
    printf("Hello, World!\n");

    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0) {
        perror("socket");
        return 1;
    }
    
    r = close(s);

    if (r < 0) {
        perror("close");
        return 1;
    }

    printf("Goodbye, World!\n");

    return r;
}
