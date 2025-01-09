#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "chess.h"
#include "input.h"
#include "affichage.h"

int playermove(Game *);

bool check_detection(Game *, bool ); //detecte si le joueur actuel est en echec

bool case_attaque(Game * , int , int );//detecte si la case est attacké par une des pieces 

bool player_cant_mv(Game * );
int fin_de_partie(Game *);

#endif