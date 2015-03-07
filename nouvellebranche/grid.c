//fichier grid.c
#include "grid.h"
#include <stdlib.h>
#include <assert.h>


// La structure de la grille, un pointeur de pointeur qui nous donnera la matrice
// et un unsigned long int score
struct grid_s {
    unsigned long int score;
    tile** grid;
};

//Le constructeur, on initialise le score à 0
//et on fait des malloc pour la struct et la grille
grid new_grid () {

    grid g = malloc(sizeof(struct grid_s));
    assert (g!=NULL);

    g->score=0;
    g->grid = malloc(GRID_SIDE * sizeof(tile*));
    assert (g->grid!=NULL);

    for (int i=0; i<GRID_SIDE; ++i) {
        g->grid[i] = malloc (GRID_SIDE * sizeof(tile));
        assert (g->grid[i]!=NULL);
    }

    return g;
}

//Destructeur de la grille, on libère d'abord les zones mémoire pointées par la variable grid puis la grille elle-même
void delete_grid (grid g) {

    for (int i=0; i<GRID_SIDE; ++i)
        free(g->grid[i]);
    free(g->grid);
    free(g);
}

//Constructeur par copie de grid
void copy_grid (grid src, grid dst) {

    dst->score = src->score;

    for (int i=0; i<GRID_SIDE; ++i)
        for (int j=0; j<GRID_SIDE; ++j)
	  set_tile(dst,i,j,get_tile(src,i,j)); //On initialise la tuile de dst avec la valeur de celle de src 

}

//Accesseur qui retourne le score
unsigned long int grid_score (grid g) {

    return g->score;
}

//Accesseur qui renvoie une tile en fonction des coordonnées en paramètres
tile get_tile (grid g, int x, int y) {

    if ((x>=0 && x<=GRID_SIDE) && (y>=0 && y<=GRID_SIDE))
        return g->grid[x][y];
    else
        return -1; // solution temporaire pour avoir toujours un return
}

//Accesseur qui instancie la valeur d'une tile en fonction des coordonnées et de la valeur en paramètres
void set_tile (grid g, int x, int y, tile t) {

    g->grid[x][y] = t;
}

