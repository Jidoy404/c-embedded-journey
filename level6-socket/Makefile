CC = gcc
CFLAGS = -Wall -Wextra

all: echoServTcp clientTcp echoServUdp clientUdp

echoServTcp: echoServTcp.c
	$(CC) $(CFLAGS) -g -o echoServTcp echoServTcp.c

clientTcp: clientTcp.c
	$(CC) $(CFLAGS) -g -o clientTcp clientTcp.c

echoServUdp: echoServUdp.c
	$(CC) $(CFLAGS) -g -o echoServUdp echoServUdp.c

clientUdp: clientUdp.c
	$(CC) $(CFLAGS) -g -o clientUdp clientUdp.c

clean:
	rm -f echoServTcp clientTcp echoServUdp clientUdp