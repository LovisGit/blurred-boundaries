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
const int               WINDOW_HEIGHT = 1792;
const int               WINDOW_WIDTH = 1062;

// player values
const int               PLAYER_START_X = 1630;
const int               PLAYER_START_Y = 670;
const int               PLAYER_WIDTH = 1; //test
const int               PLAYER_HEIGHT = 1; //test
const int               PICTURE_PER_ANIMATION = 4;
const int               WALKING_DISTANCE = 2;
const int               PLAYER_START_CELL = 1; //test

// paths for images
const std::string       BACKGROUND_SURFACEPATH = "../assets/background.jpeg";
const std::string       PLAYER_PATH_FRONT = "../assets/player/player";
const std::string       PLAYER_PATH_BACK = ".png";

// delay for smooth player animation
const int               DELAY = 60;

#endif // CONSTANTS_HPP