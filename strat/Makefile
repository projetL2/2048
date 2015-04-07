# Makefile

# Le compilateur:
CC= gcc

# Les flags de compilation:
CFLAGS= -std=c99 -Wall -g

# Le nom du fichier executable:
OUTFILE= jeu

# Les fichiers objets:
OBJS= grid.o easy.o strategy.o test-strat.o

# Les bibliothèques utilisées:
LDLIBS= -lncurses

# La bibliothèque à créer:
LIB= libgrid.a
AR= ar -q 

# La méthode pour compiler:
$(OUTFILE): $(OBJS)
	$(CC) $^  $(LDLIBS) -o $@

%o: %c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(LIB) :
	$(AR) $(LIB) grid.o


# Nettoyage des fichiers objets et exécutables:
clean:
	rm -f $(OBJS) $(OUTFILE)
