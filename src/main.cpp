#include <iostream>
#include <string>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

/*
KONSTANTEN
*/

// Fenstergrößen
int             WINDOW_HEIGHT = 1000;
int             WINDOW_WIDTH = 1000;

// Pfad zum Hintergrundbild
std::string     SURFACEPATH = "../assets/background.jpeg"; 


/*

SOURCE

*/

int main(int argc, char* argv[]) {
    
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
    Uint32          render_flags    = SDL_RENDERER_ACCELERATED;
    SDL_Renderer*   rend            = SDL_CreateRenderer(window, -1, render_flags);
    SDL_Surface*    surface         = IMG_Load(SURFACEPATH.c_str());
    SDL_Texture*    tex             = SDL_CreateTextureFromSurface(rend, surface);
    SDL_Rect        dest;

    
    SDL_FreeSurface(surface);
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    int running = 1;

    // Game Loop 
    while (running) {
        SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				// handling of close button
				running = 0;
				break;

			case SDL_KEYDOWN:
				// keyboard API for key pressed
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					//y = dest.y - speed / 30;
					//y = dest.y - 1;
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					//x = dest.x - speed / 30;

					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					//y = dest.y + speed / 30;

					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					//x = dest.x + speed / 30;

					break;
				default:
					break;
				}
			}
        }
    }

	// destroy texture
	SDL_DestroyTexture(tex);

	// destroy renderer
	SDL_DestroyRenderer(rend);

	// destroy window
	SDL_DestroyWindow(window);
	
	// close SDL
	SDL_Quit();

    return 0;
}