// Header for all Constants and includes 
#include <iostream>
#include <string>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include <array>

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// windowsize
const int               WINDOW_WIDTH = 1792;
const int               WINDOW_HEIGHT = 1062;

// player values
const int               PLAYER_START_X = 1630;
const int               PLAYER_START_Y = 670;
const int               PLAYER_WIDTH = 14;
const int               PLAYER_HEIGHT = 19;     // it makes sense to not use the real height
const int               PLAYER_FINISH_X = 588;
const int               PLAYER_FINISH_Y = 191;
const int               PLAYER_FINISH_WIDTH = 11;
const int               PLAYER_FINISH_HEIGHT = 11;
const int               PICTURE_PER_ANIMATION = 4;
const int               WALKING_DISTANCE = 2;

// paths for images
const std::string       BACKGROUND_SURFACEPATH = "../assets/background.jpeg";
const std::string       PLAYER_PATH_FRONT = "../assets/player/player";
const std::string       PLAYER_PATH_BACK = ".png";
const std::string       FINISH_PATH = "../assets/finish.png";

// paths for music
const std::string       BACKGROUND_MUSIC = "../assets/music.mp3";

// delay for smooth player animation
const int               DELAY = 60;

// zoom 
const float             ZOOM = 8.0f; 

#endif // CONSTANTS_HPP