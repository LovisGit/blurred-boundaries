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
    
    // initialize font handling
    if(TTF_Init() != 0)
        printf("error initializing SDL_ttf: %s\n", TTF_GetError());

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
    TTF_Font*       font = TTF_OpenFont(FONT_PATH.c_str(), FONT_SIZE);
    SDL_Color       textColor = {255, 255, 255, 255};

    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(playerSurface);
    SDL_FreeSurface(finishSurface);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
    SDL_QueryTexture(playerTexture, NULL, NULL, &playerRect.w, &playerRect.h);
    SDL_QueryTexture(finishTexture, NULL, NULL, &finishRect.w, &finishRect.h); 

    // depends on Query Texture
    Camera          theCamera(ZOOM, &thePlayer, &playerRect);

    // writing Name into buffer for further use
    char name[32];

    if (argc > 1) {
        // name from command line argument
        strcpy(name, argv[1]);
    } else {
        // name from file
        read(STDIN_FILENO, name, 1000);
    }

    SDL_Surface*    textSurface = TTF_RenderText_Solid(font, name, textColor);
    SDL_Texture*    textTexture = SDL_CreateTextureFromSurface(rend, textSurface);

    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_PlayMusic(backgroundMusic, -1);
    
    // set the startposition of the background
    backgroundRect.x = 0;
    backgroundRect.y = 0;

    // set the position of the finish in the middle of the window
    finishRect.x = (WINDOW_WIDTH / 2) - (finishRect.w / 2);
    finishRect.y = (WINDOW_HEIGHT / 2) - (finishRect.h / 2);

    // play the background music
    Mix_PlayMusic(backgroundMusic, -1);

    // create shadow surface with alpha channel support
    SDL_Surface* shadowSurface = SDL_CreateRGBSurface(0, playerRect.w, playerRect.h/2, 32,
        0xFF000000,  // R mask
        0x00FF0000,  // G mask
        0x0000FF00,  // B mask
        0x000000FF); // A mask

    // clear surface first
    SDL_FillRect(shadowSurface, NULL, SDL_MapRGBA(shadowSurface->format, 0, 0, 0, 0));

    SDL_LockSurface(shadowSurface);
    Uint32* pixels = (Uint32*)shadowSurface->pixels;
    int centerX = shadowSurface->w / 2;
    int centerY = shadowSurface->h / 2;
    int radiusX = shadowSurface->w / 2;
    int radiusY = shadowSurface->h / 2;

    for(int y = 0; y < shadowSurface->h; y++) {
        for(int x = 0; x < shadowSurface->w; x++) {
            float normalizedX = (float)(x - centerX) / radiusX;
            float normalizedY = (float)(y - centerY) / radiusY;
            if(normalizedX * normalizedX + normalizedY * normalizedY <= 1.0f) {
                float distance = sqrt(normalizedX * normalizedX + normalizedY * normalizedY);
                Uint8 alpha = (Uint8)(SHADOW_DENSITY * (1.0f - distance)); // Fade from center
                pixels[y * shadowSurface->w + x] = SDL_MapRGBA(shadowSurface->format, 0, 0, 0, alpha);
            }
        }
    }
    SDL_UnlockSurface(shadowSurface);

    // create texture and set blend mode
    SDL_Texture* shadowTexture = SDL_CreateTextureFromSurface(rend, shadowSurface);
    SDL_SetTextureBlendMode(shadowTexture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(shadowSurface);

    // after creating shadow texture, create shadow rect
    SDL_Rect shadowRect = playerRect;
    shadowRect.y += playerRect.h - (playerRect.h / SHADOW_OFFSET); // Position shadow below player

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
        theCamera.updateCamera(shadowRect);

        // clear the renderer
        SDL_RenderClear(rend);

        // draw the background
        SDL_RenderCopy(rend, backgroundTexture, &theCamera.getCameraRect(), &backgroundRect);

        // render the text
        SDL_Rect textRect = {
            playerRect.x + (playerRect.w / 2) - (textSurface->w / 2),  // center horizontally over player
            playerRect.y - textSurface->h - 5,  // place above player with 5px gap
            textSurface->w, 
            textSurface->h
        };
        SDL_RenderCopy(rend, textTexture, NULL, &textRect);

        if (reachedFinish) {
            SDL_RenderCopy(rend, finishTexture, NULL, &finishRect);
        } else {
            // Update shadow position to follow player
            shadowRect.x = playerRect.x;
            shadowRect.y = playerRect.y + (playerRect.h / SHADOW_OFFSET);

            // Render shadow first (before player)
            SDL_RenderCopy(rend, shadowTexture, NULL, &shadowRect);

            // Then render player as normal
            SDL_RenderCopy(rend, playerTexture, NULL, &playerRect);
        }
        
        // update the screen
        SDL_RenderPresent(rend);

        // delay for smooth player animation
        SDL_Delay(DELAY);
    }

	// destroy / reset stuff
	SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(finishTexture);
    SDL_DestroyTexture(shadowTexture);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
	SDL_Quit();

    return 0;
}