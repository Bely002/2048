#include "./2048.hpp"
#include <iostream>
#include <vector>
#include <string>

#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl
using namespace std;
using Plateau = vector<vector<int>>;

void echangerLignesEtColonnesTest() {
    Jeu jeu;
    jeu.plateau={
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    jeu.echangerLignesEtColonnes();
    CHECK(jeu.plateau==(Plateau{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}));

    jeu.plateau={
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    jeu.echangerLignesEtColonnes();
    CHECK(jeu.plateau==(Plateau{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}));

    jeu.plateau={
        {0,1,3,0},
        {0,1,0,0},
        {2,0,1,0},
        {0,0,4,1}
    };
    jeu.echangerLignesEtColonnes();
    CHECK(jeu.plateau==(Plateau{{0,0,2,0},{1,1,0,0},{3,0,1,4},{0,0,0,1}}));
}

void fusionnerEtAlignerLesLignesTest() {
    Jeu jeu;
    jeu.plateau={
        {0,0,0,2},
        {0,0,0,4},
        {0,0,0,8},
        {0,0,0,16}
    };
    jeu.fusionnerEtAlignerLesLignes(false);
    CHECK(jeu.plateau==(Plateau{{2,0,0,0},{4,0,0,0},{8,0,0,0},{16,0,0,0}}));

    jeu.plateau={
        {2,0,0,2},
        {0,0,0,4},
        {8,0,0,8},
        {0,0,0,16}
    };
    jeu.fusionnerEtAlignerLesLignes(false);
    CHECK(jeu.plateau==(Plateau{{4,0,0,0},{4,0,0,0},{16,0,0,0},{16,0,0,0}}));

    jeu.plateau={
        {4,2,0,2},
        {4,0,2,4},
        {8,0,0,8},
        {16,0,0,16}
    };
    jeu.fusionnerEtAlignerLesLignes(true);
    CHECK(jeu.plateau==(Plateau{{0,0,4,4},{0,4,2,4},{0,0,0,16},{0,0,0,32}}));
}

void deplacementTest() {
    Jeu jeu;
    jeu.plateau={
        {0,0,0,2},
        {0,0,0,4},
        {0,0,0,8},
        {0,0,0,16}
    };
    jeu.deplacement("h");
    CHECK(!jeu.deplacement("h"));
    CHECK(!jeu.deplacement("b"));
    CHECK(!jeu.deplacement("d"));
    CHECK(!jeu.deplacement("bonjour"));
    CHECK(jeu.deplacement("g"));

    jeu.plateau={
        {0,2,0,2},
        {0,0,0,4},
        {0,0,0,8},
        {0,0,0,16}
    };
    jeu.deplacement("g");
    CHECK(jeu.plateau==(Plateau{{4,0,0,0},{4,0,0,0},{8,0,0,0},{16,0,0,0}}));
    jeu.deplacement("d");
    CHECK(jeu.plateau==(Plateau{{0,0,0,4},{0,0,0,4},{0,0,0,8},{0,0,0,16}}));
    jeu.deplacement("h");
    CHECK(jeu.plateau==(Plateau{{0,0,0,8},{0,0,0,8},{0,0,0,16},{0,0,0,0}}));
    jeu.deplacement("b");
    CHECK(jeu.plateau==(Plateau{{0,0,0,0},{0,0,0,0},{0,0,0,16},{0,0,0,16}}));
}

void estTermineTest() {
    Jeu jeu;
    jeu.plateau={
        {0,0,0,2},
        {0,0,0,4},
        {0,0,0,8},
        {0,0,0,16}
    };
    CHECK(!jeu.estTermine());

    jeu.plateau={
        {4,2,4,2},
        {2,4,2,4},
        {4,8,4,8},
        {8,16,8,16}
    };
    CHECK(jeu.estTermine());

    jeu.plateau={
        {4,2,4,2},
        {2,4,2,4},
        {4,0,4,8},
        {8,16,8,16}
    };
    CHECK(!jeu.estTermine());

    jeu.plateau={
        {4,2,4,2},
        {2,4,2,4},
        {4,8,4,8},
        {4,16,8,16}
    };
    CHECK(!jeu.estTermine());
}

int main() {

    echangerLignesEtColonnesTest();
    fusionnerEtAlignerLesLignesTest();
    deplacementTest();
    estTermineTest();

    return 0;
}
