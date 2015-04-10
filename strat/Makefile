#ATTENTION makefile à utiliser que pour tester en privé la strategie sinon 

#telecharger tournament file:///net/stockage/pp1/strategies/

#chmod +x tournament

#gcc -std=c99 -fPIC -c grid.c -o grid.o
#gcc -std=c99 -fPIC -c strategy.c -o strategy.o
#gcc -std=c99 -fPIC -c fast.c -o fast.o
#gcc -shared -Wl,-soname,libA1_almyre_chambres_mahazoasy_petureau_fast.so.1 -o libA1_almyre_chambres_mahazoasy_petureau_fast.so *.o

# Makefile

# Le compilateur:
CC= gcc

# Les flags de compilation:
CFLAGS= -std=c99 -Wall -g

# Le nom du fichier executable:
OUTFILE= test-strat

# Les fichiers objets:
OBJS= grid.o libgrid.a strategy.o test-strat.o efficient.o #ou fast.o

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
