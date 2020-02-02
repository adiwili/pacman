CC=gcc
CFLAGS= -xc -Wall -Werror `pkg-config gtk+-3.0 --cflags`

LDFLAGS=  `pkg-config gtk+-3.0 --libs` -lm

NAME=main

$(NAME): main.o zamykanie.o naglowkowy.o levele.o ranking.o logowanie.o plansza.o wyniki.o ruchy.o
	$(CC) zamykanie.o naglowkowy.o levele.o logowanie.o ranking.o plansza.o wyniki.o ruchy.o main.o -o $(NAME) $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

naglowkowy.o: naglowkowy.c
	$(CC) $(CFLAGS) -c naglowkowy.c -o naglowkowy.o

zamykanie.o: zamykanie.c
	$(CC) $(CFLAGS) -c zamykanie.c -o zamykanie.o

levele.o: levele.c
	$(CC) $(CFLAGS) -c levele.c -o levele.o

logowanie.o: logowanie.c
	$(CC) $(CFLAGS) -c logowanie.c -o logowanie.o

ranking.o: ranking.c
	$(CC) $(CFLAGS) -c ranking.c -o ranking.o

plansza.o: plansza.c
	$(CC) $(CFLAGS) -c plansza.c -o plansza.o

wyniki.o: wyniki.c
	$(CC) $(CFLAGS) -c wyniki.c -o wyniki.o

ruchy.o: ruchy.c
	$(CC) $(CFLAGS) -c ruchy.c -o ruchy.o