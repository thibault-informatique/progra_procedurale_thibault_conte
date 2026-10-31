#prerequis : bin/ et build/ existent déjà donc - portable => nécessite @mkdir -p bin et @mkdir -p build 

#Variables
CC		= gcc
CFLAGS	= -Wall -Wextra -Wpedantic -std=c23 -g -MMD -MP 
# MMD fait générer un fichier .d contenant les headers inclus dans les .c
# ca evite de devoir mettre tous les .h comme dependance des cibles .o
# MP ajout de règles fictives pour ne pas casser si un header est supprimé

INC		= -Iinclude
NAME	= bin/network_manager
SRC		= src/device.c src/display.c src/main.c src/network.c
OBJ		= $(SRC:src/%.c=build/%.o) # transforme src/main.c en build/main.o, etc.

all : $(NAME)

run: $(NAME)
	./$(NAME)
	
#Création exécutable du projet | main target
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

#Compilation des fichiers sources en fichiers objets
# factorisable via 
# build/%.o: src/%.c
#	$(CC) $(CFLAGS) $(INC) -c $< -o $@

build/main.o: src/main.c
	$(CC) $(CFLAGS) $(INC) -c src/main.c -o build/main.o

build/device.o: src/device.c
	$(CC) $(CFLAGS) $(INC) -c src/device.c -o build/device.o

build/display.o: src/display.c
	$(CC) $(CFLAGS) $(INC) -c src/display.c -o build/display.o

build/network.o: src/network.c
	$(CC) $(CFLAGS) $(INC) -c src/network.c -o build/network.o

-include $(wildcard build/*.d)
# include équivalent pour Makefile du #include <> en C | le '-': ignore silencieusement si le fichier n'existe pas (premier passage)
# si des fichiers de dépendance existe charge les

.PHONY: clean run
clean:
	rm -rf build/* bin/*
# attention très dangereux si variables $(DIR)/* et que vide => car équivaudrait à la racine système -rf /*