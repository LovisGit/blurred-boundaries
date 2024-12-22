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
const int               WINDOW_WIDTH = 1792;
const int               WINDOW_HEIGHT = 1062;

// player values
const int               PLAYER_START_X = 1630;
const int               PLAYER_START_Y = 670;
const int               PLAYER_WIDTH = 14;
const int               PLAYER_HEIGHT = 19;     //wahrscheinlich macht es Sinn, die Hoehe nicht so gross wie die echte Hoehe zu machen
const int               PLAYER_FINISH_X = 588;
const int               PLAYER_FINISH_Y = 191;
const int               PLAYER_FINISH_WIDTH = 11;
const int               PLAYER_FINISH_HEIGHT = 11;
const int               PICTURE_PER_ANIMATION = 4;
const int               WALKING_DISTANCE = 10;

// paths for images
const std::string       BACKGROUND_SURFACEPATH = "../assets/background.jpeg";
const std::string       PLAYER_PATH_FRONT = "../assets/player/player";
const std::string       PLAYER_PATH_BACK = ".png";
const std::string       FINISH_PATH = "../assets/finish.png";

// delay for smooth player animation
const int               DELAY = 60;

#endif // CONSTANTS_HPP