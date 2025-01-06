#include "Menu.h"

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

void affichageMenu(Menu * Menu){
      clearscr();
      int page = Menu->page;
      afficheimage("./Graphismes/Logo");

}





