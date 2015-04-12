// Stratégie facile basée sur du jeu aléatoire.

#include <ncurses.h>  
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "strategy.h"
//#include "fast2.h"
#include "efficient.h"


void afficher (grid g) {

	//clear();   // Fonction de ncurses qui rafraîchit l'affichage.
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
/*
int jouer(grid g, dir d){
	play(g,d);			// On joue et on réaffiche la grille à chaque tour de boucle.
	afficher(g);
				
	if(game_over(g)) {    // On vérifie si on a perdu.
					
		do {
			clear();		// On fait un do while afin de pouvoir revenir à ce stade si le joueur appuie sur une touche non valide.
			afficher(g);
			printw("GAME OVER\nVotre score final est de : %d\nq : quitter\nr : rejouer\n", grid_score(g));   // On affiche le score et les choix.
			int a;
			a=getch();		// Choix du joueur.
						
			if(a=='q') { 	// Si l'utilisateur appuie sur q,
							   
					endwin(); // arrêt de la fenêtre ncurses.
					return 0; // Fin du programme.
			}
						
			else if (a=='r') {	// Si l'utilisateur appuie sur r,
							
					delete_grid(g);
					grid g = new_grid();	// on supprime la grille et on en crée une nouvelle ce qui fera de nouveau renvoyer false à game_over.
					add_tile(g);		// On prépare de nouveau le terrain avant de retourner dans la boucle de jeu.
					afficher(g);
			}
		}	
		while(game_over(g));	// Si game_over n'est plus vrai on retourne dans la boucle de jeu.
	}
	return 1;
}
	*/
	

int main (void) {

	grid g = new_grid (); // Création d'une nouvelle grille.
	strategy s = A1_almyre_chambres_mahazoasy_petureau_efficient2();
	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. Cette ligne permet d'initiliser la fonction time (de la bibliothèque time.h).
	
	//***************************//
	//		Boucle de jeu        //
	//***************************//
	
	//initscr();  // Initialisation de la bibliothèque ncurses.
	//keypad(stdscr, TRUE);  // On active le clavier.
	//noecho();  // Le choix utilisateur ne sera pas affiché.
	
	//int a; // Variable int qui contient le choix utilisateur.
	//dir d; // Variable dir qui contient la direction qui va correspondre à a.

	add_tile(g);
	add_tile(g);	// Premier affichage de la grille, avec une valeur à l'intérieur.
	afficher(g);
	
	while(!game_over(g)) { // Boucle de jeu.
		play(g,s->play_move(s,g));
		afficher(g);
	}
	
	return EXIT_SUCCESS;
}
	
	/*	
	  //a = getch(); // Récupère dans a le code de la touche appuyée.
	  if (a=='t'){
		  while(1){
			int numberRand = rand()%3;
			switch (numberRand){  // switch qui fait correspondre l'int à la direction.
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
			if (jouer(g,d) == 0)
				return EXIT_SUCCESS;
		}
	 }
		else
			switch (a){  // switch qui fait correspondre l'int à la direction.
					case KEY_RIGHT:	
						d=RIGHT;
					break;
					case KEY_LEFT:
						d=LEFT;
					break;
					case KEY_UP:
						d=UP;
					break;
					case KEY_DOWN:
						d=DOWN;
					break;
				}
				if (jouer(g,d) == 0)
					return EXIT_SUCCESS;
			}*/
		
				
