#include "Validation_coups.h"



void pop_plt_vld(Game * Jeu){
    //genere les elements de plt_vld
    int hauteur = Jeu->hauteur; 
    int longeur = Jeu->longeur;
    for(int i =0; i<hauteur;i++){
        for(int j = 0; j <longeur; j++){
            coup_valide_piece(i,j,Jeu);
        }
    }
}

void coup_valide_piece(int i, int j, Game *Jeu){
    plateauvalide * plt_vld = Jeu->plt_vld;
    chessboard * plateau = Jeu->plateau;
    piece * current_piece = plateau[i][j];
    int hauteur = Jeu->hauteur; 
    int longeur = Jeu->longeur;
    if (plateau[i][j] == 0x0){return;}
    int x = 0;
    int y = 0;
    switch(current_piece->type){
        case pion:
            y=i+current_piece->couleur;
            x=j;
            if (plateau[y][x] == 0x0){
                    plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                    // printf("pion , %d %d peut aller en %d %d \n", i,j, i+current_piece->couleur, j);
            }
            x++;
            if (plateau[y][x] != 0x0 && plateau[y][x]->couleur != current_piece->couleur){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                // printf("pion , %d %d peut aller en %d %d \n", i,j, i+current_piece->couleur, j+1);
            }
            x=j-1;
            if (x>= 0 && plateau[y][x] != 0x0 && plateau[y][x]->couleur != current_piece->couleur){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                // printf("pion , %d %d peut aller en %d %d \n", i,j, i+current_piece->couleur, j-1);
            }
            x=j;
            if(current_piece->mvd == 0){ // double coup!
                  y=y+current_piece->couleur;
                  if (plateau[y][x] == 0x0){
                    plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                    // printf("pion , %d %d peut aller en %d %d \n", i,j, i+current_piece->couleur, j);
            }
            }
            //cas en passant 
            if((j+1)<longeur && plateau[i][j+1] !=NULL && plateau[i][j+1]->couleur != current_piece->couleur && plateau[i][j+1]->type == pion && ((plateau[i][j+1]->mvd == Jeu->round && plateau[i][j+1]->couleur == blanc ) || (plateau[i][j+1]->mvd == Jeu->round-1 && plateau[i][j+1]->couleur == noir ))){
                plt_vld[i+current_piece->couleur][j+1] = add_p_liste(plt_vld[i+current_piece->couleur][j+1],current_piece);
            }
            if((j-1)>=0 && plateau[i][j-1] !=NULL && plateau[i][j-1]->couleur != current_piece->couleur && plateau[i][j-1]->type == pion && ((plateau[i][j-1]->mvd == Jeu->round && plateau[i][j-1]->couleur == blanc ) || (plateau[i][j-1]->mvd == Jeu->round-1 && plateau[i][j-1]->couleur == noir ))){
                plt_vld[i+current_piece->couleur][j-1] = add_p_liste(plt_vld[i+current_piece->couleur][j-1],current_piece);
            }





            //printf("\n~~~\n");
         break;
        
        case tour:
            x=j;
            y=i;
            for(y = i+1; y<hauteur && (plateau[y][j] == 0x0 || plateau[y][j]->couleur!=current_piece->couleur) ; y++){
                plt_vld[y][j] = add_p_liste(plt_vld[y][j],current_piece);
                printf("Tour , %d %d peut aller en %d %d \n", i,j, y, j);
                if (plateau[y][j] != 0x0) {break;}
            }
            for(y = i-1; y>=0 && (plateau[y][j] == 0x0 || plateau[y][j]->couleur!=current_piece->couleur) ; y--){
                plt_vld[y][j] = add_p_liste(plt_vld[y][j],current_piece);
                //printf("Tour , %d %d peut aller en %d %d \n", i,j, y, j);
                if (plateau[y][j] != 0x0) {break;}
            }
             for(x=j+1; x<longeur && (plateau[i][x] == 0x0 || plateau[i][x]->couleur!=current_piece->couleur) ; x++){
                plt_vld[i][x] = add_p_liste(plt_vld[i][x],current_piece);
                //printf("Tour , %d %d peut aller en %d %d \n", i,j, i, x);
                if (plateau[i][x] != 0x0) {break;}
            }
            for(x=j-1; x>=0 && (plateau[i][x] == 0x0 || plateau[i][x]->couleur!=current_piece->couleur) ; x--){
                 plt_vld[i][x] = add_p_liste(plt_vld[i][x],current_piece);
                 //printf("Tour , %d %d peut aller en %d %d \n", i,j, i, x);
                if (plateau[i][x] != 0x0) {break;}
            }
            break;
        
        case fou:
            x=j;
            y=i;
            for((y = i+1 , x=j+1); y<hauteur && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur) ; (y++ , x++)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("fou , %d %d peut aller en %d %d \n", i,j, y, x);
                if (plateau[y][x] != 0x0) {break;}
            }
            for((y = i-1 , x=j+1); y>=0 && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur) ; (y-- , x++)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("fou , %d %d peut aller en %d %d \n", i,j, y, x);
                if (plateau[y][x] != 0x0) {break;}
            }

            for((y = i-1 , x=j-1); y>=0 && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur) ; (y-- , x--)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("fou , %d %d peut aller en %d %d \n", i,j, y, x);
                if (plateau[y][x] != 0x0) {break;}
            }
            for((y = i+1 , x=j-1); y<hauteur && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur) ; (y++ , x--)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("fou , %d %d peut aller en %d %d \n", i,j, y, x);
                if (plateau[y][x] != 0x0) {break;}
            }
            break;

        case reine:
            x=j;
            y=i;         
            for(y = i+1; y<hauteur && (plateau[y][j] == 0x0 || plateau[y][j]->couleur!=current_piece->couleur) ; y++){
                plt_vld[y][j] = add_p_liste(plt_vld[y][j],current_piece);
                //printf("Dame , %d %d peut aller en %d %d \n", i,j, y, j);
                if (plateau[y][j] != 0x0) {break;}
            }
            for(y = i-1; y>=0 && (plateau[y][j] == 0x0 || plateau[y][j]->couleur!=current_piece->couleur) ; y--){
                plt_vld[y][j] = add_p_liste(plt_vld[y][j],current_piece);
                //printf("Dame , %d %d peut aller en %d %d \n", i,j, y, j);
                if (plateau[y][j] != 0x0) {break;}
            }
             for(x=j+1; x<longeur && (plateau[i][x] == 0x0 || plateau[i][x]->couleur!=current_piece->couleur) ; x++){
                plt_vld[i][x] = add_p_liste(plt_vld[i][x],current_piece);
                //printf("Dame , %d %d peut aller en %d %d \n", i,j, i, x);
                if (plateau[i][x] != 0x0) {break;}
            }
            for(x=j-1; x>=0 && (plateau[i][x] == 0x0 || plateau[i][x]->couleur!=current_piece->couleur) ; x--){
                plt_vld[i][x] = add_p_liste(plt_vld[i][x],current_piece);
                 //printf("Dame , %d %d peut aller en %d %d \n", i,j, i, x);
                if (plateau[i][x] != 0x0) {break;}
            }
            for((y = i+1 , x=j+1); y<hauteur && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur) ; (y++ , x++)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Dame , %d %d peut aller en %d %d \n", i,j, y, x);
                if (plateau[y][x] != 0x0) {break;}
            }
            for((y = i-1 , x=j+1); y>=0 && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur) ; (y-- , x++)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Dame , %d %d peut aller en %d %d \n", i,j, y, x);
                if (plateau[y][x] != 0x0) {break;}
            }

            for((y = i-1 , x=j-1); y>=0 && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur) ; (y-- , x--)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Dame , %d %d peut aller en %d %d \n", i,j, y, x);
                if (plateau[y][x] != 0x0) {break;}
            }
            for((y = i+1 , x=j-1); y<hauteur && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur) ; (y++ , x--)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Dame , %d %d peut aller en %d %d \n", i,j, y, x);
                if (plateau[y][x] != 0x0) {break;}
            }
            break;
        case roi:
            x=j;
            y=i;

            y = i+1;
            if(y<hauteur && (plateau[y][j] == 0x0 || plateau[y][j]->couleur!=current_piece->couleur)){
                plt_vld[y][j] = add_p_liste(plt_vld[y][j],current_piece);
                //printf("Roi , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            x=j+1;
            if(y<hauteur && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Roi , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            x=j-1;
            if(y<hauteur && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Roi , %d %d peut aller en %d %d \n", i,j, y, x);
            }

            y = i-1;
            if(y>=0 && (plateau[y][j] == 0x0 || plateau[y][j]->couleur!=current_piece->couleur)){
                plt_vld[y][j] = add_p_liste(plt_vld[y][j],current_piece);
                //printf("Roi , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            x=j+1;
            if(y>=0 && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Roi , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            x=j-1;
            if(y>=0 && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Roi , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            x=j+1;
            if(x<longeur && (plateau[i][x] == 0x0 || plateau[i][x]->couleur!=current_piece->couleur)){
                 plt_vld[i][x] = add_p_liste(plt_vld[i][x],current_piece);
                 //printf("Roi , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            x=j-1;
            if(x>=0 && (plateau[i][x] == 0x0 || plateau[i][x]->couleur!=current_piece->couleur)){
                 plt_vld[i][x] = add_p_liste(plt_vld[i][x],current_piece);
                 //printf("Roi , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            break;
        
        case cheval:
            x=j;
            y=i;

            x=j+1;
            y=i+2;
            if(y<hauteur && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Cheval , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            y=i-2;
            if(y>=0 && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Cheval , %d %d peut aller en %d %d \n", i,j, y, x);
            }

            x=j-1;
            y=i+2;
            if(y<hauteur && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Cheval , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            y=i-2;
            if(y>=0 && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Cheval , %d %d peut aller en %d %d \n", i,j, y, x);
            }

            
            x=j+2;
            y=i+1;
            if(y<hauteur && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Cheval , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            y=i-1;
            if(y>=0 && x<longeur && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Cheval , %d %d peut aller en %d %d \n", i,j, y, x);
            }

            x=j-2;
            y=i+1;
            if(y<hauteur && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Cheval , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            y=i-1;
            if(y>=0 && x>=0 && (plateau[y][x] == 0x0 || plateau[y][x]->couleur!=current_piece->couleur)){
                plt_vld[y][x] = add_p_liste(plt_vld[y][x],current_piece);
                //printf("Cheval , %d %d peut aller en %d %d \n", i,j, y, x);
            }
            //printf("\n ~~~~ \n");
            break;
    }
}

void clear_plt_vld(Game * Jeu){
    //netoyer tt les element de plt_vld
    plateauvalide * plt_vld = Jeu->plt_vld;
    int hauteur = Jeu->hauteur; 
    int longeur = Jeu->longeur;
    for(int i =0; i<hauteur;i++){
        for(int j = 0; j <longeur; j++){
            //printf("i,j %d,%d \n",i,j);
            plt_vld[i][j] = (p_liste *) del_p_list(plt_vld[i][j]); //supression des listes
            //printf("pointeur Should be nil :  %p \n",plt_vld[i][j]);
        }
    }
        
}

p_liste* add_p_liste(p_liste * tete, piece * elem){
    p_liste * new_tete = (p_liste *)malloc(sizeof(p_liste));
    new_tete->p = elem;
    new_tete->suiv = tete;
    return new_tete;
}

void * del_p_list(p_liste * tete){
    p_liste * temp;
    while(tete != NULL){
        temp = tete;
        tete = tete->suiv;
        free(temp);
    }
    return tete;
}

//TODO estvalide
bool estvalide(Game * Jeu, int co_arrive[]){
      int a,b;
      a = Jeu->co[0];
      b = Jeu->co[1];
      p_liste * temp = Jeu->plt_vld[co_arrive[0]][co_arrive[1]];
      while(temp != NULL){
            if(Jeu->plateau[a][b] == temp->p){return true;}
            temp = temp->suiv;
      }
      return false;
}