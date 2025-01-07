#include "input.h"
#include "affichage.h"
#include "commandes.h"
#include "Validation_coups.h"

void selectcoord(Game* Jeu, int cas){
    char coordonne[255] = "\0";
    bool coupvalide = false;
    int lettre = 0;
    int chiffre = 0;
    int coarrive[2];
    
    while(!coupvalide){
    lettre = 0 ;
    chiffre = 0;
    if(cas == 0){ printf("choisis ta case de départ : "); } else {printf("choisis ta case de d'arrivée : ");}

    user_text_input(Jeu,coordonne);
    if(Jeu->commande){return;} //tt commande demandant de sortir de cette fonction 
    int i = 0;
    for( i = 0 ; ('A'<= coordonne[i] && 'Z'>= coordonne[i]) || ('a'<= coordonne[i] && 'z'>= coordonne[i]) ; i++){
        if ( 'A'<= coordonne[i] && 'Z' >= coordonne[i]){ coordonne[i] = ( coordonne[i]-'A' ) + 'a';}
        lettre = coordonne[i]-'a' + lettre*26;
    }
    for (int j = i ; ('0' <= coordonne[j] && '9' >= coordonne[j]) ; j++){
         chiffre = coordonne[j]-'0' + chiffre*10;
    }
    chiffre--;
    
    switch (cas){
        case 0: //case de départ
            if (chiffre == -1 || lettre == -1 || chiffre>=Jeu->hauteur || lettre>=Jeu->longeur){
                printf("essaie une case qui existe \n");
                coupvalide = false;}
            else if (Jeu->plateau[chiffre][lettre] == NULL || Jeu->plateau[chiffre][lettre]->couleur != Jeu->player){ 
                printf("Tu ne peux bouger que tes pions \n");
                coupvalide = false; }
            else coupvalide=true;
            break;
        case 1: //case d'arrivée
            
            coarrive[0] = chiffre;
            coarrive[1] = lettre;
            if (chiffre == -1 || lettre == -1 || chiffre>=Jeu->hauteur || lettre>=Jeu->longeur){
                printf("essaie une case qui existe \n");
                coupvalide = false;}
            else if ( estvalide(Jeu,coarrive)){ 
                coupvalide = true; }
            else if (Jeu->plateau[chiffre][lettre] == Jeu->plateau[Jeu->co[0]][Jeu->co[1]]){
                return;}
            else {
                coupvalide=false;
                printf("Essaie un coup possible \n");
            }
            break;
    }
    printf("\033[m");
    }
    Jeu->co[0] = chiffre;
    Jeu->co[1] = lettre;

}

void pawnpromote(Game * Jeu, int co[]){
     char u[3] = "\0";
     int promotion = 0; 
     bool inputvalid = false;
     afficheplateau(Jeu);
     while(!inputvalid){
        printf("ecrit le chiffre correspondant a la piece que tu veux : \n 1.♜  2.♞  3.♝  4.♛  \n");
        fgets(u, 3, stdin);
        if ('1' <= u[0] && '4' >= u[0]){
            promotion = u[0]-'0' +1;
            inputvalid = true;
        }
    }
    Jeu->plateau[co[0]][co[1]]->type = promotion;
}

int convertstrint(char text[]){
    int res =0;
    for (int j = 0 ; ('0' <= text[j] && '9' >= text[j]) ; j++){
         res = text[j]-'0' + res*10;
    }
    return res;
}

void user_text_input(Game * Jeu,char * text){
    fgets(text,sizeof(text),stdin);
    text[strcspn(text, "\n")] = '\0';
    Jeu->commande = test_commande(text);
    exec_commande(Jeu);
    return;
}


