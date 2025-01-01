#include "Saves.h"
#include "input.h"
#include "init.h"

void CreateSave(Game * Jeu){
    FILE * Save;
    char filename[128];
    char dest[1024];
    printf("\n nom de la save :");
    fgets(filename, 128, stdin);
    filename[strcspn(filename, "\n")] = 0;

    strcpy(dest, "./Save/");
    strcat(dest, filename);


    Save = fopen(dest,"w");
    fprintf( Save ,"h: %d hauteur\nl: %d longeur \np: %d current player\nw: %d winner\nr: %d tour de jeu\ni:j;couleur;mvd;type #c'est pour les pieces\n", Jeu->hauteur, Jeu->longeur, Jeu->player, Jeu->winner, Jeu->round);
    for(int i = 0; i < Jeu->longeur; i++){
        for(int j = 0; j < Jeu->hauteur; j++){
            piece * lecture = Jeu->plateau[i][j];
            if(lecture == NULL){
            fprintf( Save ,"%d:%d\n",i,j);
            }
            else fprintf( Save ,"%d:%d;%d;%d;%d\n", i,j,lecture->couleur, lecture->mvd , lecture->type);
    }
    }

    fclose(Save);
    return;

}

int SelectSave(Game * Jeu){
    char filename[128];
    char dest[1024]; 
    printf("\n Quelle save veux-tu ouvrir :");
    fgets(filename, 128, stdin);
    filename[strcspn(filename, "\n")] = 0;
    strcpy(dest, "./Save/");
    strcat(dest, filename);
    return SaveLoad(dest, Jeu);
}

int SaveLoad(char dest[] ,Game * Jeu){
    FILE * Load;
    char buffer[255];
    Load = fopen(dest,"r");
     if(Load == NULL) {
        printf("Not able to open the file.");
        return -1;
    }
    clean_Game(Jeu);
    fgets(buffer, sizeof(buffer), Load);
    memmove(buffer, buffer+3, 200);
    Jeu->hauteur = atoi(buffer);

    fgets(buffer, sizeof(buffer), Load);
    memmove(buffer, buffer+3, 200);
    Jeu->longeur = atoi(buffer); 
    
    fgets(buffer, sizeof(buffer), Load);
    memmove(buffer, buffer+3, 200);
    Jeu->player = (int)strtol(buffer,NULL,10);

    
    fgets(buffer, sizeof(buffer), Load);
    memmove(buffer, buffer+3, 200);
    Jeu->winner = (int)strtol(buffer,NULL,10);

    fgets(buffer, sizeof(buffer), Load);
    memmove(buffer, buffer+3, 200);
    Jeu->round = (int)strtol(buffer,NULL,10);

    Jeu->plateau = (chessboard * ) creerplateau(Jeu->hauteur,Jeu->longeur);
    initplateau(Jeu, 0); // cree un tableau vide

    Jeu->plt_vld = (plateauvalide *) creerplt_vld(Jeu);
    initplt_vld(Jeu); //cree le plateau des coup valide a vide

    fgets(buffer, sizeof(buffer), Load); // saute une ligne

    while (fgets(buffer, sizeof(buffer), Load)) {
        int i = 0;
        int j = 0;
        char * lecteur;
        i = convertstrint(buffer);
        j = convertstrint(strchr(buffer, ':')+1);
        if(strchr(buffer, ';') != NULL){ // creée les pieces aux cases i,j 
            lecteur = strchr(buffer, ';')+1;
            int couleur = 0;
            (strstr(buffer, "-1") != NULL) ? (couleur = noir) : (couleur = blanc);  
            //printf(" couleur : %d \n", couleur);
            lecteur = strchr(lecteur, ';')+1;
            int moved = convertstrint(lecteur);
            lecteur = strchr(lecteur, ';')+1;
            int type = convertstrint(lecteur);
            Jeu->plateau[i][j] = malloc(sizeof(piece));
            piece * c_piece = Jeu->plateau[i][j];
            if ( Jeu->plateau[i][j] == 0x0){
                perror("Erreur d'allocation memoire");
                return -2;
            }
            c_piece->couleur = couleur;
            c_piece->mvd = moved;
            c_piece->type = type;
        }
        //else printf("rien \n");

    }
     fclose(Load);
    return 1;  

}

void Autosave(Game * Jeu){
    FILE * Save;
    char dest[] = "./Save/AutoSave/";
    char round[128];
    if(Jeu->player == blanc){ sprintf(round,"%d_%s",Jeu->round, "blanc");}
    else sprintf(round,"%d_%s",Jeu->round, "noir");
    strcat(dest, round);
    Save = fopen(dest,"w");
    fprintf( Save ,"h: %d hauteur\nl: %d longeur \np: %d current player\nw: %d winner\nr: %d tour de jeu\ni:j;couleur;mvd;type #c'est pour les pieces\n", Jeu->hauteur, Jeu->longeur, Jeu->player, Jeu->winner, Jeu->round);
    for(int i = 0; i < Jeu->longeur; i++){
        for(int j = 0; j < Jeu->hauteur; j++){
            piece * lecture = Jeu->plateau[i][j];
            if(lecture == NULL){
            fprintf( Save ,"%d:%d\n",i,j);
            }
            else fprintf( Save ,"%d:%d;%d;%d;%d\n", i,j,lecture->couleur, lecture->mvd , lecture->type);
    }
    }
    fclose(Save);
}