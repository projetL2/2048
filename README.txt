#Cher utilisateur,

#Voici notre dossier pour jouer au jeu 2048.
#Après l'avoir installé, tu pourras jouer avec les touches haut, bas, droite, gauche de ton clavier.
#Le jeu 2048 se joue sur une grille de 4 x 4 cases, mais tu peux changer cela. Dans le fichier grid.h, à la ligne 12, il suffit de remplacer 4 par le nombre que tu veux. 

#Plusieurs solutions s'offrent à toi:

#Tu veux jouer de suite en mode "rustique"/terminal:
#dans ton terminal, ces commandes, tu taperas.
make
./jeu


#Tu veux jouer de suite mais avec une manifique interface graphique:
#Toujours dans ton terminal, ces commandes, tu taperas.
gcc grid.c graph.c -g -Wall -std=c99 -lSDL2 -lSDL2_ttf -o graph
./graph


#Tu veux organiser un tournois d'Intelligences Artificelles qui jouent à ta place:
./tournament


#Si tu veux étudier nos codes pour faire une IA plus performante, il faut aller dans le dossier stratégie:

#Pour tester la stratégie rapide en interne:
gcc -std=c99 grid.c strategy.c test-strat.c fast.c -o test-strat
# et lors d'un tournois:
gcc -std=c99 -fPIC -c fast.c -o fast.o
gcc -shared -Wl,-soname,libA1_almyre_chambres_mahazoasy_petureau_fast.so.1 -o libA1_almyre_chambres_mahazoasy_petureau_fast.so *.o

#Pour tester la stratégie efficace en interne:
gcc -std=c99 grid.c strategy.c test-strat.c efficient.c -o test-strat
# et lors d'un tournois:
gcc -std=c99 -fPIC -c efficient.c -o efficient.o
gcc -shared -Wl,-soname,libA1_almyre_chambres_mahazoasy_petureau_efficient.so.1 -o libA1_almyre_chambres_mahazoasy_petureau_efficient.so *.o

#Les dossiers fonts (qui gère les polices) et sprites (qui gère le fond) sont obligatoires pour le mode graphique.
#le dossier "fichier lateX" permet de voir l'évolution de notre travail.
