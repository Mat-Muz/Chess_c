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

void affichageMenu(Menu * menu){
int page = menu->page; 
switch(page){
      case 0:
      clearscr();
      afficheimage("./Graphismes/Logo");
      printf("\n              1. New-game      2.         3.       \n");
      changepage(menu);

      break;
      
      
      case 1:
      clearscr();
      coin();
      printf("0.Main menu 1. Classic_chess      2.Custom\n");
      char buffer[8];
      fgets(buffer,sizeof(buffer),stdin);
      int option=atoi(buffer);
      if(option == 0){menu->page = 0; return;}
      menu->options = option;
      return;
}
}

void changepage(Menu * menu){
      char buffer[8];
      fgets(buffer,sizeof(buffer),stdin);
      menu->page=atoi(buffer);
      printf("%d",menu->page);
}

void main_menu(Menu * menu){
      menu->options =0;
      menu->page = 0;
      menu->couleur =0;
      while(menu->options == 0){
      affichageMenu(menu);
      }
      return;
}




