// Stratégie facile basée sur du jeu aléatoire.

#include <ncurses.h>  
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "strategy.h"
#include "efficient.h"

void afficher (grid g) {

	clear();   // Fonction de ncurses qui rafraîchit l'affichage.
	int i=0;
	char base[5*GRID_SIDE+6]="";	// On crée une chaine de caractères base qui va contenir les barres horizontales de la grille.
	strcat(base," ");
	
	// Création d'une boucle pour un affichage adapté à la taille donnée dans le point h.
	while(i<GRID_SIDE){			// On répète le motif GRID_SIDE fois dans la chaîne base.
		strcat(base,"+~~~~");
		i++;
	}
	
	strcat(base,"+ \n ");		// A la fin de la ligne, on fait un retour à la ligne.
 	printw (base);
    
    // Boucle d'affichage de l'intérieur de la grille.
    for (int ligne=0; ligne<GRID_SIDE; ++ligne) {
        printw("|");
		for (int colonne=0; colonne<GRID_SIDE; ++colonne) {
            tile res = (get_tile (g,colonne,ligne));
            if (res == 0)
                printw ("    |");		// Si la tile vaut 0, on n'écrit rien, pour plus de lisibilité.
            else
                printw ("%4d|",res); // On résèrve la place pour 4 chiffres quel que soit le nombre réel de la tile. 
        }
       	printw("\n");
       	
	printw(base);		// A chaque tour de boucle, on affiche la chaîne base.
    }

    printw ("Votre score est de %lu points\n", grid_score(g)); // Affichage du score.
    
}
	
int main (void) {

	grid g = new_grid (); // Création d'une nouvelle grille.
	strategy s = efficientInit(); // strategy s = efficientInit(); //ligne à changer pour tester la stratégie voulue
	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. Cette ligne permet d'initiliser la fonction time (de la bibliothèque time.h).
	
	
	//***************************//
	//		Boucle de jeu        //
	//***************************//
	
	initscr();  // Initialisation de la bibliothèque ncurses.
	//keypad(stdscr, TRUE);  // On active le clavier.
	//noecho();  // Le choix utilisateur ne sera pas affiché.
	
	//int a; // Variable int qui contient le choix utilisateur.
	//dir d; // Variable dir qui contient la direction qui va correspondre à a.

	add_tile(g);
	add_tile(g);	// Premier affichage de la grille, avec une valeur à l'intérieur.
	afficher(g);
	
	while(1) { // Boucle de jeu.
		
		play(g, (s->play_move)(s,g));			// On joue et on réaffiche la grille à chaque tour de boucle.
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
				s-> free_strategy(s);
				delete_grid(g);
				return EXIT_SUCCESS; // Fin du programme.
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
	}	
}	
				
