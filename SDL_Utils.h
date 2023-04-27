#ifndef SDL_UTILS_H_INCLUDED
#define SDL_UTILS_H_INCLUDED

#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"


const int SCREEN_HEIGHT=448;

const int SCREEN_WIDTH=960;

void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle,TTF_Font* font) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

const int FRAME_PER_SECOND = 24; //fps

#define TILE_SIZE 32
#define MAX_MAP_X 400
#define MAX_MAP_Y 14

#define MAX_MAP_1 6270
#define MAX_MAP_2 6370
#define OUT_OF_MAP 400

const int COLOR_KEY_R=167;
const int COLOR_KEY_G=175;
const int COLOR_KEY_B=180;


struct Map{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

struct Input{
    int left,right,up,down;
    int jump;
};


#endif // SDL_UTILS_H_INCLUDED
