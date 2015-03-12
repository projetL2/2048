//fichier test-grid.c
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//ce fichier test est creer dans le but de tester la création, copie, supression et biensur l'affichage de la grille.
//ce programme à été lancer avec valgrind pour verifier les fuites de memoires.

//fonction obligatoire pour tester notre grille et son affichage
void afficher (grid g) {

    printf (" +~~~~+~~~~+~~~~+~~~~+ \n ");
    
    for (int ligne=0; ligne<GRID_SIDE; ++ligne) {
        printf("|");
		for (int colonne=0; colonne<GRID_SIDE; ++colonne) {
            tile res = (get_tile (g,colonne,ligne));
            if (res == 0)
                printf ("    |"); // on affiche pas 0 pour plus de lisibilité.
            else
                printf ("%4d|",res); //on reserve la place de 4chiffres quel que soit le nombre réel de la tile. 
        }
        printf ("\n +~~~~+~~~~+~~~~+~~~~+ \n ");
    }

    printf ("Votre score est de %lu points\n", grid_score(g));
}


int main (void) {

	grid g = new_grid (); //creation d'une nouvelle grille
	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. cette ligne permet d'initiliser la fonction time (de la bibliotheque time.h)
	
	//***********************************************************************//
	//test de l'ajout de façon aléatoire (présent pour pour les autres tests)//
	//***********************************************************************//
	
	/*afficher(g);
	add_tile(g);
	afficher(g);*/

	//******************//
	//test de copy_grid //
	//******************//
	
	/*printf("on essaye de copier la grille \n");
	afficher (g);
	grid gBis= new_grid();
	copy_grid (g,gBis);
	afficher (gBis);*/

	//*******************************************//
	//test de delete (avec valgrind au lancement)//
	//*******************************************//
	
	/*printf("on essaye de supprimer les 2 grilles, d'abords g \n");
	delete_grid(g);
	printf("on a supprimé g, on supprime gBis\n");
	delete_grid(gBis);
	printf("on a fini\n");*/

	//***********************************************************************//
	//test des mouvement de façon aléatoire (le hasard choisi toujours mieux)//
	//***********************************************************************//
	
	/*printf("on rentre dans la boucle de test des mouvements\n");	
	for(int i = 0; i<10; i++) { // creation d'une boucle pour tester add_tile 
			
		int dirRand= rand()%3; // valariable pour choisir la direction de facon aléatoire
		printf("le mouvement que l'on va faire est %d (0->droite, 1->bas,2->haut,3->gauche) \n",dirRand);
		switch (dirRand){
			case 0:	
				do_move (g,RIGHT);
			break;
			case 1:
				do_move (g,DOWN);
			break;
			case 2:
				do_move(g,UP);
			break;
			case 3:
				do_move(g,LEFT);
			break;
		}
		add_tile(g);
		afficher(g);
		printf("on est au %d tours\n",i);
	}
	printf("on est sorti de la boucle");*/

	//*************************************************************************************************//
	//test sur les acceptations (ou non) de mouvement de can_move et les mouvement réellement effectués//
	//*************************************************************************************************//
	
	//add_tile remplit une case de façon aléatoire, on demande un mouvement en particulier
	// à nous visuellement de verifier si can_move devait l'accepter ou non
	// tester tour à tour avec RIGHT,DOWN, UP, LEFT
	/*if(can_move(g,RIGHT)){ 
    		do_move(g,RIGHT);
   		add_tile(g);
    		printf("\n le mouvement est valide \n \n");
   
  	}*/

	//******************//
	// test de game over//
	//******************//
	
	/*
	for (int colonne=0; colonne<GRID_SIDE; ++colonne){
		for (int ligne=0; ligne<GRID_SIDE; ++ligne){
			set_tile (g,colonne, ligne, colonne+ligne+1);//colone+ligne donnera un nombre différent à chaque fois
			}
		}
	afficher(g);
	int dirRand= rand()%4; // valariable pour choisir la direction de facon aléatoire
		printf("le mouvement que l'on va faire est %d (0->droite, 1->bas,2->haut,3->gauche) \n",dirRand);
		switch (dirRand){
			case 0:	
				dirRand=RIGHT;
			break;
			case 1:
				dirRand=DOWN;
			break;
			case 2:
				dirRand=UP;
			break;
			case 3:
				dirRand=LEFT;
			break;
		}
	play(g, dirRand);
	afficher(g);
	*/
	
	//***************************//
	//Tests d'entrées utilisateur//
	//***************************//
	
	/*
	int a; // variable int qui contient le choix utilisateur
	dir d; // la direction qui va correspondre
	
	add_tile(g);
	afficher(g);

	printf("droite = 0	gauche = 1	haut = 2	bas = 3\n"); // propositions
	
	for (int i=0; i<10; i++) { // on va boucler 10 fois pour le test
		
		scanf("%d", &a); // récupère un int dans la variable a 		
		switch (a){  // switch qui fait correspondre l'int au dir
			case 0:	
				d=RIGHT;
			break;
			case 1:
				d=LEFT;
			break;
			case 2:
				d=UP;
			break;
			case 3:
				d=DOWN;
			break;
		}
		play(g,d);
		afficher(g);
		printf("droite = 0	gauche = 1	haut = 2	bas = 3\n"); // propositions
	}
	*/
	return EXIT_SUCCESS;
}
