CC = gcc 
CFLAGS = -Wall -Wextra -Wpedantic -g
EXEC = prog 
 
# Règle par défaut 
all: $(EXEC) 
 
# Éditon de liens 
$(EXEC): main.o produit.o 
	$(CC) $(CFLAGS) main.o produit.o -o $(EXEC) 
 
# Compilaton de main.c (dépend de main.c et du header produit.h) 
main.o: main.c produit.h 
	$(CC) $(CFLAGS) -c main.c 
 
# Compilaton de produit.c (dépend de produit.c et produit.h) 
produit.o: produit.c produit.h 
	$(CC) $(CFLAGS) -c produit.c 
 
# Netoyage 
clean: 
	rm -f *.o $(EXEC) 
