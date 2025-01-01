#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "chess.h"
#include "input.h"
#include "affichage.h"

int playermove(Game *);

void check_detection(Game * ); //detecte si le joueur actuel est en echec

bool case_attaque(Game * , int , int );//detecte si la case est attacké par une des pieces 


#endif