#include "./2048.hpp"
#include <vector>

void Jeu::ajouterDeuxOuQuatre() {
    vector<pair<int,int>> tuilesVides;
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
}

void Jeu::echangerLignesEtColonnes() {
    int tmp;
    for(int i =1; i<4;i++){
        for(int j=0;j<i;j++){
            tmp=plateau[j][i];
            plateau[j][i]=plateau[i][j];
            plateau[i][j]=tmp;
        }
    }
}

void Jeu::fusionnerEtAlignerLesLignes(bool droite){
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
                    score+=plateau[i][j];
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
}

bool Jeu::deplacement(string direction) {
    Plateau plateauPrecedent = plateau;

    if(!(direction=="h" || direction=="d" || direction=="b" || direction=="g")) return false;

    if(direction=="h" || direction=="b"){
        echangerLignesEtColonnes();
    }

    fusionnerEtAlignerLesLignes(direction=="b" || direction=="d");

    if(direction=="h" || direction=="b"){
        echangerLignesEtColonnes();
    }

    return plateauPrecedent!=plateau;
}

bool Jeu::estTermine(){
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

string Jeu::obtenirDessin(){
    int maxTaille = tailleDuNombreLePlusLong(plateau);
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
                for(int k=0;k<maxTaille - to_string(plateau[(i-1)/2][j]).size();k++){
                    dessin+=" ";
                }
                dessin+=to_string(plateau[(i-1)/2][j])+" ";
            }
            dessin+="*\n";
        }
    }
    return dessin;
}

Jeu::Jeu() {
    plateau=vector<vector<int>>(4,vector<int>(4,0));
    ajouterDeuxOuQuatre();
    ajouterDeuxOuQuatre();
    score=0;
}

int tireDeuxOuQuatre() {
    return rand()%10==0 ? 4 : 2;
}

vector<int> retournerLigne(vector<int> ligne) {
    vector<int> resultat(4);
    for(int i=0;i<4;i++){
        resultat[3-i]=ligne[i];
    }
    return resultat;
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