#ifndef MENU_H
#define MENU_H
#include <termios.h>
#include <unistd.h>

#include "chess.h"


void affichageMenu(Menu *);
void afficheimage(char *);
void main_menu(Menu *);
void changepage(Menu *);

void enableRawMode();
void disableRawMode();
void menuManager(Menu *);



#endif