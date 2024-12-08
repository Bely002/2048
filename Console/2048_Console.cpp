#include "../header/2048.hpp"
#include <vector>
#include <iostream>

using namespace std;
using Plateau = vector<vector<int>>;

int main(){
    srand(time(0));
    Jeu jeu;

    string dir;
    while(!jeu.estTermine()){
        cout << "Score : " << jeu.score << endl;
        cout << jeu.obtenirDessin() << endl;
        cout << "Entrer commande : ";
        cin >> dir;
        if (dir=='q') break;
        while(!jeu.deplacement(dir)){
            cout << "Entrer commande : ";
            cin >> dir;
            if (dir=='q') break;
        }
        if (dir=='q') break;
        jeu.ajouterDeuxOuQuatre();
    }

    cout << "***GAME OVER***" << endl;
    cout << "Score : " << jeu.score << endl;
    cout << jeu.obtenirDessin() << endl;


    return 0;
}