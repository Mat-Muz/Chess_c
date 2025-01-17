#ifndef INIT_H
#define INIT_H
#include "chess.h"


void * creerplateau(int , int );
void initplateau(Game * , int );
void clean_Game(Game *);
void clean_board(Game *);

void * creerplt_vld(Game * );
void initplt_vld(Game *);
void clean_plt_vld(Game *);

IA * init_IA(Game * Jeu);
void clean_IA(Game * );
void clear_coup(Game*);
co* ajouter_co(co* tete, int chiffre, int lettre);
co* creer_noeud(int chiffre, int lettre);
void supp_co(co **tete);


#endif