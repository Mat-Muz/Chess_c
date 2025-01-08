#ifndef VALID_COUP_H
#define VALID_COUP_H
#include "chess.h"
#include "init.h"
#include "Game_logic.h"

void coup_valide_piece(int,int,Game*,bool);
void pop_plt_vld(Game* , bool );
void clear_plt_vld(Game *);
void * del_p_list(p_liste *);
p_liste* add_p_liste(p_liste *, piece*);

bool estvalide(Game *, int *);

#endif