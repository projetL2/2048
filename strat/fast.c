#include "strategy.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "fast.h"

//constructeur de s

dir stratFast(strategy s, grid g) {

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

strategy fastInit() {
	
	strategy s = malloc(sizeof(struct strategy_s));
	assert(s!=NULL);
	
	s->name = "fast";
	s->mem = NULL;
	s->play_move = stratFast;
	s->free_strategy = free_memless_strat;
	
	return s;
}
