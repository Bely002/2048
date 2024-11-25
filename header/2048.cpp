#include "./2048.hpp"
#include <vector>

void Jeu::initialiser() {
    plateau=vector<vector<int>>(4,vector<int>(4,0));
}

void Jeu::ajouterDeuxOuQuatre() {

}

int tireDeuxOuQuatre() {
    return rand()%10==0 ? 4 : 2;
}
