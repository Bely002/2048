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
        dir=coupAleatoire();
        while(!jeu.deplacement(dir)){
            dir=coupAleatoire();
        }
        jeu.ajouterDeuxOuQuatre();
        nbCoups++;
    }
    return jeu.score;
}

int moyenneScores(Jeu jeu,int iterations,int maxCoups) {
    int moyenne=0;
    for(int i=0;i<iterations;i++){
        moyenne+=finirJeu(jeu,maxCoups);
    }
    moyenne=moyenne/iterations;
    return moyenne;
}

string choisirCoup(Jeu jeu,int iterations,int maxCoups){
    string meilleurCoup;
    int meilleurMoyenne=0;
    for(auto coup:listeCoups){
        Jeu copie=jeu;
        if(copie.deplacement(coup)){
            int moyenne=moyenneScores(copie,iterations,maxCoups);
            if(moyenne>meilleurMoyenne){
                meilleurMoyenne=moyenne;
                meilleurCoup=coup;
            }
        }
    }
    return meilleurCoup;
}

int main() {
    srand(time(0));
    Jeu jeu;
    int iterations=100;
    int maxCoups=10;

    while (!jeu.estTermine()){
        cout << jeu.score << endl;
        cout << jeu.obtenirDessin() << endl;
        jeu.deplacement(choisirCoup(jeu,iterations,maxCoups));
        jeu.ajouterDeuxOuQuatre();
    }

    cout << jeu.score << endl;
    cout << jeu.obtenirDessin() << endl;
    


    return 0;
}