//fichier jeu.c
#include <ncurses.h>
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include<string.h>

void afficher (grid g) {

  clear();   //fonction de ncurses qui rafraichit l'affichage  
	int i=0;
	char base[6*GRID_SIDE]="";
	strcat(base," ");
//creation d'une boucle pour un affichage adapté à la taille donnée dans le point h
  while(i<GRID_SIDE){
	strcat(base,"+~~~~");
	i++;
	}
	strcat(base,"+ \n ");
 	printw (base);
    
    for (int ligne=0; ligne<GRID_SIDE; ++ligne) {
        printw("|");
		for (int colonne=0; colonne<GRID_SIDE; ++colonne) {
            tile res = (get_tile (g,colonne,ligne));
            if (res == 0)
                printw ("    |");
            else
                printw ("%4d|",res); //on reserve la place de 4chiffres quel que soit le nombre réel de la tile. 
        }
       	printw("\n");
	printw(base);
    }

    printw ("Votre score est de %lu points\n", grid_score(g));
    
}


int main (void) {

	grid g = new_grid (); //creation d'une nouvelle grille
	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. cette ligne permet d'initiliser la fonction time (de la bibliotheque time.h)
	
	
	//***************************//
	//Boucle de jeu              //
	//***************************//
	
	initscr();  // initialisation de ncurses
	keypad(stdscr, TRUE);  // on active le clavier
	noecho();  // le choix utilisateur ne sera pas affiché
	
	int a; // variable int qui contient le choix utilisateur
	dir d; // la direction qui va correspondre

	add_tile(g);
	afficher(g);
	
	while(1) { // boucle de jeu
		
	  a = getch(); // récupère dans a le code de la touche appuyée		
		switch (a){  // switch qui fait correspondre l'int à la direction
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
		
		play(g,d);			// on joue et on réaffiche la grille à chaque tour de boucle
		afficher(g);
		
		if(game_over(g)) {    // on verifie si on a perdu
			
			do {
				clear();		// on fait un do while afin de pouvoir revenir à ce stade si le joueur appuie sur une touche non valide
				afficher(g);
				printw("GAME OVER\nVotre score : %d\nq : quitter\nr : rejouer\n", grid_score(g));   // on affiche le score et les choix
				a=getch();		// choix du joueur
				
				if(a=='q') { 				// si l'utilisateur appuie sur q
					   
					endwin(); // arrete la fenetre ncurses
					return EXIT_SUCCESS; // fin du programme
				}
				
				else if (a=='r') {			// si l'utilisateur appuie sur r
					
					delete_grid(g);
					grid g = new_grid();		// on supprime la grille et on en crée une nouvelle ce qui fera de nouveau renvoyer false à game_over
					add_tile(g);			// on prépare de nouveau le terrain avant de retourner dans la boucle de jeu
					afficher(g);
				}
			}	
			while(game_over(g));			// si game_over n'est plus vrai on retourne dans la boucle de jeu
		}	
	}
}
