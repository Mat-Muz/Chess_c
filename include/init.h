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




#endif