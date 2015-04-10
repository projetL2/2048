#include "strategy.h"
#include <stdlib.h>
#include <assert.h>
#include "fast.h"
#include <time.h>

bool testMove (grid g, dir d){
	return (can_move(g,d));
}

//constructeur de s
dir stratFast(strategy s, grid g) {
	
	dir d=RIGHT;
	if (testMove(g,d))
		return d;
	
	d=DOWN;
	if (testMove(g,d))
		return d;	

	d=LEFT;
	if (testMove(g,d))
		return d;

	else
		return UP;
	}



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
