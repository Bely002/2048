#include <SDL2/SDL.h>
#include "./lib/modele.hpp"

void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
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
    drawFilledCircle(renderer,rect->x+5,rect->y+5,5);
    drawFilledCircle(renderer,rect->x+74,rect->y+5,5);
    drawFilledCircle(renderer,rect->x+5,rect->y+74,5);
    drawFilledCircle(renderer,rect->x+74,rect->y+74,5);
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

void creerTuile(){
    
}

void afficherTuiles(SDL_Renderer* renderer, Plateau plateau) {

}


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 370, 370, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); 
    SDL_RenderClear(renderer); 

    SDL_SetRenderDrawColor(renderer, 210, 190, 190, 255);

    dessinePlateau(renderer);

    SDL_RenderPresent(renderer); 

    bool jeu = true;
    SDL_Event event;
    while (jeu) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                jeu = false; // Quit event detected
            }
        }
        SDL_Delay(16); // Small delay to limit CPU usage (roughly 60 FPS)
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
