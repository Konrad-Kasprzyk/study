#Konrad Kasprzyk
#299243

CC= gcc

# ogolne flagi kompilacji dla modulow
CFLAGS= -std=gnu99 -Wall -Wextra -Werror

NAME= traceroute

$(NAME): main.o receive.o send.o
	$(CC) $(CFLAGS) main.o receive.o send.o -o $(NAME)
main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o main.o
receive.o: receive.c receive.h
	$(CC) -c $(CFLAGS) receive.c -o receive.o
send.o: send.c send.h
	$(CC) -c $(CFLAGS) send.c -o send.o

clean: 
	rm -rf *o
distclean:
	rm -rf *o $(NAME)
