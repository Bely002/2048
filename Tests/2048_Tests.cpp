#include "../header/2048.hpp"
#include <iostream>
#include <vector>
#include <string>

#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl
using namespace std;
using Plateau = vector<vector<int>>;

void ajouterDeuxOuQuatreTest() {
    Jeu jeu;
    jeu.plateau={
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    int nombreTuiles=0;
    for(auto ligne:jeu.plateau){
        for(auto tuile:ligne){
            if(tuile==2 or tuile==4){
                nombreTuiles++;
            }
        }
    }
    CHECK(nombreTuiles==0);

    jeu.ajouterDeuxOuQuatre();
    nombreTuiles=0;
    for(auto ligne:jeu.plateau){
        for(auto tuile:ligne){
            if(tuile==2 or tuile==4){
                nombreTuiles++;
            }
        }
    }
    CHECK(nombreTuiles==1);

    jeu.ajouterDeuxOuQuatre();
    nombreTuiles=0;
    for(auto ligne:jeu.plateau){
        for(auto tuile:ligne){
            if(tuile==2 or tuile==4){
                nombreTuiles++;
            }
        }
    }
    CHECK(nombreTuiles==2);
}

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

    jeu.plateau={
        {4,2,4,2},
        {2,4,2,4},
        {4,8,4,8},
        {4,16,8,0}
    };
    CHECK(!jeu.estTermine());

    jeu.plateau={
        {2,4,0,2},
        {8,32,16,8},
        {32,64,128,32},
        {4096,2048,512,128}
    };
    CHECK(!jeu.estTermine());
}

void obtenirDessinTest() {
    Jeu jeu;
    jeu.plateau={
        {0,2,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    CHECK(jeu.obtenirDessin() ==
    "*****************\n"
    "*   * 2 *   *   *\n"
    "*****************\n"
    "*   *   *   *   *\n"
    "*****************\n"
    "*   *   *   *   *\n"
    "*****************\n"
    "*   *   *   *   *\n"
    "*****************\n");
    jeu.plateau={
            {0,2,0,0},
            {0,128,0,0},
            {0,0,0,0},
            {0,0,0,0}
        };
    CHECK(jeu.obtenirDessin() ==
    "*************************\n"
    "*     *   2 *     *     *\n"
    "*************************\n"
    "*     * 128 *     *     *\n"
    "*************************\n"
    "*     *     *     *     *\n"
    "*************************\n"
    "*     *     *     *     *\n"
    "*************************\n");
}

int main() {

    ajouterDeuxOuQuatreTest();
    echangerLignesEtColonnesTest();
    fusionnerEtAlignerLesLignesTest();
    deplacementTest();
    estTermineTest();
    obtenirDessinTest();

    cout << "Tests effectués" << endl;

    return 0;
}
