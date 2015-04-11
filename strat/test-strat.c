// Ce fichier permet de tester les stratégies et surtout de voir les printf pour débuger
 
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "strategy.h"
#include "efficient.h"

//Fonction pour voir la grille qui se joue.
void afficher (grid g) {

	int i=0;
	char base[5*GRID_SIDE+6]="";	// On crée une chaine de caractères base qui va contenir les barres horizontales de la grille.
	strcat(base," ");
	
	// Création d'une boucle pour un affichage adapté à la taille donnée dans le point h.
	while(i<GRID_SIDE){			// On répète le motif GRID_SIDE fois dans la chaîne base.
		strcat(base,"+~~~~");
		i++;
	}
	
	strcat(base,"+ \n ");		// A la fin de la ligne, on fait un retour à la ligne.
 	printf (base);
    
    // Boucle d'affichage de l'intérieur de la grille.
    for (int ligne=0; ligne<GRID_SIDE; ++ligne) {
        printf("|");
		for (int colonne=0; colonne<GRID_SIDE; ++colonne) {
            tile res = (get_tile (g,colonne,ligne));
            if (res == 0)
                printf ("    |");		// Si la tile vaut 0, on n'écrit rien, pour plus de lisibilité.
            else
                printf ("%4d|",res); // On résèrve la place pour 4 chiffres quel que soit le nombre réel de la tile. 
        }
       	printf("\n");
       	
	printf(base);		// A chaque tour de boucle, on affiche la chaîne base.
    }

    printf ("Votre score est de %lu points\n", grid_score(g)); // Affichage du score.
    
}

int main (void) {

	grid g = new_grid (); // Création d'une nouvelle grille.
	strategy s = A1_almyre_chambres_mahazoasy_petureau_efficient();
	
	//***********************************//
	//		Boucle de jeu        //
	//***********************************//

	add_tile(g);
	add_tile(g);	// Premier affichage de la grille, avec une valeur à l'intérieur.
	afficher(g);
	
	while(!game_over(g)) { // Boucle de jeu.
		play(g,s->play_move(s,g));
		afficher(g);
	}
	
	return EXIT_SUCCESS;
}
		
				
