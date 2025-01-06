#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

struct termios originalTerm;

void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &originalTerm);
    term = originalTerm;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &originalTerm);
}

void displayMenu(const char *menu[], int menuSize, int selected) {
    printf("\033[2J\033[H"); // Efface l'écran et replace le curseur en haut à gauche
    for (int i = 0; i < menuSize; i++) {
        if (i == selected) {
            printf("> \033[1;32m%s\033[0m\n", menu[i]); // Surligne l'option sélectionnée
        } else {
            printf("  %s\n", menu[i]);
        }
    }
}

int main() {
    enableRawMode();

    const char *menu[] = {"Option 1", "Option 2", "Option 3", "Quitter"};
    int menuSize = sizeof(menu) / sizeof(menu[0]);
    int selected = 0;

    while (1) {
        displayMenu(menu, menuSize, selected);

        char c;
        read(STDIN_FILENO, &c, 1);

        if (c == 'q') break; // Quitter avec 'q'
        if (c == '\033') { // Touche d'échappement
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                if (seq[0] == '[') {
                    if (seq[1] == 'A' && selected > 0) selected--;        // Flèche haut
                    else if (seq[1] == 'B' && selected < menuSize - 1) selected++; // Flèche bas
                }
            }
        } else if (c == '\n') { // Entrée pour sélectionner
            printf("\033[2J\033[H"); // Efface l'écran
            printf("Vous avez sélectionné : %s\n", menu[selected]);
            break;
        }
    }

    disableRawMode();
    printf("Mode brut désactivé. Au revoir !\n");
    return 0;
}
