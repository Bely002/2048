#include "./header/jeu.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using Plateau = vector<vector<int>>;
vector<string> listeCoups = {"H","B","G","D"};

string coupAleatoire() {
    return listeCoups[rand()%4];
}

vector<pair<int,int>> obtenirTuilesVides(Plateau plateau) {
    vector<pair<int,int>> tuilesVides = {};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(plateau[i][j]==0){
                tuilesVides.push_back({i,j});
            }
        }
    }
    return tuilesVides;
}

int finirJeu(Jeu jeu,string direction){
    string coup;
    jeu=deplacement(jeu,direction);
    while(!estTermine(jeu.plateau)){
        coup=coupAleatoire();
        while(jeu.plateau==deplacement(jeu,coup).plateau){
            coup=coupAleatoire();
        }
        jeu=deplacement(jeu,coup);
        jeu.plateau=ajouterDeuxOuQuatre(jeu.plateau);
    }
    return jeu.score;
}

string choisirCoup(Jeu jeu){
    string meilleurCoup;
    int meilleurMoyenne=0;
    int moyenne;
    for(auto coup:listeCoups){
        if(jeu.plateau!=deplacement(jeu,coup).plateau){
            moyenne=0;
            for(int i=0;i<100;i++){
                moyenne+=finirJeu(jeu,coup);
            }
            moyenne=moyenne/100.0;
            if(moyenne>meilleurMoyenne){
                meilleurMoyenne=moyenne;
                meilleurCoup=coup;
            }
        }
    }
    cout << meilleurCoup << endl;
    return meilleurCoup;
}

int main() {
    srand(time(0));
    Jeu jeu = {plateauInitial(), 0};

    while(!estTermine(jeu.plateau)){
        cout << "Score : " << jeu.score << endl;
        cout << dessine(jeu.plateau) << endl;
        jeu=deplacement(jeu,choisirCoup(jeu));
        jeu.plateau=ajouterDeuxOuQuatre(jeu.plateau);
    }

    cout << "Score : " << jeu.score << endl;
    cout << dessine(jeu.plateau) << endl;

    return 0;
}