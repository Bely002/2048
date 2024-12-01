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
        while(!jeu.deplacement(dir)){
            cout << "Entrer commande : ";
            cin >> dir;
        }
        jeu.ajouterDeuxOuQuatre();
    }

    return 0;
}