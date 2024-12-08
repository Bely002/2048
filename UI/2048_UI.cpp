#include "../header/2048.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;
using Plateau = vector<vector<int>>;

void dessineDisque(SDL_Renderer* renderer, int x, int y, int r) {
    for (int w = 0; w < r * 2; w++) {
        for (int h = 0; h < r * 2; h++) {
            int dx = r - w;
            int dy = r - h;
            /* si x² + y² <= r² */
            if ((dx * dx + dy * dy) <= (r * r)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void SDL_RenderFilledRoundedRect(SDL_Renderer* renderer, SDL_Rect* rect) {
    SDL_Rect recttmp;

    /* Un rectangle de de taille 70x80 */
    recttmp = {rect->x+5,rect->y, rect->w-10, rect->h};
    SDL_RenderFillRect(renderer, &recttmp);
    /* Un rectangle de de taille 80x70 */
    recttmp = {rect->x,rect->y+5, rect->w, rect->h-10};
    SDL_RenderFillRect(renderer, &recttmp);

    /* Pour les coins arrondis */
    dessineDisque(renderer,rect->x+5,rect->y+5,5);
    dessineDisque(renderer,rect->x+74,rect->y+5,5);
    dessineDisque(renderer,rect->x+5,rect->y+74,5);
    dessineDisque(renderer,rect->x+74,rect->y+74,5);
}

void dessinePlateau(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 210, 190, 190, 255);
    SDL_Rect rect = {10,10,80,80};
    for(int i=0;i<4;i++){
        rect.x=10;
        for(int j=0;j<4;j++){
            SDL_RenderFilledRoundedRect(renderer, &rect);
            rect.x+=90;
        }
        rect.y+=90;
    }
}

void creerTuile(SDL_Renderer* renderer, int x, int y, int val, TTF_Font* font) {
    /* Créer la tuile derrière la valeur */
    SDL_Rect rect = {x, y, 80, 80};
    SDL_SetRenderDrawColor(renderer, 200,200,200, 255);
    SDL_RenderFilledRoundedRect(renderer, &rect);

    /* Convertir score en char */
    string valstr = to_string(val);
    const char *valchar = valstr.c_str();

    SDL_Color textColor = {0, 0, 0, 255}; 
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, valchar, textColor);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    
    /* On récupère la taille du texte */
    int textWidth, textHeight;
    TTF_SizeText(font, valchar, &textWidth, &textHeight);

    SDL_Rect textRect = {x + (80 - textWidth) / 2, y + (80 - textHeight) / 2, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}

void afficherTuiles(SDL_Renderer* renderer, TTF_Font* font, Plateau plateau) {
    SDL_Rect rect = {10,10,80,80};
    int x=10;
    int y=10;
    for(int i=0;i<4;i++){
        x=10;
        for(int j=0;j<4;j++){
            if(plateau[i][j]!=0){
                creerTuile(renderer,x,y, plateau[i][j],font);
            }
            x+=90;
        }
        y+=90;
    }
}

string convertirInput(int input){
    switch (input){
        case SDLK_UP:
            return "h";
        case SDLK_DOWN:
            return "b";
        case SDLK_RIGHT:
            return "d";
        case SDLK_LEFT:
            return "g";
    }
    return "";
}

void afficherScore(SDL_Renderer* renderer, TTF_Font* font,int score) {
    /* Convertir score en char */
    string scorestr = to_string(score);
    const char *scoreChar = scorestr.c_str();

    SDL_Color textColor = {255, 255, 255, 255}; 
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, scoreChar, textColor);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    /* On récupère la taille du texte */
    int textWidth, textHeight;
    TTF_SizeText(font, scoreChar, &textWidth, &textHeight);

    /* Créer un "rectangle" avec les bonnes coordonnées correspondantes à la taille du texte */
    SDL_Rect textRect = {185 - textWidth / 2, 410 - textHeight / 2, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}



void afficherJeu(SDL_Renderer* renderer, TTF_Font* font, Jeu jeu){
    /* Met la couleur de dessin à (50,50,50,255) gris */
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

    /* Colorie tout le renderer */
    SDL_RenderClear(renderer);

    dessinePlateau(renderer);
    afficherTuiles(renderer,font, jeu.plateau);
    afficherScore(renderer,font,jeu.score);

    /* Raffraichie l'écran avec les mofifications appliquées au renderer */
    SDL_RenderPresent(renderer);
}

int main(){
    srand(time(0));

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Medium.ttf", 24);

    /* Créer une fenêtre de nom 2048, positionnée au centrer de taille 370x450 sans paramètres en plus*/
    SDL_Window* window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 370, 450, 0);

    /* Créer un renderer (un canevas sur lequel les éléments vont être positionnés) */
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    Jeu jeu;

    afficherJeu(renderer,font,jeu);

    bool fin = false;
    SDL_Event event;
    while (!fin) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                fin = true;
            }
            if(event.type == SDL_KEYDOWN){
                if(jeu.deplacement(convertirInput(event.key.keysym.sym))){
                    jeu.ajouterDeuxOuQuatre();
                }
            }
        }
        afficherJeu(renderer,font,jeu);

        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    
    return 0;
}