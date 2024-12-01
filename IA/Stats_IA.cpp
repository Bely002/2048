#include "../header/2048.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;
using Plateau = vector<vector<int>>;

map<string,int> stats = {{"Nombre de parties jouees ", 0}, {"Score moyen ", 0}, {"Meilleur score ",0}};

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
    }
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
    for(int k=0;k<4;k++){
        score=0;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                score+=plateau[i][j]*meilleursPlateaux[k][i][j];
            }
        }
        score=score;
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
    ifstream statsFichier ("stats.txt");
    string key;
    string val;
    while(getline(statsFichier,key,':')){
        getline(statsFichier,val);
        stats[key]=stoi(val);
    }
    statsFichier.close();


    srand(time(0));

    for(int i=0;i<10;i++){
        Jeu jeu;
        while(!jeu.estTermine()){
            cout << "Score : " << jeu.score << endl;
            cout << jeu.obtenirDessin() << endl;
            if(!jeu.deplacement(choisirCoup(jeu))){
                break;
            }
            jeu.ajouterDeuxOuQuatre();
        }
        if(jeu.score>stats["Meilleur score "]) stats["Meilleur score "]=jeu.score;
        stats["Nombre de parties jouees "]++;
        stats["Score moyen "]=((stats["Nombre de parties jouees "]-1)*stats["Score moyen "]+jeu.score)/stats["Nombre de parties jouees "];
    }

    ofstream statsFichier2 ("stats.txt");
    statsFichier2 << "Nombre de parties jouees : " << stats["Nombre de parties jouees "] << "\n";
    statsFichier2 << "Score moyen : " << stats["Score moyen "] << "\n";
    statsFichier2 << "Meilleur score : " << stats["Meilleur score "] << "\n";

    statsFichier2.close();

    return 0;
}