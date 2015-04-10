//Le fichier fast3.c qui est premet d'effectuer la stratégie rapide

//plante très rarement pourquoi? jamais de 2/UP!! boucle à l'infini ... parfois!

#include "strategy.h"
#include <stdlib.h>
#include <assert.h>
#include "fast3.h"
#include <time.h>
#include "grid.h"

//La fonction stratFast est l'algorithme principal de la stratégie rapide
//On a choisi un deplacement totalement au hasard
dir stratFast(strategy s, grid g) {
	
	dir d;
	while (1){// on cherche un mouvement valide
		int numberRand = rand()%3;
		switch (numberRand){ // switch qui fait correspondre l'int à la direction.
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
		if (can_move(g,d))
			printf("on est dans le if dir: %d\n",d);
			return d;
			
	}
	printf("dir: %d\n",d);
}

//La fonction A1_almyre_chambres_mahazoasy_petureau_fast3 est le constructeur de la stratégie.
strategy A1_almyre_chambres_mahazoasy_petureau_fast3() {
	srand(time (NULL)); // srand est une fonction de la bibliothéque stdlib.h. Cette ligne permet d'initiliser la fonction time (de la bibliothèque time.h).
	
	strategy s = malloc(sizeof(struct strategy_s));
	assert(s!=NULL);
	
	s->name = "fast3";
	s->mem = NULL;
	s->play_move = stratFast;
	s->free_strategy = free_memless_strat;
	
	return s;
}
