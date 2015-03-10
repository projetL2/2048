#Makefile

#le compilateur
CC= gcc

#les flags de compilation
CFLAGS= -std=c99 -Wall -g

#le nom du fichier executable
OUTFILE= test-mouvement

#les fichiers objets
OBJS= grid.o testmouvement.o

#les bibliotheques utilisees
LDLIBS= -lm


$(OUTFILE): $(OBJS)
	$(CC) $^ $(LDLIBS) -o $@

%o: %c
	$(CC) -c $(CFLAGS) $< -o $@



clean:
	rm -f $(OBJS) $(OUTFILE)
