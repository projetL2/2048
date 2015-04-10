#include "strategy.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "efficient.h"
#include "grid.h"


int calculUS(grid g){
	int card = 0;
	
	for(int i = 0; i < GRID_SIDE; ++i){
		for(int j = 0; j < GRID_SIDE; ++j){
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
	 for(int i = 1; i < GRID_SIDE; ++i){
		for(int j = 0; j < GRID_SIDE; ++j){
			if(get_tile(g,i,j) < get_tile(g,i-1,j))
				card+=1;
		}
	}
	return card;
}

int calculSUP_j(grid g){
	int card =0;
	 for(int i = 0; i < GRID_SIDE; ++i){
		for(int j = 1; j < GRID_SIDE; ++j){
			if(get_tile(g,i,j) < get_tile(g,i,j-1))
				card+=1;
		}
	}
	return card;
}

int calculINF_i(grid g){
	int card = 0;
	for(int i = 1; i < GRID_SIDE; ++i){
		for(int j = 0; j < GRID_SIDE; ++j){
			if(get_tile(g,i,j) > get_tile(g,i-1,j))
				card+=1;
		}
	}
	return card;
}

int calculINF_j(grid g){
	int card = 0;
	for(int i = 0; i < GRID_SIDE; ++i){
		for(int j = 1; j < GRID_SIDE; ++j){
			if(get_tile(g,i,j) > get_tile(g,i,j-1))
				card+=1;
		}
	}
	return card;
}

int calculM(grid g){
	return ( (min(calculSUP_i(g),calculINF_i(g))) + (min(calculSUP_j(g),calculINF_j(g))) );
}

int calculL(grid g){
	double val1=0;		//i c'est des colonnes
	double val2=0;		//j c'est des lignes

	for(int colonne = 1; colonne < GRID_SIDE; ++colonne){
		for(int ligne = 0; ligne < GRID_SIDE; ++ligne){
			val1 += (abs((get_tile(g,colonne,ligne) - get_tile(g,colonne-1,ligne)))) ;			
		}
	}
	for(int colonne = 0; colonne < GRID_SIDE; ++colonne){
		for(int ligne = 1; ligne < GRID_SIDE; ++ligne){
			val2 += (abs(get_tile(g, colonne,ligne))-(get_tile(g,colonne,ligne-1)));
		}
	}
	return (int) (val1+val2);
}

int evaluation(grid g){
	return ( (2*calculL(g)) + (2*calculUS(g)) + (6*calculM(g)) );
}
	
void triTableau(int* tabEval, dir* tabMouv) {
	
	int tmp = 0;
	
	for(int i=0; i < 3; i++) {
		for(int j=3; j<(i+1); j--){		
			if(min(tabEval[i],tabEval[j])==tabEval[j]) {
				tmp = tabEval[i];
				tabEval[i] = tabEval[j];
				tabEval[j] = tmp;
			
				tmp = tabMouv[i];
				tabMouv[i] = tabMouv[j];
				tabMouv[j] = tmp;
			
				i--;
			}
		}
	}
}		

dir stratEfficient(strategy s, grid g) {
	
	int* tabEval = malloc(4*sizeof(int));		// tableau d'évaluations
	assert(tabEval!=NULL);
	dir* tabMouv = malloc(4*sizeof(dir));
	assert(tabMouv!=NULL);
	dir tmpDir;
	
	grid tmp = new_grid();
	copy_grid(g, tmp);			// grille temporaire
	
	do_move(tmp, UP);			// evaluation des différents mouvements, placées dans le tableau
	tabEval[0] = evaluation(tmp);
	tabMouv[0] = UP;
	
	copy_grid(g,tmp);
	do_move(tmp,DOWN);
	tabEval[1] = evaluation(tmp);
	tabMouv[1] = DOWN;
	
	copy_grid(g,tmp);
	do_move(tmp,RIGHT);
	tabEval[2] = evaluation(tmp);
	tabMouv[3] = RIGHT;
	
	copy_grid(g,tmp);
	do_move(tmp,LEFT);
	tabEval[3] = evaluation(tmp);
	tabMouv[3] = LEFT;
	delete_grid(tmp);
	
	triTableau(tabEval, tabMouv);
	
	for(int i=0; i<4; ++i)			// on determine l'éval minimum
		if(can_move(g,tabMouv[i])) {
			tmpDir = tabMouv[i];
			free(tabMouv);
			free(tabEval);
			return tmpDir;
		}
	
	return 0;
}
	
	
strategy A1_almyre_chambres_mahazoasy_petureau_efficient() {
	
	strategy s = malloc(sizeof(struct strategy_s));
	assert(s!=NULL);
	
	s->name = "efficient";
	s->mem = NULL;
	s->play_move = stratEfficient;
	s->free_strategy = free_memless_strat;
	
	return s;
}

