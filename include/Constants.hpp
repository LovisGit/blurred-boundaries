// Header for all Constants and includes 
#include <iostream>
#include <string>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <array>

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// windowsize
const int               SIZE = 170;
const int               WINDOW_WIDTH = 16*SIZE;
const int               WINDOW_HEIGHT = 9*SIZE;

// player values
const int               PLAYER_START_X = 1272;       //WINDOW_WIDTH - 360;
const int               PLAYER_START_Y = 576;      //WINDOW_HEIGHT - 500;   


const int               PLAYER_WIDTH = 13;
const int               PLAYER_HEIGHT = 19;      // it makes sense to not use the real height, at least somewhat
const int               PLAYER_FINISH_X = 916;
const int               PLAYER_FINISH_Y = 305;
const int               PLAYER_FINISH_WIDTH = 5;
const int               PLAYER_FINISH_HEIGHT = 20;
const int               PICTURE_PER_ANIMATION = 4;
const int               WALKING_DISTANCE = 2;
const int               NUMBER_OF_COLUMNS = 20;
const int               NUMBER_OF_ROWS = 15;

// paths for images
const std::string       BACKGROUND_SURFACEPATH = "../assets/background.jpeg";
const std::string       PLAYER_PATH_FRONT = "../assets/player/player";
const std::string       PLAYER_PATH_BACK = ".png";
const std::string       FINISH_PATH = "../assets/finish.png";

// paths for music
const std::string       BACKGROUND_MUSIC = "../assets/music.mp3";

// font settings
const std::string       FONT_PATH = "../assets/robotoFont.ttf";
const int               FONT_SIZE = 50;      

// delay for smooth player animation
const int               DELAY = 60;

// zoom 
const float             ZOOM = 8.0f; // 8.0f is default 

// shadow
const int               SHADOW_OFFSET = 2; // bigger parameter results in smaller offset
const int               SHADOW_DENSITY = 150;

#endif // CONSTANTS_HPP