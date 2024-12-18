// Header for all Constants and includes 
#include <iostream>
#include <string>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <memory>
#include <array>

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// windowsize
const int             WINDOW_HEIGHT = 1792;
const int             WINDOW_WIDTH = 1062;

// player values
const int             PLAYER_START_X = 1630;
const int             PLAYER_START_Y = 670;
const int             PICTURE_PER_ANIMATION = 3;
const int             WALKING_DISTANCE = 2;

// paths for images
const std::string     BACKGROUND_SURFACEPATH = "../assets/background.jpeg";
const std::string     PLAYER_PATH_FRONT = "../assets/player/position";
const std::string     PLAYER_PATH_BACK = ".png";


#endif // CONSTANTS_HPP