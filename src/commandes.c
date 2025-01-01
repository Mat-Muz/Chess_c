#include "commandes.h"
#include "Saves.h"
#include "init.h"

#define NB_CMD 5
int pass =0;

void exec_commande(Game * Jeu){
    switch (Jeu->commande)
        {
        case 1:
            //quit 
            printf("\n Interruption du programme \n");
            clean_Game(Jeu);
            exit(EXIT_SUCCESS);
            break;
        case 2:
            //save
            CreateSave(Jeu);
            break;
        case 3:
                printf("\n PRGM RESET \n");
                return;
                break;
        case 4:
            printf("\n-help : montre la liste des commandes \n");
            printf("-quit : quitte le programme \n");
            printf("-reset : relance le programme \n");
            printf("-save : Lance la sauvegarde de la partie \n");
            printf("-back: remonte en arrière de 1 coups \n");
            printf("\n");
            break;
        case 5:
            if (pass == 0){pass++; return; }
            char round[128];
            char dest[] = "./Save/AutoSave/";
            if(Jeu->player == noir){
                sprintf(round,"%d_%s",Jeu->round, "blanc");
            }
            else sprintf(round,"%d_%s",Jeu->round-1, "noir");
            strcat(dest, round);
            SaveLoad(dest,Jeu);
    }
    pass = 0;
    Jeu->commande = 0;
} 

int test_commande(char * text){
    char CMD_List[NB_CMD][255]={"quit","save","reset","help","back"};
    for(int i = 0; i<NB_CMD; i++){
        if (strcmp(text, CMD_List[i]) == 0){
            return i+1;
        }

    }
    return 0;
}