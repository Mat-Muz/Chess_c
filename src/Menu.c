#include "Menu.h"
#include "affichage.h"

struct termios originalTerm;

void afficheimage(char filename[]){
      FILE * Image;
      Image = fopen(filename,"r");
      if(Image == NULL) {
        printf("Not able to open the file.");
        return ;
      }
      char str[1024];
      coin();
      while (fgets(str, 1024, Image) != NULL) {
            str[strcspn(str, "\n")] = '\0';
            retchr();
            printf("%s", str);
      }
      fclose(Image);
      return;
}

void displayMenu(const char *Options[], int nboptions, int selected) {
    printf("\033[2K\r"); // Efface la ligne actuelle et replace le curseur au début
    char marge[128] = "\033[";
    strcat(marge,MARGE_GAUCHE);
    strcat(marge,"G");
    printf("%s     ",marge);
    for (int i = 0; i < nboptions; i++) {
        if (i == selected) {
            printf("\033[1;32m[%s]\033[0m     ", Options[i]); // Option sélectionnée en vert
        } else {
            printf("%s     ", Options[i]);
        }
    }
    fflush(stdout);
}

void menuManager(Menu * menu) {
    const char *mainMenu[] = {"New_game", "Last_Save", "Quitter"};
    const char *Page1[] = {"Classic-chess", "Custom", "Retour"};
    const char *subMenu2[] = {"Sub2-Option X", "Sub2-Option Y", "Retour"};

    const char **currentMenu = mainMenu; // Pointeur vers le menu actuel
    int menuSize = sizeof(mainMenu) / sizeof(mainMenu[0]); // Taille du menu actuel
    int selected = 0; // Option sélectionnée
    menu->page = 0; // Niveau du menu (0 = principal, 1 = sous-menu 1, 2 = sous-menu 2)

    printf("\n");
    displayMenu(currentMenu, menuSize, selected);

    while (1) {
        char c;
        read(STDIN_FILENO, &c, 1);

        if (c == '\033') { // Détection des flèches
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                if (seq[0] == '[') {
                    if (seq[1] == 'C' && selected < menuSize - 1) { // Flèche droite
                        selected++;
                    } else if (seq[1] == 'D' && selected > 0) { // Flèche gauche
                        selected--;
                    }
                }
            }
        } else if (c == '\n') { // Entrée pour sélectionner
            switch(menu->page) { 
            case 0: //Menu principal
                if (strcmp(mainMenu[selected], "Quitter") == 0) {
                    printf("\nVous avez quitté le programme.\n");
                    disableRawMode();
                    exit(EXIT_SUCCESS);
                    break;
                } else if (strcmp(mainMenu[selected], "New_game") == 0) {
                    currentMenu = Page1;
                    menuSize = sizeof(Page1) / sizeof(Page1[0]);
                    menu->page = 1;
                    selected = 0;
                } else if (strcmp(mainMenu[selected], "Last_Save") == 0) {
                    menu->savemode = 3;
                    return;

                }
                break;
            case 1 : 
                  if (strcmp(Page1[selected], "Classic-chess") == 0) {
                    menu->savemode=1;
                    return;
                  } else if (strcmp(Page1[selected], "Custom") == 0) {
                    menu->savemode=2;
                    return;
                  }
                  break;

            default:// Sous-menus
                if (strcmp(currentMenu[selected], "Retour") == 0) {
                    currentMenu = mainMenu;
                    menuSize = sizeof(mainMenu) / sizeof(mainMenu[0]);
                    menu->page = 0;
                    selected = 0;
                  }
            }

        } else if (c == 'q') { // Touche 'q' pour quitter
            printf("\nVous avez quitté le programme.\n");
            break;
        }

        displayMenu(currentMenu, menuSize, selected); // Réaffiche le menu actuel
    }
}

// Activer le mode brut (raw mode)
void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &originalTerm);
    term = originalTerm;
    term.c_lflag &= ~(ICANON | ECHO); // Désactiver le mode canonique et l'écho
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
// Restaurer le mode normal
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &originalTerm);
}

void main_menu(Menu * menu){
      menu->savemode =0;
      menu->page = 0;
      menu->couleur =0;
      clearscr();
      afficheimage("./Graphismes/Logo");
      
      enableRawMode();      
      menuManager(menu);
      disableRawMode();

      return;
}




