#Makefile

#le compilateur
CC= gcc

#les flags de compilation
CFLAGS= -std=c99 -Wall -g

#le nom du fichier executable
OUTFILE=  jeu

#les fichiers objets
OBJS= grid.o  jeu.o 

#les bibliotheques utilisees
LDLIBS= -lm -lncurses


$(OUTFILE): $(OBJS)
	$(CC) $^ $(LDLIBS) -o $@

%o: %c
	$(CC) -c $(CFLAGS) $< -o $@



clean:
	rm -f $(OBJS) $(OUTFILE)
