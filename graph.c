#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH (GRID_SIDE*140)
#define SCREEN_HEIGHT (GRID_SIDE*140)+60

bool init() {
	// renvoie faux si il y a un problème d'initialisation
	if(TTF_Init() ==-1 || SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;
	return true;
}

void nouveauJeu(SDL_Surface* surface) {
	// création d'une surface
	SDL_Surface* tile = NULL;
	//chargement du sprite
	tile = SDL_LoadBMP("sprites/tile.bmp");
	SDL_FillRect( surface, NULL, SDL_MapRGB(surface->format, 220, 212, 171 ));
	SDL_Rect tmp = {0,0,140,140};
	//boucle d'affichage de la grille	
	for(int i = 0; i<GRID_SIDE; i++)
		for (int j=0; j<GRID_SIDE; j++) {
			tmp.x=i*140;
			tmp.y=j*140;
			SDL_BlitSurface(tile,NULL,surface,&tmp);
		}
}

void dessinerGrille(SDL_Surface* surface, grid g) {
	
	char score[30] = "";
	SDL_Color textColor = { 0, 0, 0 };
	TTF_Font *font = TTF_OpenFont("fonts/LinLibertine.ttf", 40);
	SDL_Surface *texte = NULL;
	sprintf(score, "Score: %ld", grid_score(g));
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, score, textColor);
	SDL_Rect scoreRect = { SCREEN_WIDTH/2-100, SCREEN_HEIGHT-45,50,50};
	nouveauJeu(surface);
	
	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;
	char tile[10] = "";
	
	for (int ligne=0; ligne<GRID_SIDE; ++ligne) {
		for (int colonne=0; colonne<GRID_SIDE; ++colonne) {
            if (get_tile(g, colonne, ligne) != 0) {
				sprintf(tile, "%d", get_tile(g, colonne, ligne));
				pos.x = 40 + (140*colonne);
				pos.y = 50 + (140*ligne);
				texte = TTF_RenderText_Blended(font, tile, textColor);
				SDL_BlitSurface(texte, NULL, surface, &pos);
			}
        }
    }
	SDL_BlitSurface(textSurface, NULL, surface, &scoreRect);
}

int main() {
	
	grid g = new_grid();
	add_tile(g);
	add_tile(g);
	
	int quit = 0;
		
	if(!init()) {
		printf( "Unable to initialize SDL\n");
		return EXIT_FAILURE;
	}
	
	//déclaration de la fenêtre et d'une surface
	SDL_Window* fenetre = NULL;
	SDL_Surface* surface = NULL;
	TTF_Font *font = TTF_OpenFont("fonts/font.TTF", 28);

	// paramètres de la fenêtre
	fenetre = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	//paramètres de la surface
	surface = SDL_GetWindowSurface(fenetre);
	
	SDL_FillRect( surface, NULL, SDL_MapRGB(surface->format, 220, 212, 171 ));
	
	SDL_UpdateWindowSurface(fenetre); 
	
	if(font == NULL ) 
		printf( "Unable to load font");

	if(!fenetre )		
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());	
		
	nouveauJeu(surface);
		
	while(!quit) {
		
		SDL_Event e;
		
		while(SDL_PollEvent(&e)) {
			
			switch(e.type) {
				case SDL_QUIT :
				quit = 1;
				break;
				case SDL_KEYDOWN :
					switch( e.key.keysym.sym ){
                    case SDLK_LEFT:
                        play(g,LEFT);
                        break;
                    case SDLK_RIGHT:
                        play(g,RIGHT);
                        break;
                    case SDLK_UP:
                        play(g,UP);
                        break;
                    case SDLK_DOWN:
                        play(g,DOWN);
                        break;
                    default:
                        break;
                }
				break;
			}	
		}	
		SDL_FreeSurface(surface);	
		dessinerGrille(surface, g);
		SDL_UpdateWindowSurface( fenetre );
		
	}
	
    SDL_FreeSurface(surface);  
    SDL_DestroyWindow(fenetre);  
    SDL_Quit(); //arret de la SDL
	
	return EXIT_SUCCESS;
}
