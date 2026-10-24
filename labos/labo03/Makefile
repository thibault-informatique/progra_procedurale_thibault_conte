# variables

CC	    = gcc
CFLAGS	= -Wall -Wextra -Wpedantic -std=c23 -g
NAME	= codebreaker.exe
OBJETS	= code.o debug.o jeu.o main.o

all: $(NAME)

# creation executable
$(NAME): $(OBJETS)
	$(CC) $(CFLAGS) $(OBJETS) -o $(NAME)

# compilation fichers source en fichiers objets

main.o: main.c jeu.h code.h debug.h
	$(CC) $(CFLAGS) -c main.c -o main.o

code.o: code.c code.h jeu.h
	$(CC) $(CFLAGS) -c code.c -o code.o

debug.o: debug.c debug.h jeu.h
	$(CC) $(CFLAGS) -c debug.c -o debug.o

jeu.o: jeu.c code.h debug.h
	$(CC) $(CFLAGS) -c jeu.c -o jeu.o

# PHONY Dit que all/clean/run ne sont pas de vrais fichiers
.PHONY: all clean run

run: $(NAME)
	./$(NAME)

# Nettoyage sous Windows
clean:
	del /f /q *.o $(NAME)

# Nettoyage sous Linux
#clean:
#	rm *.o $(NAME)
