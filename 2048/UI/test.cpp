#include <SDL2/SDL.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Refreshing Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    int rectX = 100; // Rectangle's starting x-coordinate
    int rectSpeed = 5; // Movement speed

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Update logic
        rectX += rectSpeed;
        if (rectX > 800 || rectX < 0) {
            rectSpeed = -rectSpeed; // Reverse direction at window edges
        }

        // Clear the screen (black background)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
        SDL_RenderClear(renderer);

        // Draw a white rectangle
        int color=rectX%255;
        SDL_SetRenderDrawColor(renderer,color, color, color, 255); // White color
        SDL_Rect rect = {rectX, 250, 100, 100};
        SDL_RenderFillRect(renderer, &rect);

        // Present the updated frame
        SDL_RenderPresent(renderer);

        // Delay to control frame rate (e.g., ~60 FPS)
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}