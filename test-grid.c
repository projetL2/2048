//fichier test-grid.c
#include <ncurses.h>
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include<string.h>
//ce fichier test est creer dans le but de tester la création, copie, supression et biensur l'affichage de la grille.
//ce programme à été lancer avec valgrind pour verifier les fuites de memoires.

//fonction obligatoire pour tester notre grille et son affichage
void afficher (grid g) {

  clear();   //fonction de ncurses qui rafraichit l'affichage  
	int i=0;
	char base[6*GRID_SIDE]="";
	strcat(base," ");
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
        //printw ("\n +~~~~+~~~~+~~~~+~~~~+ \n ");
	printw("\n");
	printw(base);
    }

    printw ("Votre score est de %lu points\n", grid_score(g));
    
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
	
	initscr();  // initialisation de ncurses
	keypad(stdscr, TRUE);  // on active le clavier
	noecho();  // le choix utilisateur ne sera pas affiché
	
	int a; // variable int qui contient le choix utilisateur
	//int b;
	dir d; // la direction qui va correspondre

	add_tile(g);
	afficher(g);
	
	while(1) { // boucle de jeu
	  a = getch(); // récupère dans a le code de la touche appuyée		
		switch (a){  // switch qui fait correspondre l'int au dir
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
		play(g,d);
		afficher(g);
		
		if(game_over(g)) {    // on verifie si on a perdu
			
			do {
				clear();
				afficher(g);
				printw("GAME OVER\nVotre score : %d\nq : quitter\nr : rejouer\n", grid_score(g));   // on affiche le score et les choix
				a=getch();
				
				if(a=='q') { 				// si l'utilisateur appuie sur q
					   
					endwin(); // arrete la fenetre ncurses
					return EXIT_SUCCESS; // fin du programme
				}
				
				else if (a=='r') {			// si l'utilisateur appuie sur r
					
					delete_grid(g);
					grid g = new_grid();		// on supprime la grille et on en crée une nouvelle
					add_tile(g);
					afficher(g);
				}
			}	
			while(game_over(g));			// si game_over n'est plus vrai on retourne dans la boucle de jeu
		}	
	}
}
