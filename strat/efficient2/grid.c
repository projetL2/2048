// Fichier grid.c
#include "grid.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// La structure de la grille, avec un pointeur de pointeur qui donne la matrice
// et un unsigned long int pour le score.
struct grid_s {
    unsigned long int score;
    tile** grid;
};

// Le constructeur initialise le score à 0
// et fait des malloc pour la structure et la grille.
grid new_grid () {
    grid g = malloc(sizeof(struct grid_s)); // Allocation mémoire de la structure.
    assert (g!=NULL);
    g->score=0;
    g->grid = malloc(GRID_SIDE * sizeof(tile*)); // Allocation mémoire du pointeur grid.
    assert (g->grid!=NULL);
    for (int i=0; i<GRID_SIDE; ++i) {
        g->grid[i] = malloc (GRID_SIDE * sizeof(tile)); // Allocation mémoire des pointeurs dans grid.
        assert (g->grid[i]!=NULL);
    }
    for(int i=0; i<GRID_SIDE; ++i) // On initialise les cases à 0.
        for(int j=0; j<GRID_SIDE; ++j)
            g->grid[i][j]=0;
    return g;
}

// Destructeur de la grille
// qui libère d'abord les zones de la mémoire pointées par la variable grid puis la grille elle-même.
void delete_grid (grid g) {
    for (int i=0; i<GRID_SIDE; ++i)
        free(g->grid[i]);
    free(g->grid);
    free(g);
}

// Constructeur par copie de grid.
void copy_grid (grid src, grid dst) {
    dst->score = src->score; // On copie le score.
    for (int i=0; i<GRID_SIDE; ++i)
        for (int j=0; j<GRID_SIDE; ++j)
            set_tile(dst,i,j,get_tile(src,i,j)); // On initialise la tile de dst avec la valeur de celle de src.
}

// Accesseur qui retourne le score.
unsigned long int grid_score (grid g) {
    return g->score;
}

// Accesseur qui renvoie une tile en fonction des coordonnées passées en paramètre.
tile get_tile (grid g, int colonne, int ligne) {
    assert((colonne>=0 && colonne<GRID_SIDE) && (ligne>=0 && ligne<GRID_SIDE));
    return g->grid[colonne][ligne]; // Si la tile est dans les limites de la grille, on la renvoie.
}

// Accesseur qui modifie la valeur d'une tile en fonction des coordonnées et de la valeur passés en paramètre.
void set_tile (grid g, int colonne, int ligne, tile t) {
    g->grid[colonne][ligne] = t;
}

// Fonction booléenne qui renvoie true si le joueur peut effectuer un mouvement dans une direction et false sinon.
bool can_move (grid g, dir d) {
// On regarde la direction demandée (d).
// Suivant celle-ci, on parcourt la grille pour voir si on peut, quelque part, faire un déplacement ou une fusion,
// si oui, on renvoie true.
    switch (d) {
    case LEFT:
        for (int colonne=1; colonne<GRID_SIDE; ++colonne)
            for (int ligne=0; ligne<GRID_SIDE; ++ligne)
                if ( get_tile(g,colonne,ligne) != 0) // Si la case est pleine,
                    if( (get_tile(g,colonne-1,ligne) == 0) || (get_tile(g,colonne-1,ligne) == get_tile(g,colonne,ligne)) ) // alors on regarde si la case suivante est vide ou si une fusion est possible.
                        return true;
        break;
    case RIGHT:
        for (int colonne=0; colonne<GRID_SIDE-1; ++colonne)
            for (int ligne=0; ligne<GRID_SIDE; ++ligne)
                if( get_tile(g,colonne,ligne) != 0)
                    if ( (get_tile(g,colonne+1,ligne) == 0) || (get_tile(g,colonne+1,ligne) == get_tile(g,colonne,ligne)))
                        return true;
        break;
    case UP:
        for (int colonne=0; colonne<GRID_SIDE; ++colonne)
            for (int ligne=1; ligne<GRID_SIDE; ++ligne)
                if( get_tile(g,colonne,ligne) != 0)
                    if ( (get_tile(g,colonne,ligne-1) == 0) || (get_tile(g,colonne,ligne-1) == get_tile(g,colonne,ligne)) )
                        return true;
        break;
    case DOWN:
        for (int colonne=0; colonne<GRID_SIDE; ++colonne)
            for (int ligne=0; ligne<GRID_SIDE-1; ++ligne)
                if( get_tile(g,colonne,ligne) != 0)
                    if ( (get_tile(g,colonne,ligne+1) == 0) || (get_tile(g,colonne,ligne+1) == get_tile(g,colonne,ligne)) )
                        return true;
        break;
    }
// Si le mouvement demandé est impossible, on renvoie false.
    return false;
}

// Fonction booléenne qui renvoie true si aucun mouvement n'est plus possible.
bool game_over(grid g) {
    if ( !can_move(g,UP) && !can_move(g,DOWN) &&
            !can_move(g,LEFT) && !can_move(g,RIGHT))
        return true;
    else
        return false;
}

