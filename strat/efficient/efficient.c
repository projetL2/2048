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

int evaluation(grid g){
	return ( (2*calculL(g)) + (2*calculUS(g)) + (6*calculM(g)) );
}	

//La fonction stratEfficient est l'algorithme principal de la stratégie lente
dir stratEfficient(strategy s, grid g) {
	
	//on crée un tableau d'évaluations
	int* tabEval = malloc(4*sizeof(int));		
	assert(tabEval!=NULL);

	//on crée un tableau où l'on va strocker les directions
	dir* tabMouv = malloc(4*sizeof(dir));
	assert(tabMouv!=NULL);

	//on crée une grille temporaire pour évaluer le resultat de chaques déplacements
	grid tmp = new_grid();
	copy_grid(g, tmp);			
	
	//On effectue un mouvement que l'on place dans tabMouv 
	//On place le résultat de l'evaluation de ce mouvement dans tabEval

	dir tmpDir;

	//pour le mouvement UP
	tmpDir=UP;
	if(can_move(g,tmpDir)){
		do_move(tmp, tmpDir);			
		tabEval[0] = evaluation(tmp);
		//on réinisalise la grille pour le mouvement suivant
		copy_grid(g,tmp);
		}
	else{
		tabEval[0] = 8000;
		}
	tabMouv[0] = tmpDir;
	

	//pour le mouvement DOWN
	tmpDir=DOWN;	
	if(can_move(g,tmpDir)){
		do_move(tmp, tmpDir);			
		tabEval[1] = evaluation(tmp);
		//on réinisalise la grille pour le mouvement suivant
		copy_grid(g,tmp);
		}
	else{
		tabEval[1] = 8000;
		}
	tabMouv[1] = tmpDir;
	
	
	//pour le mouvement RIGHT
	tmpDir=RIGHT;
	if(can_move(g,tmpDir)){
		do_move(tmp, tmpDir);			
		tabEval[2] = evaluation(tmp);
		//on réinisalise la grille pour le mouvement suivant
		copy_grid(g,tmp);
		}
	else{
		tabEval[2] = 8000;
		}
	tabMouv[2] = tmpDir;
	

	//pour le mouvement LEFT
	tmpDir=LEFT;
	if(can_move(g,tmpDir)){
		do_move(tmp, tmpDir);			
		tabEval[3] = evaluation(tmp);
		}
	else{
		tabEval[3] = 8000;
		}
	tabMouv[3] = tmpDir;
	
	delete_grid(tmp);	
	
	//On cherche à le classement des indices de tabEval de l'évaluation avec la plus petite à celle avec la valeure la plus grande
	//on initialise en partant du principe que le tableau est trié

	int val0=0;//indice de la valeure mini
	int val1=1;//indice de la 2eme valeure par ordre croissant
	int val2=2;//indice de la 3eme valeure
	int val3=3;//indice de la valeure max
	for (int i=0; i<4; ++i){
		// si i est l'indice de la valeure mini
		if (tabEval[i]<tabEval[val0]){
			val3=val2;
			val2=val1;
			val1=val0;
			val0=i;
		}
		// si i est l'indice de la 2eme valeure	
		if (tabEval[i]<tabEval[val1]&& tabEval[i]<tabEval[val0]){
			val3=val2;
			val2=val1;
			val1=i;
		}
		// si i est l'indice de la 3eme valeure
		if (tabEval[i]<tabEval[val2]&&tabEval[i]<tabEval[val1]&& tabEval[i]<tabEval[val0]){ 
			val3=val2;
			val2=i;
		}
		else // si i est l'indice de la valeur max
			val3=i;
		}
	//tests
	/*for(int i = 0; i<4; ++i){
		printf("TabEval[%d] = %d\n",i,tabEval[i]);
		
	}
	for(int i = 0; i<4; ++i){
		printf("TabMouv[%d] = %d\n",i,tabMouv[i]);
	}
	printf("val0: %d \n",val0);
	printf("val1: %d \n",val1);
	printf("val2: %d \n",val2);
	printf("val3: %d \n",val3);*/

	// on test pour savoir si le mouvement avec l'evaluation la plus faible est valide
	// si on peut faire le mouvement on l'effectue
	if (can_move(g,tabMouv[val0])){
		tmpDir=tabMouv[val0];
		free(tabMouv);
		free(tabEval);
		return tmpDir;
	}
	// sinon on effectue le mouvement avec l'evaluation juste un peu plus élévée
	if (can_move(g,tabMouv[val1])){
		tmpDir=tabMouv[val1];
		free(tabMouv);
		free(tabEval);
		return tmpDir;
	}
	if (can_move(g,tabMouv[val2])){
		tmpDir= tabMouv[val2];
		free(tabMouv);
		free(tabEval);
		return tmpDir;
	}
	if (can_move(g,tabMouv[val3])){
		tmpDir= tabMouv[val3];
		free(tabMouv);
		free(tabEval);
		return tmpDir;
	}	

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

