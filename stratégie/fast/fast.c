//Le fichier fast.c qui est premet d'effectuer la stratégie rapide

//fonctionne parfaitement

#include "strategy.h"
#include <stdlib.h>
#include <assert.h>
#include "fast.h"
#include <time.h>

//La fonction stratFast est l'algorithme principal de la stratégie rapide
//On a choisi une serie constante de déplacement
dir stratFast(strategy s, grid g) {
	//on essaye toujours d'avoir la plus grose valeur en bas à droite
	dir d=RIGHT;
	if (can_move(g,d))
		return d;
	
	d=DOWN;
	if (can_move(g,d))
		return d;	

	d=LEFT;
	if (can_move(g,d))
		return d;

	d=UP;
	return d;
	}





//La fonction A1_almyre_chambres_mahazoasy_petureau_fast est le constructeur de la stratégie.
strategy A1_almyre_chambres_mahazoasy_petureau_fast() {
	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. Cette ligne permet d'initiliser la fonction time (de la bibliothèque time.h).
	
	strategy s = malloc(sizeof(struct strategy_s));
	assert(s!=NULL);
	
	s->name = "fast";
	s->mem = NULL;
	s->play_move = stratFast;
	s->free_strategy = free_memless_strat;
	
	return s;
}
