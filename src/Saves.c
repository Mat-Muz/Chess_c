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
    fprintf( Save ,"h: %d hauteur\nl: %d longeur \np: %d current player\nw: %d winner\nr: %d tour de jeu\ni:j;couleur;type;mvd;pst #c'est pour les pieces\n", Jeu->hauteur, Jeu->longeur, Jeu->player, Jeu->winner, Jeu->round);
    for(int i = 0; i < Jeu->longeur; i++){
        for(int j = 0; j < Jeu->hauteur; j++){
            piece * lecture = Jeu->plateau[i][j];
            if(lecture == NULL){
            fprintf( Save ,"%d:%d\n",i,j);
            }
            else fprintf( Save ,"%d:%d;%d;%d;%d;%d\n", i,j,lecture->couleur, lecture->type, lecture->mvd , lecture->pst);
    }}
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
            int type = convertstrint(lecteur);
            lecteur = strchr(lecteur, ';')+1;
            int moved = convertstrint(lecteur);
            lecteur = strchr(lecteur, ';')+1;
            int past = convertstrint(lecteur);
            Jeu->plateau[i][j] = malloc(sizeof(piece));
            piece * c_piece = Jeu->plateau[i][j];
            if ( Jeu->plateau[i][j] == 0x0){
                perror("Erreur d'allocation memoire");
                return -2;
            }
            c_piece->couleur = couleur;
            c_piece->mvd = moved;
            c_piece->type = type;
            c_piece->pst = past;
            c_piece->coups = NULL;
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
    fprintf( Save ,"h: %d hauteur\nl: %d longeur \np: %d current player\nw: %d winner\nr: %d tour de jeu\ni:j;couleur;type;mvd;pst #c'est pour les pieces\n", Jeu->hauteur, Jeu->longeur, Jeu->player, Jeu->winner, Jeu->round);
    for(int i = 0; i < Jeu->longeur; i++){
        for(int j = 0; j < Jeu->hauteur; j++){
            piece * lecture = Jeu->plateau[i][j];
            if(lecture == NULL){
            fprintf( Save ,"%d:%d\n",i,j);
            }
            else fprintf( Save ,"%d:%d;%d;%d;%d;%d\n", i,j,lecture->couleur, lecture->type, lecture->mvd , lecture->pst);
    }
    }
    fclose(Save);
}



char* findMostRecentFile(const char *directoryPath) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    static char mostRecentFile[512]; // Tableau statique pour retourner la chaîne
    time_t mostRecentTime = 0;

    // Initialisation du chemin vide
    mostRecentFile[0] = '\0';

    // Ouvrir le répertoire
    dir = opendir(directoryPath);
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return NULL;
    }

    // Parcourir les fichiers du répertoire
    while ((entry = readdir(dir)) != NULL) {
        // Construire le chemin complet du fichier
        char filePath[512];
        snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, entry->d_name);

        // Ignorer les entrées "." et ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Récupérer les informations du fichier avec stat
        if (stat(filePath, &fileStat) == -1) {
            perror("Erreur avec stat");
            continue;
        }

        // Vérifier si c'est un fichier régulier
        if (S_ISREG(fileStat.st_mode)) {
            // Comparer les timestamps pour trouver le fichier le plus récent
            if (fileStat.st_mtime > mostRecentTime) {
                mostRecentTime = fileStat.st_mtime;
                strncpy(mostRecentFile, filePath, sizeof(mostRecentFile));
            }
        }
    }

    // Fermer le répertoire
    closedir(dir);

    // Retourner le fichier le plus récent ou NULL si aucun fichier trouvé
    return (mostRecentFile[0] != '\0') ? mostRecentFile : NULL;
}

void Last_save_Load(Game * Jeu){

    char *Last_save = findMostRecentFile("./Save/AutoSave/");
    
    if (Last_save != NULL) {
        printf("Le fichier le plus récent est : %s\n", Last_save);
        SaveLoad(Last_save, Jeu);
    } else {
        printf("Aucun fichier trouvé dans le répertoire.\n");
    }



}


void Clear_Auto_Saves() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Ouvrir le répertoire
    dir = opendir("./Save/AutoSave/");
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    // Parcourir les fichiers et dossiers du répertoire
    while ((entry = readdir(dir)) != NULL) {
        // Construire le chemin complet du fichier
        char filePath[512];
        snprintf(filePath, sizeof(filePath), "%s/%s", "./Save/AutoSave", entry->d_name);


        if (stat(filePath, &fileStat) == -1) {
            perror("stat error");
            continue;
        }
        // Vérifier si c'est un fichier régulier avant de le supprimer
        if (S_ISREG(fileStat.st_mode)) {
            if (unlink(filePath) == 0) {
            } else {
                perror("Erreur lors de la suppression du fichier ");
            }
        } 
        }

    // Fermer le répertoire
    closedir(dir);
}