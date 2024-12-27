#include "../include/Constants.hpp"
#include "../include/Player.hpp"
#include "../include/Camera.hpp"

bool playerReachedFinish(const Player& thePlayer) {
    return !(thePlayer.getXCoordinate() + PLAYER_WIDTH <= PLAYER_FINISH_X ||            // player ist left of finish
             thePlayer.getXCoordinate() >= PLAYER_FINISH_X + PLAYER_FINISH_WIDTH ||     // player ist right of finish
             thePlayer.getYCoordinate() + PLAYER_FINISH_HEIGHT <= PLAYER_FINISH_Y ||    // player is above finish
             thePlayer.getYCoordinate() >= PLAYER_FINISH_Y + PLAYER_FINISH_HEIGHT);     // player is below finish
}

int main(int argc, char* argv[]) {
    // looking after problems in the initialization
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("error initializing SDL: %s\n", SDL_GetError());
    
    // initialize music
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        printf("error initializing SDL_mixer: %s\n", Mix_GetError());

    // building the window
    SDL_Window* window = SDL_CreateWindow(  "Blurred Boundaries",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            WINDOW_WIDTH,
                                            WINDOW_HEIGHT, 
                                            0);

    // more initializations of the background, player and finish
    Uint32          render_flags        = SDL_RENDERER_ACCELERATED;
    SDL_Renderer*   rend                = SDL_CreateRenderer(window, -1, render_flags);
    SDL_Surface*    backgroundSurface   = IMG_Load(BACKGROUND_SURFACEPATH.c_str());
    Player          thePlayer(PLAYER_START_X, PLAYER_START_Y, PLAYER_WIDTH, PLAYER_HEIGHT, PICTURE_PER_ANIMATION, WALKING_DISTANCE);
    SDL_Surface*    playerSurface       = IMG_Load((PLAYER_PATH_FRONT + std::to_string(thePlayer.getPlayerPicture()) + PLAYER_PATH_BACK).c_str());
    SDL_Surface*    finishSurface       = IMG_Load(FINISH_PATH.c_str());
    SDL_Texture*    backgroundTexture   = SDL_CreateTextureFromSurface(rend, backgroundSurface);
    SDL_Texture*    playerTexture       = SDL_CreateTextureFromSurface(rend, playerSurface);
    SDL_Texture*    finishTexture       = SDL_CreateTextureFromSurface(rend, finishSurface);
    SDL_Rect        backgroundRect;
    SDL_Rect        playerRect;
    SDL_Rect        finishRect;
    Mix_Music*      backgroundMusic = Mix_LoadMUS(BACKGROUND_MUSIC.c_str());
    
    
    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(playerSurface);
    SDL_FreeSurface(finishSurface);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
    SDL_QueryTexture(playerTexture, NULL, NULL, &playerRect.w, &playerRect.h);
    SDL_QueryTexture(finishTexture, NULL, NULL, &finishRect.w, &finishRect.h);

    // depends on Query Texture
    Camera          theCamera(&thePlayer, &playerRect, ZOOM); 

    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_PlayMusic(backgroundMusic, -1);
    
    // set the startposition of the background and player
    backgroundRect.x = 0;
    backgroundRect.y = 0;

    // set the position of the finish in the middle of the window
    finishRect.x = (WINDOW_WIDTH / 2) - (finishRect.w / 2);
    finishRect.y = (WINDOW_HEIGHT / 2) - (finishRect.h / 2);

    // play the background music
    Mix_PlayMusic(backgroundMusic, -1);

    bool running = true;
    bool reachedFinish = false;

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
                    // handle key presses only if the game is not in "finished" state
                    if (!event.key.repeat && !reachedFinish) {
                        switch (event.key.keysym.scancode) {
                            case SDL_SCANCODE_W:
                            case SDL_SCANCODE_UP:
                                thePlayer.walkAndAnimate(0, true);
                                break;
                            case SDL_SCANCODE_A:
                            case SDL_SCANCODE_LEFT:
                                thePlayer.walkAndAnimate(1, true);
                                break;
                            case SDL_SCANCODE_S:
                            case SDL_SCANCODE_DOWN:
                                thePlayer.walkAndAnimate(2, true);
                                break;
                            case SDL_SCANCODE_D:
                            case SDL_SCANCODE_RIGHT:
                                thePlayer.walkAndAnimate(3, true);
                                break;
                            default:
                                break;
                        }
                    }
                    break;

                case SDL_KEYUP:
                    // handle key releases only if the game is not in "finished" state
                    if (!reachedFinish) {
                        switch (event.key.keysym.scancode) {
                            case SDL_SCANCODE_W:
                            case SDL_SCANCODE_UP:
                                thePlayer.walkAndAnimate(0, false);
                                break;
                            case SDL_SCANCODE_A:
                            case SDL_SCANCODE_LEFT:
                                thePlayer.walkAndAnimate(1, false);
                                break;
                            case SDL_SCANCODE_S:
                            case SDL_SCANCODE_DOWN:
                                thePlayer.walkAndAnimate(2, false);
                                break;
                            case SDL_SCANCODE_D:
                            case SDL_SCANCODE_RIGHT:
                                thePlayer.walkAndAnimate(3, false);
                                break;
                            default:
                                break;
                        }
                    }
                    break;

                default:
                    break;         
            }
        }

        if (!reachedFinish) {
            thePlayer.walkAndAnimate(-1, true);

            // player image is being updated
            SDL_DestroyTexture(playerTexture);
            playerSurface = IMG_Load((PLAYER_PATH_FRONT + std::to_string(thePlayer.getPlayerPicture()) + PLAYER_PATH_BACK).c_str());
            playerTexture = SDL_CreateTextureFromSurface(rend, playerSurface);
            SDL_FreeSurface(playerSurface);
        }

        // check if the player has reached the finish
        if (playerReachedFinish(thePlayer))
            reachedFinish = true;

        // update camera 
        theCamera.updateCamera(); 

        // clear the renderer
        SDL_RenderClear(rend);

        // draw the background
        SDL_RenderCopy(rend, backgroundTexture, &theCamera.getCameraRect(), &backgroundRect);

        if (reachedFinish) 
            SDL_RenderCopy(rend, finishTexture, NULL, &finishRect);
        else
            SDL_RenderCopy(rend, playerTexture, NULL, &playerRect);

        // update the screen
        SDL_RenderPresent(rend);

        // delay for smooth player animation
        SDL_Delay(DELAY);
    }

	// destroy / reset stuff
	SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(finishTexture);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
	SDL_Quit();

    return 0;
}