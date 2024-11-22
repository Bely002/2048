#include "./header/modele.hpp"

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

void creerTuile(SDL_Renderer* renderer, int x, int y, int val, TTF_Font* font) {
    SDL_Rect rect = {x, y, 80, 80};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Couleur de la tuile
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

void afficherJeu(SDL_Renderer* renderer, TTF_Font* font, Jeu jeu){
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); 
    SDL_RenderClear(renderer); 

    SDL_SetRenderDrawColor(renderer, 210, 190, 190, 255);

    dessinePlateau(renderer);
    afficherTuiles(renderer,font, jeu.plateau);

    SDL_RenderPresent(renderer); 
}


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Medium.ttf", 24);
    SDL_Window* window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 370, 370, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Jeu jeu = {plateauInitial(),0};


    afficherJeu(renderer,font,jeu);

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
        afficherJeu(renderer,font,jeu);
        SDL_Delay(16); // Small delay to limit CPU usage (roughly 60 FPS)
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    
    return 0;
}
