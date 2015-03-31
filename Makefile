# Makefile

# Le compilateur
CC= gcc

# Les flags de compilation
CFLAGS= -std=c99 -Wall -g

# Le nom du fichier executable
OUTFILE=  test-strat

# Les fichiers objets
OBJS= grid.o  test-strat.o 

# Les bibliothèques utilisées
LDLIBS= -lncurses

# La méthode pour compiler
$(OUTFILE): $(OBJS)
	$(CC) $^ $(LDLIBS) -o $@

%o: %c
	$(CC) -c $(CFLAGS) $< -o $@


# Nettoyage des fichiers objets et exécutables
clean:
	rm -f $(OBJS) $(OUTFILE)