// Fonction qui déplace les tiles de la grid si le mouvement est possible.
void do_move (grid g, dir d) {
    int flag; // Cette variable sert à indiquer une limite. Quand une fusion a eu lieu, aucune fusion n'est plus possible après cette limite.
// Ca évite les fusions type : 0 4 4 8 *mouvement à droite* ==> 0 0 0 16
    switch (d) {
    case LEFT:
        for (int ligne = 0; ligne<GRID_SIDE; ++ligne) { // On parcourt de haut en bas
            flag = 0;
            for (int colonne = 1; colonne<GRID_SIDE; ++colonne) { // et de gauche à droite.
                if (get_tile(g,colonne,ligne) != 0) { // Si la case n'est pas vide
                    if (get_tile(g,colonne-1,ligne) == 0) { // et si la case de gauche est vide, on décale la case actuelle.
                        set_tile(g,colonne-1,ligne,get_tile(g,colonne,ligne));
                        set_tile(g,colonne,ligne,0);
                        if(colonne >1)
                            colonne-=2; // On décrémente i au cas où il y ait à déplacer la tile plusieurs fois.
                    }
                    else if (get_tile(g,colonne,ligne) == get_tile(g,colonne-1,ligne) && colonne > flag) { // S'il doit y avoir une fusion et qu'on n'a pas dépassé notre limite,
                        set_tile(g,colonne,ligne,0);
                        set_tile(g,colonne-1,ligne,(get_tile(g,colonne-1,ligne)*2)); // on vide la case actuelle et on double la valeur de celle qu'elle a heurté.
                        g->score += get_tile(g,colonne-1,ligne); // On actualise le score.
                        flag = colonne; // Il y a eu fusion, donc on installe la limite à cet endroit.
                    }
                }
            }
        }
        break;
// Le principe est le même, seul le parcours change.
    case RIGHT:
        for (int ligne=0; ligne<GRID_SIDE; ++ligne) {// On parcourt de haut en bas
            flag = GRID_SIDE-1;
            for (int colonne = GRID_SIDE-2; colonne>=0; --colonne) { // et droite à gauche.
                if (get_tile(g,colonne,ligne) != 0 && colonne < GRID_SIDE -1) {
                    if (get_tile(g,colonne+1,ligne) == 0) {
                        set_tile(g,colonne+1,ligne,get_tile(g,colonne,ligne));
                        set_tile(g,colonne,ligne,0);
                        colonne+=2;
                    }
                    else if (get_tile(g,colonne,ligne) == get_tile(g,colonne+1,ligne) && colonne < flag) {
                        set_tile(g,colonne,ligne,0);
                        set_tile(g,colonne+1,ligne,(get_tile(g,colonne+1,ligne)*2));
                        g->score += get_tile(g,colonne+1,ligne);
                        flag = colonne;
                    }
                }
            }
        }
        break;
    case DOWN:
        for (int colonne=0; colonne<GRID_SIDE; ++colonne) { // On parcourt de gauche à droite
            flag = GRID_SIDE-1;
            for (int ligne = GRID_SIDE-2; ligne>=0; --ligne) {// de bas en haut.
                if (get_tile(g,colonne,ligne) != 0 && ligne < GRID_SIDE -1) {
                    if (get_tile(g,colonne,ligne+1) == 0) {
                        set_tile(g,colonne,ligne+1,get_tile(g,colonne,ligne));
                        set_tile(g,colonne,ligne,0);
                        ligne+=2;
                    }
                    else if (get_tile(g,colonne,ligne) == get_tile(g,colonne,ligne+1) && ligne < flag) {
                        set_tile(g,colonne,ligne,0);
                        set_tile(g,colonne,ligne+1,get_tile(g,colonne,ligne+1)*2);
                        g->score += get_tile(g,colonne,ligne+1);
                        flag = ligne;
                    }
                }
            }
        }
        break;
    case UP:
        for (int colonne=0; colonne<GRID_SIDE; ++colonne) { // On parcourt de gauche à droite
            flag = 0;
            for (int ligne=1; ligne<GRID_SIDE; ++ligne) { // de haut en bas.
                if (get_tile(g,colonne,ligne) != 0) {
                    if (get_tile(g,colonne,ligne-1) == 0) {
                        set_tile(g,colonne,ligne-1,get_tile(g,colonne,ligne));
                        set_tile(g,colonne,ligne,0);
                        if(ligne>1)
                            ligne-=2;
                    }
                    else if (get_tile(g,colonne,ligne-1) == get_tile(g,colonne,ligne) && ligne > flag) {
                        set_tile(g,colonne,ligne,0);
                        set_tile(g,colonne,ligne-1,get_tile(g,colonne,ligne-1)*2);
                        g->score += get_tile(g,colonne,ligne-1);
                        flag = ligne;
                    }
                }
            }
        }
        break;
    }
}

// Fonction qui ajoute une tile de façon aléatoire dans une case vide de la grid.
void add_tile (grid g) {
    int numberRand = rand()%10; // Dans l'entier numberRand, on stocke une valeur aléatoire entre 0 et 10 donnée par la fonction rand.
    int colonneRand = rand()%GRID_SIDE;// Choix d'une colonne aléatoirement.
    int ligneRand = rand()%GRID_SIDE; // Choix d'une ligne aléatoirement.
    while(get_tile(g,colonneRand,ligneRand)!=0) { // Si la case est occupée, on refait des random jusqu'à en trouver une vide.
        colonneRand = rand()%GRID_SIDE;
        ligneRand = rand()%GRID_SIDE;
    }
    if(numberRand == 9)// 4 doit avoir une chance sur 10 d'apparaître, on a sélectionné le chiffre 9 de façon arbitraire.
        set_tile(g,colonneRand,ligneRand,4);
    else
        set_tile(g,colonneRand,ligneRand,2);
}

// Fonction qui doit récupérer les instructions du joueur.
void play (grid g, dir d) {
    if (can_move(g,d)) { // Si on peut jouer,
        do_move(g,d); // on joue, on effectue le déplacement,
        add_tile(g); // et on ajoute une tile aléatoire.
    }
}
