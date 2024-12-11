#include <iostream>
#include <string>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include "../include/Player.hpp"

/*
KONSTANTEN
*/

// Fenstergrößen
const int             WINDOW_HEIGHT = 1792;
const int             WINDOW_WIDTH = 1062;

//Spieler Werte
const int             PLAYER_START_X = 1630;
const int             PLAYER_START_Y = 670;
const int             PICTURE_PER_ANIMATION = 3;
const int             WALKING_DISTANCE = 2;

// Pfade zu Bildern
const std::string     BACKGROUND_SURFACEPATH = "../assets/background.jpeg";
const std::string     PLAYER_PATH_1 = "../assets/player/position";
const std::string     PLAYER_PATH_2 = ".png";

/*
SOURCE
*/

int main(int argc, char* argv[]) {

    Player thePlayer = Player(PLAYER_START_X, PLAYER_START_Y, PICTURE_PER_ANIMATION, WALKING_DISTANCE);
    
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
    Uint32          render_flags        = SDL_RENDERER_ACCELERATED;
    SDL_Renderer*   rend                = SDL_CreateRenderer(window, -1, render_flags);
    SDL_Surface*    backgroundSurface   = IMG_Load(BACKGROUND_SURFACEPATH.c_str());
    SDL_Surface*    playerSurface       = IMG_Load((PLAYER_PATH_1 + std::to_string(thePlayer.getPlayerPicture()) + PLAYER_PATH_2).c_str());
    SDL_Texture*    backgroundTexture   = SDL_CreateTextureFromSurface(rend, backgroundSurface);
    SDL_Texture*    playerTexture       = SDL_CreateTextureFromSurface(rend, playerSurface);
    SDL_Rect        backgroundRect;
    SDL_Rect        playerRect;
    
    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(playerSurface);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
    SDL_QueryTexture(playerTexture, NULL, NULL, &playerRect.w, &playerRect.h);

    backgroundRect.x = 0;  // Position des Hintergrundbildes
    backgroundRect.y = 0;

    playerRect.x = thePlayer.getXCoordinate();
    playerRect.y = thePlayer.getYCoordinate();

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
					        thePlayer.walkAndAnimate('W');
					        break;
				        case SDL_SCANCODE_A:
				        case SDL_SCANCODE_LEFT:
                            thePlayer.walkAndAnimate('A');
					        break;
				        case SDL_SCANCODE_S:
				        case SDL_SCANCODE_DOWN:
                            thePlayer.walkAndAnimate('S');
					        break;
				        case SDL_SCANCODE_D:
				        case SDL_SCANCODE_RIGHT:
                            thePlayer.walkAndAnimate('D');
					        break;
				        default:
					        break;
				    }
                    break;
            
                case SDL_KEYUP:
                    thePlayer.walkAndAnimate('0');
                    break;
			}
        }

        //Spielerbild wird neu gesetzt
        SDL_DestroyTexture(playerTexture);
        playerSurface = IMG_Load((PLAYER_PATH_1 + std::to_string(thePlayer.getPlayerPicture()) + PLAYER_PATH_2).c_str());
        playerTexture = SDL_CreateTextureFromSurface(rend, playerSurface);
        SDL_FreeSurface(playerSurface);

        playerRect.x = thePlayer.getXCoordinate();
        playerRect.y = thePlayer.getYCoordinate();
        
        // Setze den Hintergrund (optional, aber empfohlen)
        SDL_RenderClear(rend);

        // Zeichne das Hintergrundbild
        SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect);

        // Zeichne das Spielerbild
        SDL_RenderCopy(rend, playerTexture, NULL, &playerRect);

        // Aktualisiere den Bildschirm
        SDL_RenderPresent(rend);

        SDL_Delay(20);
    }

	// destroy texture
	SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playerTexture);

	// destroy renderer
	SDL_DestroyRenderer(rend);

	// destroy window
	SDL_DestroyWindow(window);
	
	// close SDL
	SDL_Quit();

    return 0;
}