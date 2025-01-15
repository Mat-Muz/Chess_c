#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>




#define noir -1
#define blanc 1
#define true 1
#define false 0


typedef struct piece piece;
typedef struct Game Game;
typedef struct Menu Menu;
typedef struct p_liste p_liste;
typedef struct IA IA;
typedef struct co co; 
typedef int bool;

typedef piece ** chessboard; // plateau contenant une piece placée a la coordonnée i,j 
typedef p_liste ** plateauvalide; // plateau contenant la liste des pieces pouvant aller a cette case au coordonnées i,j 



enum valeurs
{
    vide, pion, tour, cheval, fou, reine, roi 
}; 

struct piece{
    int type;
    int couleur;
    int mvd;
    int pst; //mvd du passé

    //co * coups;
};


struct Game{
    Menu * menu;
    //cst
    chessboard * plateau;
    int hauteur;
    int longeur;
    int mode;
    //IA * ordi;
    // var de game loop
    plateauvalide * plt_vld;
    int player;
    int winner;
    int round;
    //touché par user
    int co[2]; //[chiffre][lettre]
    int commande;


};

struct Menu{
    Game * Jeu;
    int couleur;
    int savemode;
    int page;
};

struct p_liste{
    
    piece * p; //pointeur vers une piece qui peut aller sur la case 
    p_liste * suiv;
};

struct IA{
    int couleur;

    co * pieces;

};

struct co{
    int chiffre;
    int lettre;

    co * suiv;
};

#endif