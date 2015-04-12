//Le fichier efficient.c qui est premet d'effectuer la stratégie lente

#include "strategy.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "efficient.h"
#include "grid.h"

//les fonctions de calculs de l'évaluation:
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
 
 
// calcul de minimum 
int min(int v1, int v2){ 
	 if(v1<=v2)
		return v1;
	return v2;
}

// les fonctions suivantes sont utilisées pour calculer M 
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

//calcul de M
int calculM(grid g){
	return ( (min(calculSUP_i(g),calculINF_i(g))) + (min(calculSUP_j(g),calculINF_j(g))) );
}

//calcul de L
int calculL(grid g){
	double val1=0;		
	double val2=0;		

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

// évaluation de la qualité d'une grille
int evaluation(grid g){
	return ( (2*calculL(g)) + (2*calculUS(g)) + (6*calculM(g)) );
}	

// fonction de tri de tableau d'évaluation dans l'ordre croissant, avec mise à jour du tableau
// de mouvements en même temps
void triTableau(int* tabEval, dir* tabMouv, int tabSize) {
        
	int tmp = 0;
        
	for(int i=0; i <tabSize ; i++) {
		for(int j=i+1; j<tabSize; j++){                
			if(min(tabEval[i],tabEval[j])==tabEval[j]) {
				tmp = tabEval[i];
				tabEval[i] = tabEval[j];
				tabEval[j] = tmp;
										
				tmp = tabMouv[i];
				tabMouv[i] = tabMouv[j];
				tabMouv[j] = tmp;
			}
		}
	}
}

//La fonction stratEfficient est l'algorithme principal de la stratégie lente
dir stratEfficient(strategy s, grid g) {
	
	//on crée un tableau d'évaluations
	int* tabEval = malloc(sizeof(int));		
	assert(tabEval!=NULL);

	//on crée un tableau où l'on va strocker les directions
	dir* tabMouv = malloc(4*sizeof(dir));
	assert(tabMouv!=NULL);

	//on crée une grille temporaire pour évaluer le resultat de chaques déplacements
	grid tmp = new_grid();
	copy_grid(g, tmp);			
	
	//On effectue un mouvement que l'on place dans tabMouv 
	//On place le résultat de l'evaluation de ce mouvement dans tabEval

	tabMouv[0]=UP;
	tabMouv[1]=DOWN;
	tabMouv[2]=RIGHT;
	tabMouv[3]=LEFT;

	int tabSize = 0;

	for(int i=0; i<4; i++) {	// on crée un tableau assez grand pour contenir l'évaluation de tous les mouvements possibles
		if(can_move(g,tabMouv[i])) {
			tabEval = realloc(tabEval, sizeof(int)*(tabSize+1));
			assert(tabEval!=NULL);
			play(tmp, tabMouv[i]);
			tabEval[tabSize]=evaluation(tmp);
			copy_grid(g,tmp);
			tabMouv[tabSize]=tabMouv[i];
			tabSize ++;
		}
	}
	
	tabMouv = realloc(tabMouv, sizeof(dir)*tabSize);
	assert(tabMouv!=NULL);

	dir tmpDir;
	
	delete_grid(tmp);	
	
	// On trie le tableau pour pouvoir renvoyer la direction qui a la plus petite évaluation
	
	triTableau(tabEval, tabMouv, tabSize);
	
	tmpDir=tabMouv[0];
	free(tabMouv);
	free(tabEval);
	return tmpDir;
}
	
//La fonction A1_almyre_chambres_mahazoasy_petureau_efficient est le constructeur de la stratégie lente.	
strategy A1_almyre_chambres_mahazoasy_petureau_efficient() {
	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. Cette ligne permet d'initiliser la fonction time (de la bibliothèque time.h).
	strategy s = malloc(sizeof(struct strategy_s));
	assert(s!=NULL);
	
	s->name = "efficient";
	s->mem = NULL;
	s->play_move = stratEfficient;
	s->free_strategy = free_memless_strat;
	
	return s;
}
