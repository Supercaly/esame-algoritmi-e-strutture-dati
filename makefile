#
# Progetto di Algoritmi e Strutture dati sessione autunnale 2015/2016
# di Lorenzo Calisti matricola: 271250 email: l.calisti@campus.uniurb.it
#
# Makefile
#
#Variabili
target = programma
CC = gcc
RM = rm -f
CFLAGS = -ansi -Wall -W -Wshadow
oggetti = main.o grafo.o statistiche.o ordinamento.o
sorgenti = main.c grafo.c statistiche.c ordinamento.c
#Obbiettivi
#genera il file eseguibile
$(target): $(oggetti) makefile
	$(CC) $(CFLAGS) -o2 $(oggetti) -o $(target)
#genera i file oggetto
$(oggetti): $(sorgenti) makefile
	$(CC) $(CFLAGS) -c $(sorgenti)
#genera il file per il debug
debug: $(oggetti) makefile
	$(CC) $(CFLAGS) $(oggetti) -o $(target) -g
#elimina i file oggetto e l'eseguibile
.PHONY: clean
clean:
	$(RM) $(oggetti) $(target)
