//fichier grid.c
#include "grid.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


// La structure de la grille, avec un pointeur de pointeur qui donne la matrice
// et un unsigned long int pour le score
struct grid_s {
	
    unsigned long int score;
    tile** grid;
};

//Le constructeur, qui initialise le score � 0
//et qui fait des malloc pour la structure et la grille
grid new_grid () {

    grid g = malloc(sizeof(struct grid_s));		//malloc de la struct
    assert (g!=NULL);

    g->score=0;
    g->grid = malloc(GRID_SIDE * sizeof(tile*));		// malloc du pointeur grid
    assert (g->grid!=NULL);

    for (int i=0; i<GRID_SIDE; ++i) {
        g->grid[i] = malloc (GRID_SIDE * sizeof(tile));		//malloc des pointeurs dans grid
        assert (g->grid[i]!=NULL);
    }
    
    for(int i=0; i<GRID_SIDE; ++i)		// on initialise les cases � 0
		for(int j=0; j<GRID_SIDE; ++j)
			g->grid[i][j]=0;

    return g;
}

//Destructeur de la grille,
//qui lib�re d'abord les zones m�moire point�es par la variable grid puis la grille elle-m�me
void delete_grid (grid g) {

    for (int i=0; i<GRID_SIDE; ++i)
        free(g->grid[i]);
    free(g->grid);
    free(g);
}

//Constructeur par copie de grid
void copy_grid (grid src, grid dst) {

    dst->score = src->score;			// on copie le score

    for (int i=0; i<GRID_SIDE; ++i)
        for (int j=0; j<GRID_SIDE; ++j)
            set_tile(dst,i,j,get_tile(src,i,j)); //On initialise la tile de dst avec la valeur de celle de src

}

//Accesseur qui retourne le score
unsigned long int grid_score (grid g) {

    return g->score;
}

//Accesseur qui renvoie une tile en fonction des coordonn�es pass�es en param�tres
tile get_tile (grid g, int colonne, int ligne) {

    assert((colonne>=0 && colonne<GRID_SIDE) && (ligne>=0 && ligne<GRID_SIDE));
    return g->grid[colonne][ligne]; // si la tile est dans les limites de la grille, on la renvoie
}

//Accesseur qui modifie la valeur d'une tile en fonction des coordonn�es et de la valeur pass�s en param�tres
void set_tile (grid g, int colonne, int ligne, tile t) {

    g->grid[colonne][ligne] = t;
}

//Fonction bool�enne qui renvoie true si le joueur peut effectuer un mouvement dans une direction et false sinon
bool can_move (grid g, dir d) {

    // on regarde la direction demand�e (d)
    // suivant celle_ci, on parcourt la grille pour voir si on peut, quelque part, faire un d�placement ou une fusion,
    //si oui, on renvoie true
    switch (d) {

    case LEFT:
        for (int colonne=1; colonne<GRID_SIDE; ++colonne)
            for (int ligne=0; ligne<GRID_SIDE; ++ligne)
                if ( get_tile(g,colonne,ligne) != 0) //si case pleine,
                    if( (get_tile(g,colonne-1,ligne) == 0) || (get_tile(g,colonne-1,ligne) == get_tile(g,colonne,ligne)) ) // alors on regarde si case suivante vide ou fusion possible
                        return true;
        break;

    case RIGHT:
        for (int colonne=0; colonne<GRID_SIDE-1; ++colonne)
            for (int ligne=0; ligne<GRID_SIDE; ++ligne)
                if( get_tile(g,colonne,ligne) != 0)
                    if ( (get_tile(g,colonne+1,ligne) == 0) || (get_tile(g,colonne+1,ligne) == get_tile(g,colonne,ligne)))
                        return true;
        break;

    case UP:
        for (int colonne=0; colonne<GRID_SIDE; ++colonne)
            for (int ligne=1; ligne<GRID_SIDE; ++ligne)
                if( get_tile(g,colonne,ligne) != 0)
                    if ( (get_tile(g,colonne,ligne-1) == 0) || (get_tile(g,colonne,ligne-1) == get_tile(g,colonne,ligne)) )
                        return true;
        break;

    case DOWN:
        for (int colonne=0; colonne<GRID_SIDE; ++colonne)
            for (int ligne=0; ligne<GRID_SIDE-1; ++ligne)
                if( get_tile(g,colonne,ligne) != 0)
                    if ( (get_tile(g,colonne,ligne+1) == 0) || (get_tile(g,colonne,ligne+1) == get_tile(g,colonne,ligne)) )
                        return true;
        break;
    }
    // Si le mouvement demand� est impossible, on renvoie false
    return false;
}

//Fonction bool�enne qui renvoie TRUE si aucun mouvement n'est plus possible.
bool game_over(grid g) {

    if ( !can_move(g,UP) && !can_move(g,DOWN) &&
            !can_move(g,LEFT) && !can_move(g,RIGHT))
        return true;

    else
        return false;
}

