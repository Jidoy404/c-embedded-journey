#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUF_SIZE 1024

int main(void)
{
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd == -1)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind");
        return 1;
    }

    printf("UDP-сервер слухає порт %d...\n", PORT);

    char buf[BUF_SIZE];
    struct sockaddr_in client_addr;

    while (1)
    {
        socklen_t client_len = sizeof(client_addr);
        ssize_t n = recvfrom(sock_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&client_addr, &client_len);
        if (n == -1)
        {
            perror("recvfrom");
            continue;
        }
        printf("Отримано від клієнта: %s\n", buf);
        buf[n] = '\0';

        sendto(sock_fd, buf, n, 0, (struct sockaddr *)&client_addr, client_len);
    }

    close(sock_fd);
    return 0;
}