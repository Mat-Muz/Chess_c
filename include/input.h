#ifndef INPUT_H
#define INPUT_H

#include "chess.h"

int convertstrint(char *);
void selectcoord(Game* Jeu, int cas);
void pawnpromote(Game * Jeu, int co[]);
void user_text_input(Game * Jeu,char *); 


#endif