//Fonction booléene qui renvoie true si le joueur peut effectuer un movement dans une direction
bool can_move (grid g, dir d) {

    // on vérifie la direction demandée (d)
    // suivant cette dernière, on parcourt la grille pour voir si on peut déplacer ou fusionner,
    //si oui, on renvoie true
    switch (d) {

      case LEFT:
      for (int ligne=0; ligne<GRID_SIDE; ++ligne)
      	for (int colonne=1; colonne<GRID_SIDE; ++colonne)
      	  if ( get_tile(g,colonne,ligne) != 0) //si case pleine,
      	    if( (get_tile(g,colonne-1,ligne) == 0) |  (get_tile(g,colonne-1,ligne) == get_tile(g,colonne,ligne)) ) // alors on regarde si case suivante vide ou fusion possible
      	      return true;
      break;

    /* case LEFT: */
    /*   for (int colonne=1; colonne<GRID_SIDE; ++colonne){ */
    /*   	for (int ligne=0; ligne<GRID_SIDE; ++ligne){ */
    /*   	  if ( get_tile(g,ligne,colonne) != 0){ //si case pleine, */
    /*   	    if( (get_tile(g,ligne,colonne-1) == 0) |  (get_tile(g,ligne,colonne-1) == get_tile(g,ligne,colonne)) ) // alors on regarde si case suivante vide ou fusion possible */
    /*   	      return true; */
    /*   	  } */
    /*   	} */
    /*   } */
    /*   return false; */
    /*   break; */

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
    // Si le mouvement demandé est impossible, on renvoie false
    return false;
}

//Fonction booléenne qui renvoie TRUE si aucun mouvement n'est plus possible.
bool game_over(grid g) {

    if ( !can_move(g,UP) && !can_move(g,DOWN) &&
	 !can_move(g,LEFT) && !can_move(g,RIGHT))
        return true;

    else
        return false;
}

//Fonction qui déplace les tiles de la grid si le mouvement est possible
void do_move (grid g, dir d) {

  if (can_move(g,d)) {
        
        switch (d) {

        case LEFT:
	  for (int colonne = 0; colonne<GRID_SIDE; ++colonne) {	// on parcourt de gauche à droite
                for (int ligne = 1; ligne<GRID_SIDE; ++ligne) {   // et de haut en bas
		  if (get_tile(g,colonne,ligne) != 0) { // si la case n'est pas vide
		    if (get_tile(g,colonne-1,ligne) == 0) {  // si la case de gauche est vide, on décale la case actuelle
		      set_tile(g,colonne-1,ligne,get_tile(g,colonne,ligne));
		      set_tile(g,colonne,ligne,0);
                            colonne-=2; // on décrémente i au cas où il y ait à déplacer la tile plusieurs fois
                        }
		    else if (get_tile(g,colonne,ligne) == get_tile(g,colonne-1,ligne)) { // s'il doit y avoir une fusion
			set_tile(g,colonne,ligne,0);
			set_tile(g,colonne-1,ligne,(get_tile(g,colonne-1,ligne)*2));				// on vide la case actuelle et on double la valeur de celle qu'elle a heurté
			g->score += get_tile(g,colonne-1,ligne);		// on actualise le score
                        }
                    
                }
	  }

            break;

        case RIGHT:
            for (int ligne=0; ligne<GRID_SIDE; ++ligne) {// on parcourt de droite à gauche
                for (int colonne = GRID_SIDE-2; colonne>=0; --colonne) { // et haut en bas
		  if (get_tile(g,colonne,ligne) != 0 && colonne < 3) { 
		    if (get_tile(g,colonne+1,ligne) == 0) {  
		      set_tile(g,colonne+1,ligne,get_tile(g,colonne,ligne));
		      set_tile(g,colonne,ligne,0);
                            colonne+=2; 
                        }
		    else if (get_tile(g,colonne,ligne) == get_tile(g,colonne+1,ligne)) { 
			set_tile(g,colonne,ligne,0);
			set_tile(g,colonne-1,ligne,(get_tile(g,colonne+1,ligne)*2));
                        g->score += get_tile(g,colonne+1,ligne);		
                        }
                    
                }
            }
            break;

	    case DOWN: //RE ECRIRE EN UTILISANT LES ACCESSEURS
	  for (int colonne=0; colonne<GRID_SIDE; ++colonne) { // on parcourt de gauche à droite
	    for (int ligne = GRID_SIDE-2; ligne>=0; --ligne)  {// de bas en haut
                    if (g->grid[colonne][ligne] != 0 && ligne < 3) {		
                        if (g->grid[colonne][ligne+1] == 0) {		
                            g->grid[colonne][ligne+1] = g->grid[colonne][ligne];
                            g->grid[colonne][ligne] = 0;
                            ligne+=2; 
                        }
                        else if (g->grid[colonne][ligne+1] == g->grid[colonne][ligne]) {
                            g->grid[colonne][ligne] = 0;
                            g->grid[colonne][ligne+1] *= 2;
                            g->score += g->grid[colonne][ligne+1];
                        }
                    }
	    }
	  }
            break;
	    
	    case UP: //RE ECRIRE EN UTILISANT LES ACCESSEURS
	  for (int colonne=0; colonne<GRID_SIDE; ++colonne) {
	    for (int ligne=0; ligne<GRID_SIDE-1; ++ligne) {
	      if (g->grid[colonne][ligne] != 0) {
		if (g->grid[colonne][ligne-1] == 0) {
		  g->grid[colonne][ligne-1] = g->grid[colonne][ligne];
		  g->grid[colonne][ligne]=0;
		  ligne-=2;
		}
		else if (g->grid[colonne][ligne+1] == g->grid[colonne][ligne]) {
		  g->grid[colonne][ligne] = 0;
		  g->grid[colonne][ligne] *= 2;
		  g->score += g->grid[colonne][ligne-1];
		}
	      }
	    }
	  }
	  break;
        }
	  }
	}
  }
  else
    return;
}
// fonction qui ajoute une tile de fonction aléatoire dans une case vide de la grid
void add_tile (grid g) {
// il faut creer une structure avec une liste des cases vide et faire le random sur cette liste
// peut etre avec un tableau de int avec le 1er chiffre la colonne et  2 eme chiffre la colonne

	int numberRand = rand()%10; //entier aléatoire entre 0 et 10
	
	int colonneRand = rand()%GRID_SIDE;// choix d'une colonne aléatoirement
	int ligneRand = rand()%GRID_SIDE; // choix d'une ligne aléatoirement

	while(g->grid[colonneRand][ligneRand]!=0) { // si la case est occupé on refait des random jusqu'a en trouver une vide.
		colonneRand = rand()%GRID_SIDE;
		ligneRand = rand()%GRID_SIDE;
	}

	if(numberRand == 9)// 4 doit avoir une chance sur 10 d'etre choix, on a prit le chiffre 9 de façon arbitraire, fallait choisir un chiffre!
		set_tile(g,colonneRand,ligneRand,4);
	else
		set_tile(g,colonneRand,ligneRand,2);
}

// fonction qui doit récuperer les instruction du joueur 
void play (grid g, dir d) {

    if(can_move(g,d)) { // si on peut jouer
        do_move(g,d);  // on joue: on effectue le deplacement
        add_tile(g);    // on ajoute une tile
    }
}
