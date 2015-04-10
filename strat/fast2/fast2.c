//Le fichier fast2.c qui est premet d'effectuer la stratégie rapide

//fonctionne parfaitement mais fait pas des scores très haut

#include "strategy.h"
#include <stdlib.h>
#include <assert.h>
#include "fast2.h"
#include <time.h>

//La fonction stratFast est l'algorithme principal de la stratégie rapide
// l'agorythme implémenté si est un "mix" entre 2 stratégies: acoller 2 grosses valeurs et faire essayer de faire fixe une même suite de direction.
dir stratFast(strategy s, grid g) {

	//on cherche les 2 plus grosses valeurs et leurs possitions
	int valMax1=0;
	int ligne1=0;
	int colonne1=0;

	int valMax2=0;
	int ligne2=0;
	int colonne2=0;
	
	//on cherche les plus grosses valeurs
	for (int colonne=0; colonne<GRID_SIDE; ++colonne)
		for (int ligne=0; ligne<GRID_SIDE; ++ligne){
			if (get_tile(g,colonne,ligne)<valMax1){
				valMax1=get_tile(g,colonne,ligne);// la plus grosse valeur
				ligne1=ligne;
				colonne1=colonne;
				}
			else
				if (get_tile(g, colonne, ligne)<valMax2){
					valMax2=get_tile(g,colonne, ligne);// la 2eme plus grosse valeur
					ligne2=ligne;
					colonne2=colonne;
					}
		}
	// on calcul la différence sur la hauteur de la grille
	int valLigne=abs(ligne1-ligne2);
	//on calcul la différence sur la largeur de la grille
	int valColonne=abs(colonne1-colonne2);
	
	dir d=RIGHT;// on initialise à une valeur pour commencer.
	if (valColonne>valLigne){	// si la plus grande différence est sur la largeur de la grille
		if (can_move(g,d))
			return d;
		d=LEFT;
		if (can_move(g,d))	// on essaye l'autre direction "logique"
			return d;
		d=DOWN;			//pour ne pas rester bloquer
		if (can_move(g,d))
			return d;	
		d=UP;
		return d;
		}
	else	// si la plus grande différence est sur la hauteur de la grille
		d=DOWN;
		if (can_move(g,d))
			return d;	
		d=UP;	// on essaye l'autre direction "logique"
		if (can_move(g,d))
			return d;
		d=RIGHT;	// on ne veut pas etre bloquer
		if (can_move(g,d))
			return d;
		d=LEFT;
		return d;
	
	return d;
}


//La fonction A1_almyre_chambres_mahazoasy_petureau_fast est le constructeur de la stratégie.
strategy A1_almyre_chambres_mahazoasy_petureau_fast2() {

	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. Cette ligne permet d'initiliser la fonction time (de la bibliothèque time.h).
	
	strategy s = malloc(sizeof(struct strategy_s));
	assert(s!=NULL);
	
	s->name = "fast2";
	s->mem = NULL;
	s->play_move = stratFast;
	s->free_strategy = free_memless_strat;
	
	return s;
}
