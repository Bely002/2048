#include "./lib/modele.hpp"

int main() {
    srand(time(0));
    Jeu jeu = {plateauInitial(), 0};
    int dir;

    initscr();
    keypad(stdscr, TRUE);
    noecho();

    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(1));


    while(!estTermine(jeu.plateau)){
        clear();
        printw("Score: %d\n", jeu.score);
        printw("%s", dessine(jeu.plateau).c_str());
        dir=0;
        while((dir!=KEY_UP && dir!=KEY_DOWN && dir!=KEY_LEFT && dir!=KEY_RIGHT) or jeu.plateau==deplacement(jeu,dir).plateau){
            dir=getch();
        }
        jeu=deplacement(jeu,dir);
        jeu.plateau=ajouterDeuxOuQuatre(jeu.plateau);
    }

    move(0,10);
    printw("%s",dessine(jeu.plateau).c_str());

    endwin();
    return 0;
}