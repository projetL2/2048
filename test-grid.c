// Fichier test-grid.c

#include <ncurses.h>
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// Ce fichier test est créé dans le but de tester la création, copie, supression et bien sûr l'affichage de la grille.
// Ce programme a été lancé avec valgrind pour vérifier les fuites de mémoire.

// Fonction obligatoire pour tester notre grille et son affichage.
void afficher (grid g) {

	clear();   // Fonction de ncurses qui rafraîchit l'affichage.
	int i=0;
	char base[5*GRID_SIDE+6]="";  // On crée une chaine de caractères base qui va contenir les barres horizontales de la grille.
	strcat(base," ");
	
	// Création d'une boucle pour un affichage adapté à la taille donnée dans le point h.
	while(i<GRID_SIDE){		// On répète le motif GRID_SIDE fois dans la chaîne base.
		strcat(base,"+~~~~");	
		i++;
	}
	
	strcat(base,"+ \n ");   // A la fin de la ligne, on fait un retour à la ligne.
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
       	
	printw(base);	// A chaque tour de boucle, on affiche la chaîne base.
    }

    printw ("Votre score est de %lu points\n", grid_score(g));  // Affichage du score.
}

int main (void) {

	grid g = new_grid (); // Création d'une nouvelle grille.
	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. Cette ligne permet d'initiliser la fonction time (de la bibliothèque time.h).
	
	//***********************************************************************//
	//Test de l'ajout de façon aléatoire (présent pour pour les autres tests)//
	//***********************************************************************//
	
	/*afficher(g);
	add_tile(g);
	afficher(g);*/

	//******************//
	//Test de copy_grid //
	//******************//
	
	/*printf("on essaye de copier la grille \n");
	afficher (g);
	grid gBis= new_grid();
	copy_grid (g,gBis);
	afficher (gBis);*/

	//*******************************************//
	//Test de delete (avec valgrind au lancement)//
	//*******************************************//
	
	/*printf("on essaye de supprimer les 2 grilles, d'abords g \n");
	delete_grid(g);
	printf("on a supprimé g, on supprime gBis\n");
	delete_grid(gBis);
	printf("on a fini\n");*/

	//*************************************************************************//
	//Test des mouvements de façon aléatoire (le hasard choisit toujours mieux)//
	//*************************************************************************//
	
	/*printf("on rentre dans la boucle de test des mouvements\n");	
	for(int i = 0; i<10; i++) { // Création d'une boucle pour tester add_tile.
			
		int dirRand= rand()%3; // Variable pour choisir la direction de façon aléatoire.
		printf("le mouvement que l'on va faire est %d (0->droite, 1->bas, 2->haut, 3->gauche) \n", dirRand);
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
		printf("on est au tour %d\n",i);
	}
	printf("on est sorti de la boucle");*/

	//***************************************************************************************************//
	//Test sur les acceptations (ou non) de mouvements de can_move et les mouvements réellement effectués//
	//***************************************************************************************************//
	
	// add_tile remplit une case de façon aléatoire, on demande un mouvement en particulier.
	// A nous visuellement de vérifier si can_move devait l'accepter ou non.
	// Tester tour à tour avec RIGHT, DOWN, UP et LEFT.
	
	/*if(can_move(g,RIGHT)){ 
    		do_move(g,RIGHT);
   		add_tile(g);
    		printf("\n le mouvement est valide \n \n");
   
  	}*/

	//******************//
	//Test de game over //
	//******************//
	
	/*
	for (int colonne=0; colonne<GRID_SIDE; ++colonne){
		for (int ligne=0; ligne<GRID_SIDE; ++ligne){
			set_tile (g,colonne, ligne, colonne+ligne+1); // colonne+ligne donnera un nombre différent à chaque fois.
			}
		}
	afficher(g);
	int dirRand= rand()%4; // Variable pour choisir la direction de façon aléatoire
		printf("le mouvement que l'on va faire est %d (0->droite, 1->bas, 2->haut, 3->gauche) \n", dirRand);
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
	
	initscr();  // Initialisation de la bibliothèque ncurses.
	keypad(stdscr, TRUE);  // On active le clavier.
	noecho();  // Le choix utilisateur ne sera pas affiché.
	
	int a; // Variable int qui contient le choix utilisateur.
	dir d; // Variable dir qui contient la direction qui va correspondre à a.
	
	add_tile(g);	// Premier affichage de la grille, avec une valeur à l'intérieur.
	afficher(g);
	
	while(1) {  // Boucle de jeu.
		
	  a = getch(); // Récupère dans a le code de la touche appuyée.		
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
		
		play(g,d);		// On joue et on réaffiche la grille à chaque tour de boucle.
		afficher(g);
		
		if(game_over(g)) {    // On vérifie si on a perdu.
			
			do {
				clear();		// On fait un do while afin de pouvoir revenir à ce stade si le joueur appuie sur une touche non valide.
				afficher(g);
				printw("GAME OVER\nVotre score final est de : %d\nq : quitter\nr : rejouer\n", grid_score(g));   // On affiche le score et les choix.
				a=getch();		// Choix du joueur.
				
				if(a=='q') { 	// Si l'utilisateur appuie sur q,
					   
					endwin(); // arrêt de la fenêtre ncurses.
					return EXIT_SUCCESS; // Fin du programme.
				}
				
				else if (a=='r') {	// Si l'utilisateur appuie sur r,
					
					delete_grid(g);
					grid g = new_grid();	// on supprime la grille et on en crée une nouvelle ce qui fera de nouveau renvoyer false à game_over.
					add_tile(g);	// On prépare de nouveau le terrain avant de retourner dans la boucle de jeu.
					afficher(g);
				}
			}	
			while(game_over(g));	// Si game_over n'est plus vrai on retourne dans la boucle de jeu.
		}	
	}
}
