#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
  addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, "10.12.15.119", &addr.sin_addr) <= 0)
  {
    perror("inet_pton");
    return 1;
  }

  char buf[BUF_SIZE];
  while (1)
  {
    printf("> ");
    if (!fgets(buf, sizeof(buf), stdin))
      break;
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
      buf[--len] = '\0';

    sendto(sock_fd, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr));
    if (strcmp(buf, "exit") == 0)
      break;

    ssize_t n = recvfrom(sock_fd, buf, sizeof(buf) - 1, 0, NULL, NULL);
    if (n <= 0)
      continue;
    buf[n] = '\0';
    printf("Сервер: %s\n", buf);
  }

  close(sock_fd);
  return 0;
}
