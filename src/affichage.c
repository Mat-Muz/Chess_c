#define MARGE_GAUCHE "25"
#define MARGE_HAUTE "4"
#include "affichage.h"
#include "Validation_coups.h"

void clearscr(){
    //clear le terminal
    printf("\033[H");
    printf("\033[0J");

}

void retchr(){
    //fait un retour a la ligne avec une marge definie comme étant MARGE_GAUCHE
    char marge[128] = "\033[";
    strcat(marge,MARGE_GAUCHE);
    strcat(marge,"G");
    printf("\n %s",marge);    
}
void coin(){
    //place le curseur au coin défini par MARGE_GAUCHE et MARGE_HAUTE 
    char corner[128] = "\033[";
    strcat(corner,MARGE_HAUTE);
    strcat(corner,";");
    strcat(corner,MARGE_GAUCHE);
    strcat(corner,"H");
    printf("%s",corner);  


}

void afficheplateau( Game * Jeu ){
        chessboard * plateau = Jeu->plateau;
    char * pieces[6] ={"♟","♜","♞","♝","♛","♚"};
 clearscr();
 bordereau();
 coin();
 printf("\033[0m");
 if(Jeu->player == blanc ){ //symétrie due au tableau 
    for(int i = Jeu->hauteur -1;i>=0;i--){
        seppaligne(Jeu->longeur);
        retchr();
        for(int j = 0 ; j<Jeu->longeur; j++){
            printf("\033[0m");
            printf("│");
                if(plateau[i][j]==0x0){printf("   ");}
                else{
                plateau[i][j]->couleur == blanc ?  printf("\033[0;97m"):printf("\033[90m"); //Couleur pour les autres pieces
                printf(" %s ",pieces[plateau[i][j]->type -1]);
                }
        }
        printf("\033[0m");
        printf("│  %d",i+1);
    }
 }
 else {
    for(int i =0; i<Jeu->hauteur;i++){
        seppaligne(Jeu->longeur);
        retchr();
        for(int j = Jeu->longeur -1 ; j>=0; j--){
            printf("\033[0m");
            printf("│");
                if(plateau[i][j]==0x0){printf("   ");}
                else{
                plateau[i][j]->couleur == blanc ?  printf("\033[0;97m"):printf("\033[90m"); //Couleur pour les autres pieces
                printf(" %s ",pieces[plateau[i][j]->type -1]);
                }
        }
        printf("\033[0m");
        printf("│  %d",i+1);
    }
 }
    seppaligne(Jeu->longeur);
    retchr();
    lettres(Jeu);
    printf("\033[0m");
    printf("\n");
    afficheJoueur(Jeu);
}


void affichecoupvalide(Game * Jeu){
    // Jeu->co doit etre dans les bornes du tableau !!!
    chessboard * plateau = Jeu->plateau;
    char * pieces[6] ={"♟","♜","♞","♝","♛","♚"};
 clearscr();
 bordereau();
 coin();
 printf("\033[0m");
 if(Jeu->player == blanc ){
    for(int i = Jeu->hauteur -1;i>=0;i--){
        seppaligne(Jeu->longeur);
        retchr();
        for(int j = 0 ; j<Jeu->longeur; j++){
            printf("\033[0m");
            printf("│");
            int co_case[] = {i,j};
            if(plateau[i][j]==0x0){ estvalide(Jeu,co_case)?printf("\033[0;35m ⏺ "):printf("   ");}
            else {
                if(i == Jeu->co[0] && j == Jeu->co[1]){printf("\033[0;32m");} // couleur verte si case selectionne == piece joue
                else if(estvalide(Jeu,co_case)){ //verif si piece ateignable par la select
                    plateau[i][j]->couleur == Jeu->player ?  printf("\033[0;35m"):printf("\033[31m"); //Magenta si piece meme couleur rouge sinon
                }
                else plateau[i][j]->couleur == blanc ?  printf("\033[0;97m"):printf("\033[90m"); //Couleur pour les autres pieces
                printf(" %s ",pieces[plateau[i][j]->type -1]);
            }

        }
        printf("\033[0m");
        printf("│  %d",i+1);
    }
 }
 else {
    for(int i =0; i<Jeu->hauteur;i++){
        seppaligne(Jeu->longeur);
        retchr();
        for(int j = Jeu->longeur -1 ; j>=0; j--){
            printf("\033[0m");
            printf("│");
            int co_case[] = {i,j};
            if(plateau[i][j]==0x0){ estvalide(Jeu,co_case)?printf("\033[0;35m ⏺ "):printf("   ");}
            else {
                if(i == Jeu->co[0] && j == Jeu->co[1]){printf("\033[0;32m");} // couleur verte si case selectionne == piece joue
                else if(estvalide(Jeu,co_case)){ //verif si piece ateignable par la select
                    plateau[i][j]->couleur == Jeu->player ?  printf("\033[0;35m"):printf("\033[31m"); //Magenta si piece meme couleur rouge sinon
                }
                else plateau[i][j]->couleur == blanc ?  printf("\033[0;97m"):printf("\033[90m"); //Couleur pour les autres pieces
                printf(" %s ",pieces[plateau[i][j]->type -1]);
            }

        }
        printf("\033[0m");
        printf("│  %d",i+1);
    }
 }
    seppaligne(Jeu->longeur);
    retchr();
    lettres(Jeu);
    printf("\033[0m");
    printf("\n");
    afficheJoueur(Jeu);
}

void seppaligne(int longeur){
    // fait les epparations de lignes pour affiche plateau
    printf("\033[0m");
    retchr();
    for(int i = 0; i<longeur; i++){
    printf("┼───");}
    printf("┼");
}

void bordereau(){
    printf("\033[s");
    printf("\033[H\033[107m\033[30m Now playing < chess.c > │ Version by Mattéo & Stanislas \n");
    printf("\033[u");
}

void lettres(Game * Jeu){
    // affiches les lettres en dessous du plateau
    printf("\033[0m");
    if(Jeu->player == blanc){
    for(int i = 0; i < Jeu->longeur; i++){
    printf("  %c ", 'A'+i);}
    }
    if(Jeu->player == noir){
    for(int i = 0; i < Jeu->longeur; i++){
    printf("  %c ", 'A'+Jeu->longeur-1 -i );}
    }
    retchr();
}

void afficheJoueur(Game * Jeu){
    // affiche le joueur qui joue

    printf("\033[s"); //save la pos du curseur
    printf("\033[3;2H"); // va en ligne 2 col 2
    printf("\033[107;30m"); // background blanc clair et ecriure noire
    if(Jeu->winner == 0){
    printf("  PLAYER  ");}
    else printf("  WINNER  "); 
    printf("\033[4;2H");
    if(Jeu->player == blanc){
         printf("\033[47;30m  BLANC   \033[m");} //BG BLANC FG noir
    else {printf("\033[100;97m" ); printf("   NOIR   \033[m");} //BG noir_clair FG bLanc_clair
    printf("\033[m"); //reset les couleurs
    printf("\033[u"); //retourne le curseur a la pos sauvée
}