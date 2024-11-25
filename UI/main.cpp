#include "./header/jeu.hpp"
#include "./header/dessin.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main() {
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Medium.ttf", 24);
    SDL_Window* window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 370, 370, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Jeu jeu = {plateauInitial(),0};


    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); 
    SDL_RenderClear(renderer); 
    SDL_SetRenderDrawColor(renderer, 210, 190, 190, 255);
    dessinePlateau(renderer);
    afficherTuiles(renderer,font, jeu.plateau);
    SDL_RenderPresent(renderer); 

    bool fin = false;
    SDL_Event event;
    while (!fin) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                fin = true;
            }
            if(event.type == SDL_KEYDOWN){
                if((event.key.keysym.sym==SDLK_UP || event.key.keysym.sym==SDLK_DOWN || event.key.keysym.sym==SDLK_LEFT || event.key.keysym.sym==SDLK_RIGHT) && (jeu.plateau!=deplacement(jeu,event.key.keysym.sym).plateau)){
                    jeu=deplacement(jeu,event.key.keysym.sym);
                    jeu.plateau=ajouterDeuxOuQuatre(jeu.plateau);
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); 
        SDL_RenderClear(renderer); 
        SDL_SetRenderDrawColor(renderer, 210, 190, 190, 255);
        dessinePlateau(renderer);
        afficherTuiles(renderer,font, jeu.plateau);
        SDL_RenderPresent(renderer); 


        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    
    return 0;
}
