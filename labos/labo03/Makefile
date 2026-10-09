CC = gcc 
CFLAGS = -Wall -Wextra -Wpedantic -g -std=c23
EXEC = prog 
 
# Règle par défaut 
all: $(EXEC) 
 
# Éditon de liens 
$(EXEC): main.o produit.o inventaire.o utils.o
	$(CC) $(CFLAGS) -o $(EXEC) main.o produit.o inventaire.o utils.o
 

# Compilation des différents .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# dépendances sur les headers
main.o: produit.h inventaire.h utils.h
produit.o: produit.h
inventaire.o: inventaire.h produit.h
utils.o: utils.h

# PHONY Dit que all/clean/run ne sont pas de vrais fichiers
.PHONY: all clean run

run: $(EXEC)
	./$(EXEC)

# Nettoyage 
clean: 
	rm -f *.o $(EXEC) 
