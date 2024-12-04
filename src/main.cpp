#include <iostream>
#include <SDL2/SDL_test_images.h>
#include <string>

/*

KONSTANTEN

*/

// Fenstergrößen
int             WINDOW_HEIGHT = 0;
int             WINDOW_WIDTH = 0;

// Pfad zum Hintergrundbild
std::string     SURFACEPATH = ""; 


/*

SOURCE

*/

int main(int argc, char** argv) {
    
    // Schaue nach der Probleme in der Initialisierung
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("error initializing SDL: %s\n", SDL_GetError());

    // Baue das Fenster auf
    SDL_Window* window = SDL_CreateWindow(  "Blurred Boundaries",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            WINDOW_HEIGHT,
                                            WINDOW_WIDTH,
                                            0);

    // Verschiedene weitere Initialisierungen 
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);
    SDL_Surface* surface;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

}