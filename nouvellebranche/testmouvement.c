//fichier test-grid.c
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//fonction pour tester notre grille et son affichage

void afficher (grid g) {

    printf (" +~~~~+~~~~+~~~~+~~~~+ \n ");

    for (int colonne=0; colonne<GRID_SIDE; ++colonne) {
        printf("|");
        for (int ligne=0; ligne<GRID_SIDE; ++ligne) {
            tile res = (get_tile (g,colonne,ligne));
            if (res == 0)
                printf ("    |"); // on affiche pas 0 pour plus de lisibilité.
            else
                printf ("%4d|",res); //on reserve la place de 4chiffres quel que soit le nombre réel de 						// la tile. 
        }
        printf ("\n +~~~~+~~~~+~~~~+~~~~+ \n ");
    }

    printf ("Votre score est de %lu points\n", grid_score(g));
}


int main (void) {

  grid g = new_grid (); //creation d'une nouvelle grille
  srand(time (NULL)); //pour initialiser la fonction add_tile
  afficher(g);
  add_tile(g);
  afficher(g);
  if(can_move(g,LEFT)){
    //do_move(g,LEFT);
    //add_tile(g);
    printf("\n le mouvement est valide \n \n");
   
  }
  //afficher(g);

  return EXIT_SUCCESS;
}
