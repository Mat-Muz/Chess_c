#include "Game_logic.h"



int playermove(Game * Jeu){
    chessboard * plateau = Jeu->plateau;
    int casedepart[2];
    int casearrive[2];
    check_detection(Jeu, false);
    selectcoord(Jeu, 0); // case de départ
    if(Jeu->commande){return -1;} //tt commande demandant de sortir de cette fonction
    casedepart[0] = Jeu->co[0];
    casedepart[1] =  Jeu->co[1];
    piece * current_piece = plateau[casedepart[0]][casedepart[1]];
    
    affichecoupvalide(Jeu);
    check_detection(Jeu,false);
    selectcoord(Jeu, 1); // case d'arrivée
    if(Jeu->commande){return -1;} //tt commande demandant de sortir de cette fonction
    casearrive[0] = Jeu->co[0];
    casearrive[1] =  Jeu->co[1];

    //retry
    if (casearrive[1] == casedepart[1] && casearrive[0]==casedepart[0])
    {
        return 0;
    }
    
    //Mouvement

    if(plateau[casearrive[0]][casearrive[1]] != 0x0){
        free(plateau[casearrive[0]][casearrive[1]]) ; 
    }
    plateau[casearrive[0]][casearrive[1]] = plateau[casedepart[0]][casedepart[1]];
    plateau[casedepart[0]][casedepart[1]] = 0x0;
    if(plateau[casearrive[0]][casearrive[1]]->type == pion){
            if ( (plateau[casearrive[0]][casearrive[1]]->couleur == blanc && casearrive[0]==Jeu->hauteur-1 ) || (plateau[casearrive[0]][casearrive[1]]->couleur == noir && casearrive[0]==0))
            {
            pawnpromote(Jeu, casearrive);
            }
            //Google en passant 
            if(plateau[casearrive[0]-current_piece->couleur][casearrive[1]] != NULL && plateau[casearrive[0]-current_piece->couleur][casearrive[1]]->type == pion && plateau[casearrive[0]-current_piece->couleur][casearrive[1]]->couleur != current_piece->couleur && (plateau[casearrive[0]-current_piece->couleur][casearrive[1]]->mvd == Jeu->round || plateau[casearrive[0]-current_piece->couleur][casearrive[1]]->mvd == Jeu->round-1))
            {
                  free(plateau[casearrive[0]-current_piece->couleur][casearrive[1]]);
                  plateau[casearrive[0]-current_piece->couleur][casearrive[1]] = 0x0;
            }
        }
    if(plateau[casearrive[0]][casearrive[1]]->type == roi && casearrive[0] == casearrive[0] ){
        if(casedepart[1]-casearrive[1] == -2){
        //roque king side
        int j;
        for(j = casearrive[1]; (plateau[casearrive[0]][j] == 0x0 || plateau[casearrive[0]][j]->type != tour );j++){}
            plateau[casearrive[0]][casearrive[1]-1] = plateau[casearrive[0]][j];
            plateau[casearrive[0]][j] = 0X0;
            plateau[casearrive[0]][casearrive[1]-1]->mvd = Jeu->round;
        }else if (casedepart[1]-casearrive[1] == 2){
            //roque queen side
            int j;
            for(j = casearrive[1]; ( plateau[casearrive[0]][j] == 0x0 || plateau[casearrive[0]][j]->type != tour );j--){}
            plateau[casearrive[0]][casearrive[1]+1] = plateau[casearrive[0]][j];
            plateau[casearrive[0]][j] = 0X0;
            plateau[casearrive[0]][casearrive[1]+1]->mvd = Jeu->round;
        }
    }

    plateau[casearrive[0]][casearrive[1]]->pst = plateau[casearrive[0]][casearrive[1]]->mvd;
    plateau[casearrive[0]][casearrive[1]]->mvd = Jeu->round;
    return 1; // Success
}



bool check_detection(Game * Jeu, bool silencieux){
      int hauteur = Jeu->hauteur;
      int longeur = Jeu->longeur;
      chessboard* plateau = Jeu->plateau;
      for(int i = 0; i<hauteur; i++){
            for(int j = 0; j<longeur; j++){
                  if (plateau[i][j] != 0x0 && plateau[i][j]->type == roi && case_attaque(Jeu, i, j))
                  {     
                   if(plateau[i][j]->couleur == Jeu->player){
                        if(silencieux == false){
                        printf("\033[s");
                        coin();
                        printf("\033[1A\033[31m Le roi est en echec \033[0m\033[u");
                        }
                        return true;
                        }

                  }
                  
            }     
      }
      return false;

}


bool case_attaque(Game * Jeu, int i, int j){
      plateauvalide * plt_valid = Jeu->plt_vld;
      int couleur_case = Jeu->plateau[i][j]->couleur;
      p_liste * tete = plt_valid[i][j];
      while (tete !=NULL)
      {
            if(tete->p->couleur != couleur_case){
                  return true;
            }
            tete = tete->suiv;
      }
      return false;
}

bool player_cant_mv(Game * Jeu){
    for(int i = 0; i<Jeu->hauteur; i++){
        for(int j = 0; j<Jeu->longeur; j++){
            p_liste * temp = Jeu->plt_vld[i][j];
            while(temp != NULL){
                if(temp->p->couleur == Jeu->player){
                    return false;
                }
                temp = temp->suiv;
            }
        }
    }
    return true;
}

int fin_de_partie(Game * Jeu){
      bool check = check_detection(Jeu,true);
      bool nomv = player_cant_mv(Jeu);
      if (check && nomv){Jeu->winner = -Jeu->player; return 1;} //Check mate
      if (nomv && !check){Jeu->winner = 2*Jeu->player; return 2;} //PAT      
      return 0;
}