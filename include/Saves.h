#ifndef SAVE_H
#define SAVE_H
#include "chess.h"


void CreateSave(Game *);
int SelectSave(Game *);
int SaveLoad(char * ,Game *);
void Autosave(Game *);

#endif
