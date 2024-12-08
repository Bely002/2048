#include "../header/2048.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using Plateau = vector<vector<int>>;

vector<string> listeCoups = {"h","b","g","d"};

vector<Plateau> meilleursPlateaux ={
    {
    {2,4,8,16},
    {256,128,64,32},
    {512,1024,2048,4096},
    {65536,32768,16384,8192}
    },{
        {65536, 32768, 16384, 8192},
    {512, 1024, 2048, 4096},
    {256, 128, 64, 32},
    {2, 4, 8, 16}
    },{
        {8192, 16384, 32768, 65536},
    {4096, 2048, 1024, 512},
    {32, 64, 128, 256},
    {16, 8, 4, 2}
    },{
        {16, 8, 4, 2},
    {32, 64, 128, 256},
    {4096, 2048, 1024, 512},
    {8192, 16384, 32768, 65536}
    },
    {
    {65536, 512, 256, 2},
    {32768, 1024 , 128, 4},
    {16384, 2048, 64, 8},
    {8192, 4096, 32, 16}
    },

    
    {{8192, 4096, 32, 16},
    {16384, 2048, 64, 8},
    {32768, 1024, 128, 4},
    {65536 , 512, 256, 2}
    },

    {{2 ,256, 512, 65536},
    {4 ,128, 1024, 32768},
    {8 ,64, 2048, 16384},
    {16 ,32, 4096, 8192}},

    {{16, 32, 4096, 8192},
    {8, 64, 2048, 16384},
    {4, 128, 1024, 32768},
    {2, 256, 512, 65536}}
};

vector<pair<int,int>> obtenirTuilesVides(Plateau plateau) {
    vector<pair<int,int>> tuilesVides;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(plateau[i][j]==0){
                tuilesVides.push_back({i,j});
            }
        }
    }
    return tuilesVides;
}

string coupAleatoire() {
    return listeCoups[rand()%4];
}


int scorePlateau(Plateau plateau){
    int score=0;
    int meilleurScore=0;
    for(int k=0;k<meilleursPlateaux.size();k++){
        score=0;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                score+=plateau[i][j]*meilleursPlateaux[k][i][j];
            }
        }
        meilleurScore=score>meilleurScore ? score : meilleurScore;
    }
    return meilleurScore;
}

int scoreCoup(Jeu jeu,string coup,int profondeur){
    int score=0;
    if(jeu.deplacement(coup)){
        if(!jeu.estTermine()){
            vector<pair<int,int>> tuilesVides = obtenirTuilesVides(jeu.plateau);
            Jeu copie;
            for(int i=0; i<2; i++){
                for(int j=0;j<tuilesVides.size();j++){
                    copie=jeu;
                    copie.plateau[tuilesVides[j].first][tuilesVides[j].second]=(i==0 ? 2 : 4);
                    if(profondeur==0){
                        score+=scorePlateau(copie.plateau)*(i==0 ? 0.9 : 0.1)/tuilesVides.size();
                    }else{
                        int meilleurScore=0;
                        for(auto coup2:listeCoups){
                            int score2=scoreCoup(copie,coup2,profondeur-1)*(i==0 ? 0.9 : 0.1)/tuilesVides.size();
                            meilleurScore=score2>meilleurScore ? score2 : meilleurScore;
                        }
                        score+=meilleurScore;
                    }
                }
            }
        }
    }
    return score;
}

string choisirCoup(Jeu jeu){
    string meilleurCoup;
    int meilleurScore=-1;
    int score;
    for(auto coup:listeCoups){
        vector<pair<int,int>> tuilesVides = obtenirTuilesVides(jeu.plateau);
        score = scoreCoup(jeu,coup,1+(tuilesVides.size()<4));
        if(score>meilleurScore){
            meilleurScore=score;
            meilleurCoup=coup;
        }
    }
    return meilleurCoup;
}


int main() {
    srand(time(0));
    Jeu jeu;

    while(!jeu.estTermine()){
        cout << "Score : " << jeu.score << endl;
        cout << jeu.obtenirDessin() << endl;
        jeu.deplacement(choisirCoup(jeu));
        jeu.ajouterDeuxOuQuatre();
    }
    
    return 0;
}