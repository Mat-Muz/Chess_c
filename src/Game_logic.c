#include "Game_logic.h"



int playermove(Game * Jeu){

    chessboard * plateau = Jeu->plateau;
    int casedepart[2];
    int casearrive[2];
    check_detection(Jeu);
    selectcoord(Jeu, 0); // case de départ
    if(Jeu->commande){return -1;} //tt commande demandant de sortir de cette fonction
    casedepart[0] = Jeu->co[0];
    casedepart[1] =  Jeu->co[1];
    piece * current_piece = plateau[casedepart[0]][casedepart[1]];
    
    affichecoupvalide(Jeu);
    check_detection(Jeu);
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
        
        //Detection mort du roi
        if(plateau[casearrive[0]][casearrive[1]]->type == roi){
            if (plateau[casearrive[0]][casearrive[1]]->couleur == blanc )
            {
            Jeu->winner = noir;
            }
            else  Jeu->winner = blanc;
        }

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
    plateau[casearrive[0]][casearrive[1]]->mvd = Jeu->round;
    return 1; // Success
}



void check_detection(Game * Jeu){
      int hauteur = Jeu->hauteur;
      int longeur = Jeu->longeur;
      chessboard* plateau = Jeu->plateau;
      for(int i = 0; i<hauteur; i++){
            for(int j = 0; j<longeur; j++){
                  if (plateau[i][j] != 0x0 && plateau[i][j]->type == roi && case_attaque(Jeu, i, j))
                  {     
                        if(plateau[i][j]->couleur == Jeu->player){
                        printf("\033[s");
                        coin();
                        printf("\033[1A\033[31m Le roi est en echec \033[0m\033[u");
                        return ;
                        }

                  }
                  
            }     
      }

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