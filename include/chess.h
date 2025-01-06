#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


#define noir -1
#define blanc 1
#define true 1
#define false 0


typedef struct piece piece;
typedef struct Game Game;
typedef struct Menu Menu;
typedef struct p_liste p_liste;
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
};


struct Game{
    //cst
    chessboard * plateau;
    int hauteur;
    int longeur;
    int mode;
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
    int options;
    int page;
};

struct p_liste{
    
    piece * p; //pointeur ver une piece qui peut aller sur la case 
    p_liste * suiv;
};

#endif