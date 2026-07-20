#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUF_SIZE 1024

int main(void)
{
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1)
  {
    perror("socket");
    return 1;
  }

  int opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
  {
    perror("bind");
    return 1;
  }
  
  if (listen(server_fd, 5) == -1)
  {
    perror("listen");
    return 1;
  }

  printf("Сервер слухає порт %d...\n", PORT);

  while (1)
  {
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1)
    {
      perror("accept");
      continue;
    }

    char buf[BUF_SIZE];
    ssize_t n;
    while ((n = recv(client_fd, buf, sizeof(buf) - 1, 0)) > 0)
    {
      buf[n] = '\0';
      if (strncmp(buf, "exit", 4) == 0)
        break;
      send(client_fd, buf, n, 0);
    }
    close(client_fd);
  }

  close(server_fd);
  return 0;
}