#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 8080
#define BUF_SIZE 1024
#define MAX_CLIENTS 5

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
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
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

  int flags = fcntl(server_fd, F_GETFL, 0);
  fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

  int client_sockets[MAX_CLIENTS];
  for (int i = 0; i < MAX_CLIENTS; i++)
    client_sockets[i] = -1;

  fd_set readfds;
  char buf[BUF_SIZE];

  while (1)
  {
    FD_ZERO(&readfds);
    FD_SET(server_fd, &readfds);
    int max_fd = server_fd;

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
      int sd = client_sockets[i];
      if (sd > 0)
        FD_SET(sd, &readfds);
      if (sd > max_fd)
        max_fd = sd;
    }

    select(max_fd + 1, &readfds, NULL, NULL, NULL);

    if (FD_ISSET(server_fd, &readfds))
    {
      int new_socket = accept(server_fd, NULL, NULL);
      if (new_socket == -1)
      {
        perror("accept");
        continue;
      };

      int client_flags = fcntl(new_socket, F_GETFL, 0);
      fcntl(new_socket, F_SETFL, client_flags | O_NONBLOCK);

      int placed = 0;

      for (int i = 0; i < MAX_CLIENTS; i++)
      {
        if (client_sockets[i] == -1)
        {
          client_sockets[i] = new_socket;
          placed = 1;
          break;
        }
      }

      if (!placed)
      {
        printf("Сервер переповнений, відхиляю нового клієнта\n");
        close(new_socket);
      }
    }

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
      int sd = client_sockets[i];
      if (sd > 0 && FD_ISSET(sd, &readfds))
      {
        ssize_t n = recv(sd, buf, sizeof(buf) - 1, 0);
        if (n > 0)
        {
          buf[n] = '\0';
          send(sd, buf, n, 0);
        }
        else if (n == 0)
        {
          close(sd);
          client_sockets[i] = -1;
        }
        else // n == -1
        {
          if (errno != EWOULDBLOCK && errno != EAGAIN)
          {
            perror("recv");
            close(sd);
            client_sockets[i] = -1;
          }
        }
      }
    }
  }

  return 0;
}