//Fonction qui d�place les tiles de la grid si le mouvement est possible
void do_move (grid g, dir d) {

	int flag; // cette variable sert � indiquer une limite, quand une fusion a eu lieu, aucune fusion n'est plus possible apr�s elle 
				// pour �viter les fusions type : 0 4 4 8 *mouvement � droite* ==> 0 0 0 16
    switch (d) {

    case LEFT:
        for (int ligne = 0; ligne<GRID_SIDE; ++ligne) {	// on parcourt de haut en bas
            flag = 0;
            for (int colonne = 1; colonne<GRID_SIDE; ++colonne) {   // et de gauche � droite  
                if (get_tile(g,colonne,ligne) != 0) { // si la case n'est pas vide
                    if (get_tile(g,colonne-1,ligne) == 0) {  // si la case de gauche est vide, on d�cale la case actuelle
                        set_tile(g,colonne-1,ligne,get_tile(g,colonne,ligne));
                        set_tile(g,colonne,ligne,0);
                        if(colonne >1)
							colonne-=2; // on d�cr�mente i au cas o� il y ait � d�placer la tile plusieurs fois
                    }
                    else if (get_tile(g,colonne,ligne) == get_tile(g,colonne-1,ligne) && colonne > flag) { // s'il doit y avoir une fusion et qu'on n'a pas d�pass� notre flag
                        set_tile(g,colonne,ligne,0);
                        set_tile(g,colonne-1,ligne,(get_tile(g,colonne-1,ligne)*2));				// on vide la case actuelle et on double la valeur de celle qu'elle a heurt�
                        g->score += get_tile(g,colonne-1,ligne);		// on actualise le score
                        flag = colonne;			// il y a eu fusion, on installe le flag � cet endroit
                    }
                }
            }
        }

        break;

    case RIGHT:
        for (int ligne=0; ligne<GRID_SIDE; ++ligne) {// on parcourt de haut en bas
            flag = GRID_SIDE-1;
            for (int colonne = GRID_SIDE-2; colonne>=0; --colonne) { // et droite � gauche
                if (get_tile(g,colonne,ligne) != 0 && colonne < GRID_SIDE -1) {
                    if (get_tile(g,colonne+1,ligne) == 0) {
                        set_tile(g,colonne+1,ligne,get_tile(g,colonne,ligne));
                        set_tile(g,colonne,ligne,0);
                        colonne+=2;
                    }
                    else if (get_tile(g,colonne,ligne) == get_tile(g,colonne+1,ligne) && colonne < flag) {
                        set_tile(g,colonne,ligne,0);
                        set_tile(g,colonne+1,ligne,(get_tile(g,colonne+1,ligne)*2));
                        g->score += get_tile(g,colonne+1,ligne);
                        flag = colonne;
                    }
                }
            }
        }
        break;

    case DOWN:
        for (int colonne=0; colonne<GRID_SIDE; ++colonne) { // on parcourt de gauche � droite
			flag = GRID_SIDE-1;
            for (int ligne = GRID_SIDE-2; ligne>=0; --ligne)  {// de bas en haut
                if (get_tile(g,colonne,ligne) != 0 && ligne < GRID_SIDE -1) {
                    if (get_tile(g,colonne,ligne+1) == 0) {
                        set_tile(g,colonne,ligne+1,get_tile(g,colonne,ligne));
                        set_tile(g,colonne,ligne,0);
                        ligne+=2;
                    }
                    else if (get_tile(g,colonne,ligne) == get_tile(g,colonne,ligne+1) && ligne < flag) {
                        set_tile(g,colonne,ligne,0);
                        set_tile(g,colonne,ligne+1,get_tile(g,colonne,ligne+1)*2);
                        g->score += get_tile(g,colonne,ligne+1);
                        flag = ligne;
                    }
                }
            }
        }
        break;

    case UP:
        for (int colonne=0; colonne<GRID_SIDE; ++colonne) {		// on parcourt de gauche � droite
            flag = 0;
            for (int ligne=1; ligne<GRID_SIDE; ++ligne) {		// de haut en bas
                if (get_tile(g,colonne,ligne) != 0) {
                    if (get_tile(g,colonne,ligne-1) == 0) {
                        set_tile(g,colonne,ligne-1,get_tile(g,colonne,ligne));
                        set_tile(g,colonne,ligne,0);
                        if(ligne>1)
							ligne-=2;
                    }
                    else if (get_tile(g,colonne,ligne-1) == get_tile(g,colonne,ligne) && ligne > flag) {
                        set_tile(g,colonne,ligne,0);
                        set_tile(g,colonne,ligne-1,get_tile(g,colonne,ligne-1)*2);
                        g->score += get_tile(g,colonne,ligne-1);
                        flag = ligne;
                    }
                }
            }
        }
        break;
    }
}
// fonction qui ajoute une tile de fa�on al�atoire dans une case vide de la grid
void add_tile (grid g) {
// il faut cr�er une structure avec une liste des cases vides et faire le random sur cette liste
// peut �tre avec un tableau de int avec le 1er chiffre la colonne et  2 eme chiffre la colonne

    int numberRand = rand()%10; //entier al�atoire entre 0 et 10

    int colonneRand = rand()%GRID_SIDE;// choix d'une colonne al�atoirement
    int ligneRand = rand()%GRID_SIDE; // choix d'une ligne al�atoirement

    while(get_tile(g,colonneRand,ligneRand)!=0) { // si la case est occup�e on refait des random jusqu'a en trouver une vide.
        colonneRand = rand()%GRID_SIDE;
        ligneRand = rand()%GRID_SIDE;
    }

    if(numberRand == 9)// 4 doit avoir une chance sur 10 d'apparaitre, on a prit le chiffre 9 de fa�on arbitraire
        set_tile(g,colonneRand,ligneRand,4);
    else
        set_tile(g,colonneRand,ligneRand,2);
}

// fonction qui doit r�cup�rer les instructions du joueur
void play (grid g, dir d) {
    
    if (can_move(g,d)){  // si on peut jouer
		do_move(g,d);  // on joue: on effectue le deplacement
		add_tile(g);    // on ajoute une tile al�atoire
	}
}
