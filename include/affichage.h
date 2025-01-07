#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#define MARGE_GAUCHE "25"
#define MARGE_HAUTE "4"

#include "chess.h"

void lettres(Game *);
void clearscr();
void afficheJoueur(Game *);
void afficheplateau(Game * );
void seppaligne(int );
void retchr();
void coin();
void affichecoupvalide(Game *);
void bordereau();

#endif