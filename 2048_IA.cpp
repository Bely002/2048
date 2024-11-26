#include "./header/2048.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using Plateau = vector<vector<int>>;
vector<string> listeCoups = {"h","b","g","d"};

string coupAleatoire() {
    return listeCoups[rand()%4];
}

int finirJeu(Jeu jeu,int maxCoups) {
    string dir;
    int nbCoups=0;
    while(!jeu.estTermine() and nbCoups<maxCoups){
        cout << jeu.obtenirDessin() << endl;
        dir=coupAleatoire();
        while(!jeu.deplacement(dir)){
            dir=coupAleatoire();
        }
        jeu.ajouterDeuxOuQuatre();
        nbCoups++;
    }
    return jeu.score;
}

string choisirCoup(Jeu jeu){
    //....
    return "";
}

int main() {
    srand(time(0));
    Jeu jeu;

    cout << finirJeu(jeu,10) << endl;


    return 0;
}