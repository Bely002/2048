#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;
using Plateau = vector<vector<int>>;

void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius);

void SDL_RenderFillRoundedRect(SDL_Renderer* renderer, SDL_Rect* rect);

void dessinePlateau(SDL_Renderer* renderer);

void creerTuile(SDL_Renderer* renderer, int x, int y, int val, TTF_Font* font);

void afficherTuiles(SDL_Renderer* renderer, TTF_Font* font, Plateau plateau);