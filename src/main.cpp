#include "../include/Constants.hpp"
#include "../include/Player.hpp"

int main(int argc, char* argv[]) {

    // initialization of the player object
    Player thePlayer = Player(PLAYER_START_X, PLAYER_START_Y, PLAYER_WIDTH, PLAYER_HEIGHT, PICTURE_PER_ANIMATION, WALKING_DISTANCE, PLAYER_START_CELL);
    
    // looking after problems in the initialization
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    // building the window
    SDL_Window* window = SDL_CreateWindow(  "Blurred Boundaries",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            WINDOW_HEIGHT,
                                            WINDOW_WIDTH,
                                            0);

    // more initializations
    Uint32          render_flags        = SDL_RENDERER_ACCELERATED;
    SDL_Renderer*   rend                = SDL_CreateRenderer(window, -1, render_flags);
    SDL_Surface*    backgroundSurface   = IMG_Load(BACKGROUND_SURFACEPATH.c_str());
    SDL_Surface*    playerSurface       = IMG_Load((PLAYER_PATH_FRONT + std::to_string(thePlayer.getPlayerPicture()) + PLAYER_PATH_BACK).c_str());
    SDL_Texture*    backgroundTexture   = SDL_CreateTextureFromSurface(rend, backgroundSurface);
    SDL_Texture*    playerTexture       = SDL_CreateTextureFromSurface(rend, playerSurface);
    SDL_Rect        backgroundRect;
    SDL_Rect        playerRect;
    
    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(playerSurface);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
    SDL_QueryTexture(playerTexture, NULL, NULL, &playerRect.w, &playerRect.h);

    // set the startposition of the background and player
    backgroundRect.x = 0;
    backgroundRect.y = 0;
    playerRect.x = thePlayer.getXCoordinate();
    playerRect.y = thePlayer.getYCoordinate();

    bool running = true;
    bool keyPressed = false;

    // game loop 
    while (running) {
        SDL_Event event;

		// events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			    case SDL_QUIT:
				    // handling of close button
				    running = false;
				    break;

			    case SDL_KEYDOWN:
				    // keyboard API for key pressed
                    keyPressed = true;
                    break;
            
                case SDL_KEYUP:
                    // keyboard API for key lifted
                    keyPressed = false;
                    break;

                default:
                    break;         
			}
            switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					thePlayer.walkAndAnimate(0, keyPressed);
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
                    thePlayer.walkAndAnimate(1, keyPressed);
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
                    thePlayer.walkAndAnimate(2, keyPressed);
				    break;
			    case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
                    thePlayer.walkAndAnimate(3, keyPressed);
					break;
				default:
					break;
		    }
        }

        // playerimage is being updated
        SDL_DestroyTexture(playerTexture);
        playerSurface = IMG_Load((PLAYER_PATH_FRONT + std::to_string(thePlayer.getPlayerPicture()) + PLAYER_PATH_BACK).c_str());
        playerTexture = SDL_CreateTextureFromSurface(rend, playerSurface);
        SDL_FreeSurface(playerSurface);

        // update the player coordinates
        playerRect.x = thePlayer.getXCoordinate();
        playerRect.y = thePlayer.getYCoordinate();
        
        // set the background
        SDL_RenderClear(rend);

        // draw the background and player
        SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect);
        SDL_RenderCopy(rend, playerTexture, NULL, &playerRect);

        // update the screen
        SDL_RenderPresent(rend);

        // delay for smooth player animation
        SDL_Delay(DELAY);
    }

	// destroy texture of background and player
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