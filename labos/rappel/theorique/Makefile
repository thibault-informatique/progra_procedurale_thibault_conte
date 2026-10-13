# Simple Makefile example
hello: hello.c
 gcc hello.c -o hello

# Plus "complexe"

## Main target
hello: hello.o utils.o
 gcc hello.o utils.o -o hello

## Compile source files into object files
hello.o: hello.c
 gcc -c hello.c -o hello.o

utils.o: utils.c
 gcc -c utils.c -o utils.o

## Phony target for cleaning build artifacts
clean:
 rm -f hello hello.o utils.o

 

 le -c permet de compiler uniquement sans linkage => permet de compiler un ou plusieurs.c si nécessaire (et pas tous si une minorité a été modifiée)