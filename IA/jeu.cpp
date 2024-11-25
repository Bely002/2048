#include "./header/jeu.hpp"
#include <vector>
#include <string>

using namespace std;
using Plateau = vector<vector<int>>;

int tireDeuxOuQuatre() {
    return rand()%10==0 ? 4 : 2;
}

Plateau plateauVide() {
    return vector<vector<int>>(4,vector<int>(4,0));
}

Plateau plateauInitial(){
    Plateau plateau = plateauVide();
    int placeAleatoire;
    placeAleatoire=rand()%16; // On prend un nombre aléatoire entre 0 et 15
    plateau[placeAleatoire/4][placeAleatoire%4]=tireDeuxOuQuatre();
    while(plateau[placeAleatoire/4][placeAleatoire%4]!=0){ // On vérifie si la tuile n'est pas égale à 0
        placeAleatoire=rand()%16; //Si elle m'est pas égale alors on change de placeAleatoire
    }
    plateau[placeAleatoire/4][placeAleatoire%4]=tireDeuxOuQuatre();
    return plateau;
}

Plateau ajouterDeuxOuQuatre(Plateau plateau) {
    vector<pair<int,int>> tuilesVides = {};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(plateau[i][j]==0){
                tuilesVides.push_back({i,j});
            }
        }
    }
    if(tuilesVides.size()>0){
        int placeAleatoire = rand()%(tuilesVides.size());
        plateau[tuilesVides[placeAleatoire].first][tuilesVides[placeAleatoire].second] = tireDeuxOuQuatre();
    }
    return plateau;
}

Plateau echangerLignesEtColonnes(Plateau plateau) {
    Plateau resultat(4,vector<int>(4));
    for(int i =0; i<4;i++){
        for(int j=0;j<4;j++){
            resultat[i][j]=plateau[j][i];
        }
    }
    return resultat;
}

vector<int> retournerLigne(vector<int> ligne) {
    vector<int> resultat(4);
    for(int i=0;i<4;i++){
        resultat[3-i]=ligne[i];
    }
    return resultat;
}

Jeu fusionnerEtAlignerLesLignes(Jeu jeu,bool droite) {
    Plateau& plateau = jeu.plateau;
    for(int i=0;i<4;i++){
        if(droite){
            plateau[i]=retournerLigne(plateau[i]);
        }
        for(int j=0;j<4;j++){
            for(int k=j+1;k<4;k++){
                if(plateau[i][j]==0 && plateau[i][k]!=0){
                    plateau[i][j]=plateau[i][k];
                    plateau[i][k]=0;
                }
                if(plateau[i][j]==plateau[i][k] && plateau[i][k]!=0){
                    plateau[i][j]*=2;
                    jeu.score+=plateau[i][j];
                    plateau[i][k]=0;
                    break;
                }if(plateau[i][k]!=0 && plateau[i][k]!=plateau[i][j]){
                    break;
                }
            }
        }
        if(droite){
            plateau[i]=retournerLigne(plateau[i]);
        }
    }
    return jeu;
}

Jeu deplacement(Jeu jeu, string direction) {
    Plateau& plateau = jeu.plateau;

    if(direction=="H" || direction=="B"){
        plateau = echangerLignesEtColonnes(plateau);
    }

    jeu = fusionnerEtAlignerLesLignes(jeu,direction=="B" || direction=="D");

    if(direction=="H" || direction=="B"){
        plateau = echangerLignesEtColonnes(plateau);
    }

    return jeu;
}

int tailleDuNombreLePlusLong(Plateau plateau) {
    int max=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(to_string(plateau[i][j]).size()>max){
                max=to_string(plateau[i][j]).size();
            }
        }
    }
    return max;
}

string dessine(Plateau p){
    int maxTaille = tailleDuNombreLePlusLong(p);
    string dessin  = "";
    for(int i=0;i<9;i++){
        if(i%2==0){
            for(int j=0; j<13+maxTaille*4;j++){
                dessin+= "*";
            }
            dessin+="\n";
        }else{
            for(int j=0;j<4;j++){
                dessin+= "* ";
                for(int k=0;k<maxTaille - to_string(p[(i-1)/2][j]).size();k++){
                    dessin+=" ";
                }
                dessin+=to_string(p[(i-1)/2][j])+" ";
            }
            dessin+="*\n";
        }
    }
    return dessin;
}

bool estTermine(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++) { // on parcourt les lignes
        for (int j = 0; j < plateau.size(); j++) {// on parcourt les collonnes
            if (plateau[i][j]==0) return false;
            if (j<= 2){
                if(plateau[i][j] == plateau[i][j+1]) return false;  // si la case a la doite de [i][j] a la meme valeur on peut continuer a jouer
            }
            if (i<=2) {
                if (plateau[i][j] == plateau[i+1][j] )return false ; // si la case en dessous de [i][j] a la meme valeur on peut continuer de jouer
                    
            }
        }
    }
    return !(plateau[3][3]==plateau[2][3] or plateau[3][3]==plateau[3][2]);
    
}

bool estGagnant(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++) {// on parcourt les lignes
        for (int j = 0; j < plateau.size(); j++) {// on parcourt les collonnes
            if (plateau[i][j]==2048 )// si une des cases du plateau est egal a 2048
                return true;   }
    }
    return false;
}