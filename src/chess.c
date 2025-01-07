#include "chess.h"
#include "affichage.h"
#include "Saves.h"
#include "input.h"
#include "init.h"
#include "Validation_coups.h"
#include "Game_logic.h"
#include "commandes.h"
#include "Menu.h"

void tour2jeu(Game * );



int main(){
    Game * Jeu = (Game *) malloc(sizeof(Game));
    Menu * menu = (Menu *) malloc(sizeof(Menu));
    menu->Jeu = Jeu;
    Jeu->menu = menu;
    clean_Game(Jeu);
    start:
    if(Jeu->commande == 5){
    exec_commande(Jeu);}
    else{
    main_menu(menu);
    clean_Game(Jeu);
    
    switch(menu->savemode){

        case 1:
        Jeu->hauteur = 8;
        Jeu->longeur = 8;
        Jeu->player = blanc;
        Jeu->winner = 0;
        Jeu->co[0] = -1;
        Jeu->co[1] = -1;
        Jeu->plateau = creerplateau(8,8);
        initplateau(Jeu, 1);
        Jeu->plt_vld = (plateauvalide *) creerplt_vld(Jeu);
        initplt_vld(Jeu); //cree le plateau des coup valide a vide
        break;
        case 2:
            while(SelectSave(Jeu) != 1){}
            break;
    }
    }
 

    /*
 
    
    initplateau(Jeu);
    

    //CreateSave(Jeu);*/
    
    if(Jeu->round == 0){Jeu->round = 1;}
    while(Jeu->winner == 0){
    
    tour2jeu(Jeu); 
    if(Jeu->commande){break;}
    }

    if(Jeu->commande == 3 || Jeu->commande == 5){goto start;} 
    Jeu->player = Jeu->winner;
    afficheplateau(Jeu);
    clean_Game(Jeu);
    return 0;
}



//gameloop


void tour2jeu(Game * Jeu ){

    
    Jeu->co[0] = -1;
    Jeu->co[1] = -1;

    if (Jeu->player == 0 ){Jeu->player = blanc;}
    
    afficheplateau(Jeu);
    
    if (Jeu->player == blanc){
        Autosave(Jeu);
        clear_plt_vld(Jeu);
        pop_plt_vld(Jeu);
        while ( !playermove(Jeu)){
                Jeu->co[0] = -1;
                Jeu->co[1] = -1;
            afficheplateau(Jeu);
            if(Jeu->commande){return;}//tt commande demandant de sortir de cette fonction 
        }
        if(Jeu->commande){return;}//tt commande demandant de sortir de cette fonction

        //suite
        Jeu->player = noir;
    }
    Jeu->co[0] = -1;
    Jeu->co[1] = -1;
    if (Jeu->winner != 0){return;}
    
    afficheplateau(Jeu);

    if (Jeu->player==noir){
        Autosave(Jeu);
        clear_plt_vld(Jeu);
        pop_plt_vld(Jeu);
        while ( !playermove(Jeu)){
                Jeu->co[0] = -1;
                Jeu->co[1] = -1;
            afficheplateau(Jeu);
            if(Jeu->commande){return;} //tt commande demandant de sortir de cette fonction 
        }
        if(Jeu->commande){return;}//tt commande demandant de sortir de cette fonction
        //suite 
        Jeu->player = 0;
    }
    Jeu->round++;
    
}









