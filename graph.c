#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH (GRID_SIDE*140)
#define SCREEN_HEIGHT (GRID_SIDE*140)+40

int main() {
	
	//déclaration de la fenêtre et d'une surface
	SDL_Window* fenetre = NULL;
	SDL_Surface* surface = NULL;
	SDL_Surface* tile = NULL;
	
	// initialisation de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

	// paramètres de la fenêtre
	fenetre = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	//paramètres de la surface
	surface = SDL_GetWindowSurface(fenetre);
	
	SDL_FillRect( surface, NULL, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff ));
	
	SDL_UpdateWindowSurface(fenetre); 
	
	tile = SDL_LoadBMP("sprites/tile.bmp");
	
	if( tile == NULL ) { 
		printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
	}
	
	if( !fenetre )		
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());	
			
	SDL_Rect tmp = {0,0,140,140};
		
	for(int i = 0; i<GRID_SIDE; i++)
		for (int j=0; j<GRID_SIDE; j++) {
			tmp.x=i*140;
			tmp.y=j*140;
			SDL_BlitSurface(tile,NULL,surface,&tmp);
		}
		
	while(1) {
		
		SDL_Event e;
		
		if(SDL_PollEvent(&e))
			if(e.type == SDL_QUIT)
				break;	
		SDL_UpdateWindowSurface( fenetre );
	}
	
    SDL_FreeSurface(surface);  
    SDL_DestroyWindow(fenetre);  
    SDL_Quit(); //arret de la SDL
	
	return EXIT_SUCCESS;
}
