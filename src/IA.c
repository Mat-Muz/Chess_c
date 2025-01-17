#include "IA.h"

void Ordi_move(Game * Jeu){
      IA * ordi = Jeu->ordi;
      chessboard * plateau = Jeu->plateau;
      int casedepart[2];
      int casearrive[2];
      remplir_ordi(Jeu);
      random :
      int r = rand()%32 ;
      co * piece_choisie = ordi->pieces;
      for(int i = 0; i<= r ; i++){
            piece_choisie = piece_choisie->suiv;
      }
       casedepart[0] = piece_choisie->chiffre;
       casedepart[1] = piece_choisie->lettre;
      if(plateau[casedepart[0]][casedepart[1]]->coups == NULL) goto random;
      r = rand()%32;
      co * case_arrive = ordi->pieces;
            for(int i = 0; i<= r ; i++){
            case_arrive = plateau[casedepart[0]][casedepart[1]]->coups->suiv;
      }
       casearrive[0] = case_arrive->chiffre;
       casearrive[1] = case_arrive->lettre;
      piece_mv(Jeu , casedepart, casearrive);
      supp_co(&(ordi->pieces));
      clear_coup(Jeu);
}



void remplir_ordi(Game * Jeu){
int hauteur = Jeu->hauteur; 
int longeur = Jeu->longeur;
IA * ordi = Jeu->ordi;
    for(int i =0; i<hauteur;i++){
        for(int j = 0; j <longeur; j++){
            if(Jeu->plateau[i][j] != 0X0 && Jeu->plateau[i][j]->couleur == ordi->couleur){
                  ordi->pieces = ajouter_co(ordi->pieces, i , j);
            }
        }
    }
}

