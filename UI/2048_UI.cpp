#include "../header/2048.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;
using Plateau = vector<vector<int>>;



void dessineDisque(SDL_Renderer* renderer, int x, int y, int r) {
    for (int w = 0; w < r * 2; w++) {
        for (int h = 0; h < r * 2; h++) {
            int dx = r - w;
            int dy = r - h;
            if ((dx * dx + dy * dy) <= (r * r)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void SDL_RenderFillRoundedRect(SDL_Renderer* renderer, SDL_Rect* rect) {
    SDL_Rect recttmp;

    recttmp = {rect->x+5,rect->y, rect->w-10, rect->h};
    SDL_RenderFillRect(renderer, &recttmp);
    recttmp = {rect->x,rect->y+5, rect->w, rect->h-10};
    SDL_RenderFillRect(renderer, &recttmp);

    /* Pour les coins arrondis */
    dessineDisque(renderer,rect->x+5,rect->y+5,5);
    dessineDisque(renderer,rect->x+74,rect->y+5,5);
    dessineDisque(renderer,rect->x+5,rect->y+74,5);
    dessineDisque(renderer,rect->x+74,rect->y+74,5);
}

void dessinePlateau(SDL_Renderer* renderer){
    SDL_Rect rect = {10,10,80,80};
    for(int i=0;i<4;i++){
        rect.x=10;
        for(int j=0;j<4;j++){
            SDL_RenderFillRoundedRect(renderer, &rect);
            rect.x+=90;
        }
        rect.y+=90;
    }
}

void creerTuile(SDL_Renderer* renderer, int x, int y, int val, TTF_Font* font) {
    SDL_Rect rect = {x, y, 80, 80};
    SDL_SetRenderDrawColor(renderer, 200,200,200, 255); // Couleur de la tuile
    SDL_RenderFillRoundedRect(renderer, &rect);

    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", val);

    SDL_Color textColor = {0, 0, 0, 255}; 
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, buffer, textColor);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int textWidth, textHeight;
    TTF_SizeText(font, buffer, &textWidth, &textHeight);

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
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", score);
    SDL_Color textColor = {255, 255, 255, 255}; 
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, buffer, textColor);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int textWidth, textHeight;
    TTF_SizeText(font, buffer, &textWidth, &textHeight);

    SDL_Rect textRect = {185 - textWidth / 2, 410 - textHeight / 2, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}

int main(){
    srand(time(0));

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Medium.ttf", 24);
    SDL_Window* window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 370, 450, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Jeu jeu;


    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); 
    SDL_RenderClear(renderer); 
    SDL_SetRenderDrawColor(renderer, 210, 190, 190, 255);
    dessinePlateau(renderer);
    afficherTuiles(renderer,font, jeu.plateau);
    afficherScore(renderer,font,jeu.score);
    SDL_RenderPresent(renderer); 

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
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); 
        SDL_RenderClear(renderer); 
        SDL_SetRenderDrawColor(renderer, 210, 190, 190, 255);
        dessinePlateau(renderer);
        afficherTuiles(renderer,font, jeu.plateau);
        afficherScore(renderer,font,jeu.score);
        SDL_RenderPresent(renderer); 

        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    
    return 0;
}