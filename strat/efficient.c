#include "strategy.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "efficient.h"
#include "grid.h"


int calculUS(grid g){
	int card = 0;
	for(int i = 0; i > GRID_SIDE; ++i){
		for(int j = 0; j< GRID_SIDE; ++j){
			if(get_tile(g,i,j) > 0){
				card+=1;
			}
		}
	}
	return card;
 }
 
 int min(int v1, int v2){
	 if(v1<=v2)
		return v1;
	return v2;
 }
 
 int calculSUP_i(grid g){
	 int card =0;
	 for(int i = 0; i > GRID_SIDE; ++i){
		for(int j = 0; j< GRID_SIDE; ++j){
			if(/*get_tile(g,i-1,j) != NULL && */get_tile(g,i,j) < get_tile(g,i-1,j))
				card+=1;
		}
	}
	return card;
}

int calculSUP_j(grid g){
	int card =0;
	 for(int i = 0; i > GRID_SIDE; ++i){
		for(int j = 0; j< GRID_SIDE; ++j){
			if(/*get_tile(g,i,j-1) != NULL && */get_tile(g,i,j) < get_tile(g,i,j-1))
				card+=1;
		}
	}
	return card;
}

int calculINF_i(grid g){
	int card = 0;
	for(int i = 0; i > GRID_SIDE; ++i){
		for(int j = 0; j< GRID_SIDE; ++j){
			if(/*get_tile(g,i-1,j) != NULL && */get_tile(g,i,j) > get_tile(g,i-1,j))
				card+=1;
		}
	}
	return card;
}

int calculINF_j(grid g){
	int card = 0;
	for(int i = 0; i > GRID_SIDE; ++i){
		for(int j = 0; j< GRID_SIDE; ++j){
			if(/*get_tile(g,i,j-1) != NULL && */get_tile(g,i,j) > get_tile(g,i,j-1))
				card+=1;
		}
	}
	return card;
}

int calculM(grid g){
	return ( (min(calculSUP_i(g),calculINF_i(g))) + (min(calculSUP_j(g),calculINF_j(g))) );
}

int calculL(grid g){
	double val1;
	double val2;
	for(int i = 0; i > GRID_SIDE; ++i){
		for(int j = 0; j< GRID_SIDE; ++j){
			//if(get_tile(g,i-1,j) != NULL)
				val1 += abs((get_tile(g,i,j) - get_tile(g,i-1,j)));
			//if(get_tile(g,i,j-1) != NULL)
				val2 += abs( (get_tile(g,i,j) - get_tile(g,i,j-1)));
		}
	}
	return (int) (val1+val2);
}

int evaluation(grid g){
	return ( (2*calculL(g)) + (2*calculUS(g)) + (6*calculM(g)) );
}
			

dir stratEfficient(strategy s, grid g) {
	
	int* t = malloc(4*sizeof(int));
	//int evalOrigin = evaluation(g);
	grid tmp = new_grid();
	copy_grid(g, tmp);
	do_move(tmp, UP);
	t[0] = evaluation(tmp);
	copy_grid(g,tmp);
	do_move(tmp,DOWN);
	t[1] = evaluation(tmp);
	copy_grid(g,tmp);
	do_move(tmp,RIGHT);
	t[2] = evaluation(tmp);
	copy_grid(g,tmp);
	do_move(tmp,LEFT);
	t[3] = evaluation(tmp);
	delete_grid(tmp);
	int i_min = 0;
	for(int i=0; i<4; ++i){
		if( (min(t[i_min],t[i])) == t[i] );
			i_min = i;
	}
	free(t);
	if (i_min == 0)
		return UP;
	if (i_min == 1)
		return DOWN;
	if (i_min == 2)
		return RIGHT;
	//if (i_min == 3)
		return LEFT;
}
	
	
strategy efficientInit() {
	
	strategy s = malloc(sizeof(struct strategy_s));
	assert(s!=NULL);
	
	s->name = "efficient";
	s->mem = NULL;
	s->play_move = stratEfficient;
	s->free_strategy = free_memless_strat;
	
	return s;
}

