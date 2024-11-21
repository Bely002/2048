#include <iostream>
#include <vector>
#include <string>
using namespace std;

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

using Plateau = vector<vector<int>>;

struct Jeu{
    Plateau plateau;
    int score;
};

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre() {
    return rand()%10==0 ? 4 : 2;
}

/** génère un plateau de dimensions 4*4 ne contenant que des 0
 *  @return un plateau vide
 **/
Plateau plateauVide() {
    return vector<vector<int>>(4,vector<int>(4,0));
}

/** génère deux nombres sur des cases aléatoires d'un plateau vide
 *  @return un plateau en début de jeu
 **/
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

/**
 * Ajoute un quatre ou un deux à la place d'un zero
 * @param plateau le plateau
 * @return le plateau avec un quatre ou un deux à la place d'un ancien zero
**/
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

/**
 * Echange les lignes et les colonnes du plateau
 * @param plateau le plateau
 * @return le plateau avec les lignes et les colonnes echangees 
 **/

Plateau echangerLignesEtColonnes(Plateau plateau) {
    Plateau resultat(4,vector<int>(4));
    for(int i =0; i<4;i++){
        for(int j=0;j<4;j++){
            resultat[i][j]=plateau[j][i];
        }
    }
    return resultat;
}

/** 
 * retourne une ligne du tableau
 * @param ligne un tableau a 4 entiers
 * @return la ligne retournee
**/

vector<int> retournerLigne(vector<int> ligne) {
    vector<int> resultat(4);
    for(int i=0;i<4;i++){
        resultat[3-i]=ligne[i];
    }
    return resultat;
}

/** 
 * Fusionne et aligne (vers la droite ou la gauche) les éléments des lignes du plateau
 * @param jeu le jeu avec le plateau et le score
 * @param droite qui specifie s'il faut aligner a droite
 * @return le jeu avec le plateau et le score actualises
**/

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


/** déplace les tuiles d'un plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param Jeu le jeu avec le plateau
 *  @param direction la direction
 *  @return le jeu avec le plateau déplacé dans la direction indiqué et le score mis à jour
 **/
Jeu deplacement(Jeu jeu, int direction) {
    Plateau& plateau = jeu.plateau;

    if(direction==KEY_UP || direction==KEY_DOWN){
        plateau = echangerLignesEtColonnes(plateau);
    }

    jeu = fusionnerEtAlignerLesLignes(jeu,direction==KEY_DOWN || direction==KEY_RIGHT);

    if(direction==KEY_UP || direction==KEY_DOWN){
        plateau = echangerLignesEtColonnes(plateau);
    }

    return jeu;
}

/** 
 * cherche la taille du nombre le plus long dans le plateau
 * @param plateau le plateau
 * @return la taille du nombre le plus long
**/
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

/** permet de savoir si une partie est terminée
 *  @param plateau un plateau
 *  @return true si le plateau est vide, false sinon
 **/
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
 

/** permet de savoir si une partie est gagnée
 * @param plateau un plateau
 * @return true si le plateau contient un 2048, false sinon
 **/

bool estGagnant(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++) {// on parcourt les lignes
        for (int j = 0; j < plateau.size(); j++) {// on parcourt les collonnes
            if (plateau[i][j]==2048 )// si une des cases du plateau est egal a 2048
                return true;   }
    }
    return false;
}