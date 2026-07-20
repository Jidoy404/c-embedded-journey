#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{

  int clientsocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientsocket == -1)
  {
    perror("clientsocket");
    return 1;
  }

  struct sockaddr_in servaddr = {0};
  servaddr.sin_family = AF_INET;   // IPv4
  servaddr.sin_port = htons(8080); // порт
  if (inet_pton(AF_INET, "192.168.0.102", &servaddr.sin_addr) <= 0)
{
    perror("inet_pton");
    return 1;
}

  if (connect(clientsocket, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
  {
    perror("connect");
    return 1;
  }

  char buf[1024];

  while (1)
  {
    printf("> ");
    if (!fgets(buf, sizeof(buf), stdin))
      break;
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
      buf[--len] = '\0';

    send(clientsocket, buf, len, 0);
    if (strcmp(buf, "exit") == 0)
      break;

    ssize_t n = recv(clientsocket, buf, sizeof(buf) - 1, 0);
    if (n <= 0)
      break;
    buf[n] = '\0';
    printf("Сервер: %s\n", buf);
  }

  close(clientsocket);

  return 0;
}