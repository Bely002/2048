#include "../header/2048.hpp"
#include <vector>
#include <string>
#include <ncurses.h>

using namespace std;
using Plateau = vector<vector<int>>;

string convertirInput(int input){
    switch (input){
        case KEY_UP:
            return "h";
        case KEY_DOWN:
            return "b";
        case KEY_RIGHT:
            return "d";
        case KEY_LEFT:
            return "g";
        case 113:
            return "quit";
    }
    return "";
}

int main(){
    srand(time(0));
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(1));

    Jeu jeu;
    string dir;

    while(dir!="quit" and !jeu.estTermine()){
        clear();
        printw("Score: %d\n", jeu.score);
        printw("%s", jeu.obtenirDessin().c_str());
        dir="";
        while(dir!="quit" and !jeu.deplacement(dir)){
            dir=convertirInput(getch());
        }
        jeu.ajouterDeuxOuQuatre();
    }
    while(dir!="quit" and convertirInput(getch())!="quit"){
        clear();
        printw("GAME OVER\n");
        printw("Score: %d\n", jeu.score);
        printw("%s", jeu.obtenirDessin().c_str());
        printw("q : quit");
    }

    move(0,10);
    printw("%s",jeu.obtenirDessin().c_str());

    endwin();
    return 0;
}