#include "strategy.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "easy.h"

//constructeur de s

dir stratEasy(strategy s, grid g) { //enculé comment c'est beau

	dir d;
	
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
		
	return d;
}
/*
void free_memless_strat (strategy strat) {
	
	free (strat->name);
	free (strat);
}
*/
strategy easyInit() {
	
	strategy s = malloc(sizeof(struct strategy_s));
	assert(s!=NULL);
	
	s->name = "easy";
	s->mem = NULL;
	s->play_move = stratEasy/*(strategy s, grid g)*/;
	s->free_strategy = free_memless_strat/*(strategy strat)*/;
	
	return s;
}
