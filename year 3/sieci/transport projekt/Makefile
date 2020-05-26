#Konrad Kasprzyk
#299243

CC= gcc

# ogolne flagi kompilacji dla modulow
CFLAGS= -std=gnu99 -Wall -Wextra -Werror

NAME= transport

$(NAME): main.o check_data.o receive.o send.o pool_manager.o
	$(CC) $(CFLAGS) main.o check_data.o receive.o send.o pool_manager.o -o $(NAME)
main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o main.o
check_data.o: check_data.c check_data.h
	$(CC) -c $(CFLAGS) check_data.c -o check_data.o
receive.o: receive.c receive.h
	$(CC) -c $(CFLAGS) receive.c -o receive.o
send.o: send.c send.h
	$(CC) -c $(CFLAGS) send.c -o send.o
pool_manager.o: pool_manager.c pool_manager.h
	$(CC) -c $(CFLAGS) pool_manager.c -o pool_manager.o

clean: 
	rm -rf *o
distclean:
	rm -rf *o $(NAME)
