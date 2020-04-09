# makefile dla programu: reversi
CC= gcc

# ogolne flagi kompilacji dla modulow
CFLAGS= -std=c99 -Wall -Wextra -Werror

PACKAGE= `pkg-config --cflags --libs gtk+-3.0`

# ogolne flagi konsolidacji programu
LDFLAGS= -lm

NAME= reversi

$(NAME): main.o plansza.o tablica.o wykonany_ruch.o fifo.o
	$(CC) $(CFLAGS) main.o plansza.o tablica.o wykonany_ruch.o fifo.o -o $(NAME) $(LDFLAGS) $(PACKAGE)
main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o main.o $(PACKAGE)
plansza.o: plansza.c plansza.h
	$(CC) -c $(CFLAGS) plansza.c -o plansza.o $(PACKAGE)
tablica.o: tablica.c tablica.h
	$(CC) -c $(CFLAGS) tablica.c -o tablica.o
wykonany_ruch.o: wykonany_ruch.c wykonany_ruch.h
	$(CC) -c $(CFLAGS) wykonany_ruch.c -o wykonany_ruch.o $(PACKAGE)
fifo.o: fifo.c fifo.h
	$(CC) -c $(CFLAGS) fifo.c -o fifo.o

clean: 
	rm -rf *o $(NAME)
