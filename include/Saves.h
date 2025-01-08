#ifndef SAVE_H
#define SAVE_H
#include "chess.h"


void CreateSave(Game *);
int SelectSave(Game *);
int SaveLoad(char * ,Game *);
void Autosave(Game *);
void Last_save_Load(Game *);
char* findMostRecentFile(const char *);

#endif
