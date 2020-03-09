CC = gcc
CFLAGS = -O2 -march=native -Wformat-security -Warray-bounds -Wall
ODIR=obj

all: server_main.c signal.c
	$(CC) -o tesla-server server_main.c signal.c

clean:
	rm -f *.o tesla-server
