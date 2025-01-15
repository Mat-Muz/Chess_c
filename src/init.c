#include "init.h"
#include "Validation_coups.h"


void * creerplateau(int hauteur, int longeur){
    chessboard * plateau;
    plateau  = (chessboard * )malloc(hauteur*sizeof(piece **));

    for (int i = 0; i < longeur;i++){
        plateau[i] = (chessboard)malloc(hauteur*sizeof(piece *));
    }
    return plateau;
}


void initplateau(Game * Jeu , int mode){
    
    chessboard * plateau = Jeu->plateau;

    int hauteur = Jeu->hauteur; //chiffre
    int longeur = Jeu->longeur; //lettre 

    // Le plateau[i,j] sont i pour les chiffres et j pour les lettres
switch (mode){
    case 0: 
        for(int i =0; i<hauteur;i++){
            for(int j = 0; j <longeur; j++){
                plateau[i][j] = NULL; 
            }
        }
    break;
    case 1:
         for(int i =0; i<hauteur;i++){
            for(int j = 0; j <longeur; j++){
                if( j<8 && (i==0 || i == 1 || i ==hauteur-2 ||i == hauteur-1 )){
                    plateau[i][j] = (piece *) malloc(sizeof(piece)) ;
                    if (i ==0 ||i == 1){ //Atention A1 en 0,0 H1 en 0,7 H8 en 7,7
                        plateau[i][j]->couleur= blanc;
                    }
                    else if(i ==hauteur-2 ||i == hauteur-1){
                        plateau[i][j]->couleur= noir;
                    }
                    if(i==hauteur-2||i==1){
                        plateau[i][j]->type = pion;
                    }
                    else if(j==0||j==7){ // 0 == A, 7 == H
                        plateau[i][j]->type =tour;
                    }
                    else if(j==1||j==6){ // 1 == B,  6 == G
                        plateau[i][j]->type =cheval;
                    }
                    else if(j==2||j==5){ // 2 == C , 5 == F 
                        plateau[i][j]->type =fou;
                    }
                    else if(j==4){ // 4 == E
                        plateau[i][j]->type =roi;
                    }                    
                    else if(j==3){ // 3 == D
                        plateau[i][j]->type =reine;
                    } 
                }
                else plateau[i][j] = 0x0;
            }

        }
    //default:
        //rien
    }
}


void * creerplt_vld(Game * Jeu){
    
    plateauvalide * plt_valide;
    plt_valide  = (plateauvalide * ) malloc(Jeu->hauteur*sizeof(p_liste ***));

    for (int i = 0; i < Jeu->longeur;i++){

        plt_valide[i] = (plateauvalide)malloc(Jeu->hauteur*sizeof(p_liste **));
    }
    return plt_valide;
}

void initplt_vld(Game * Jeu){
    
    plateauvalide * plt_valide = Jeu->plt_vld;

    int hauteur = Jeu->hauteur; //chiffre
    int longeur = Jeu->longeur; //lettre 
    // Le plateau[i,j] sont i pour les chiffres et j pour les lettres
    for(int i =0; i<hauteur;i++){
        for(int j = 0; j <longeur; j++){
            plt_valide[i][j] = NULL;
            //printf("i : %d, j : %d , initalized as %p |" , i, j , plt_valide[i][j]);
        }
        //printf("\n");
    }
    //printf("\n");
}


void clean_Game(Game * Jeu){
    //Netoie le jeu en cours 
    if(Jeu->plateau != NULL){
        clean_board(Jeu);
        
    }
    if(Jeu->plt_vld != NULL){
        clean_plt_vld(Jeu);
        
    }
    //Clean IA
    Jeu->player = 0;
    Jeu->hauteur = 0;
    Jeu->longeur = 0;
    Jeu->co[0] = -1;
    Jeu->co[1] = -1;
    Jeu->player = 0;
    Jeu->winner=0;
    Jeu->mode=0;
    Jeu->commande = 0;
    Jeu->round = 0;

}



void clean_board(Game * Jeu){
    //netoie le plateua de jeu
    chessboard * plateau = Jeu->plateau;
    int hauteur = Jeu->hauteur; 
    int longeur = Jeu->longeur;
    
    if(plateau  != NULL){
        for(int i =0; i<hauteur;i++){
            if(plateau[i] != NULL){ 
                for(int j = 0; j <longeur; j++){
                    if(plateau[i][j] != NULL){
                        free(plateau[i][j]); //free des pieces
                    } 
                }
                free(plateau[i]); //free des lignes
            }
        }
        free(plateau); // libération du plateau
        Jeu->plateau = NULL;
    }

}


void clean_plt_vld(Game * Jeu){
    //libere le plt_vld de jeu
    plateauvalide * plt_vld = Jeu->plt_vld;
    int hauteur = Jeu->hauteur; 
    int longeur = Jeu->longeur;
    
    if(plt_vld  != NULL){
        for(int i =0; i<hauteur;i++){
            if(plt_vld[i] != NULL){ 
                for(int j = 0; j <longeur; j++){
                    if(plt_vld[i][j] != NULL){
                        
                        plt_vld[i][j] = (p_liste *) del_p_list(plt_vld[i][j]); //suppression des listes
                    } 
                }
                free(plt_vld[i]); //free des lignes
            }
        }
        free(plt_vld); // libération du plateau
        Jeu->plt_vld = NULL;
    }
}



