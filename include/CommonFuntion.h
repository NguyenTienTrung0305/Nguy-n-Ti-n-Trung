#ifndef COMMONFUNTION_H
#define COMMONFUNTION_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event  g_event;


//FPS
const int FRAME_PER_SECOND = 32;

// screen
const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

#define BLANK_TILE 0

// đồng bộ màu background nhân vật với bacground hình nền
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;


#define TILE_SIZE  64

#define MAX_MAP_X  400
#define MAX_MAP_y 10

// item support
#define HP 15
#define PRINCESS 49
#define SWORD 16
#define LIGHTNING 17
#define MSSTANDSTILL 21
#define MSMOVE 40

typedef struct Map{
    // man hinh bat dau o toa do x , y
    int start_x_ ;
    int start_y_ ;

    // full map
    int max_x;
    int max_y;

    int tile[MAX_MAP_y][MAX_MAP_X]; // mang luu thong tin chuong ngai vat

    char* file_name_;
};

// trang thai di chuyen
typedef struct keyEvents{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;

};

namespace SDLCommonFuncion{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int ShowMenu(SDL_Renderer* menu , TTF_Font* font);
}

#endif // COMMONFUNTION_H
