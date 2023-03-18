#include "game_map.h"
#include <fstream>
using namespace std;
void GameMap::LoadMap(char* path){
    game_map_.max_x = 0;
    game_map_.max_y = 0;
    ifstream file(path);
    if (file){
        for ( int i = 0 ; i < MAX_MAP_y ; i++){
            for ( int j = 0 ; j < MAX_MAP_X ; j++){
                file >> game_map_.tile[i][j];
                int val = game_map_.tile[i][j];
                if ( val > 0){
                    if (j > game_map_.max_x){
                        game_map_.max_x = j;
                    }
                    if ( i > game_map_.max_y){
                        game_map_.max_y = i;
                    }
                }
            }
        }
    }
    game_map_.max_x = (game_map_.max_x+1)*TILE_SIZE;
    game_map_.max_y = (game_map_.max_y+1)*TILE_SIZE;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;
    game_map_.file_name_ = path;

    file.close();
}

void GameMap::LoadTiles(SDL_Renderer* screen){
    char file_img[50];
    FILE* fp = NULL;
    for ( int i = 0 ; i < 40 ; i++){
        sprintf_s(file_img , "map/%d.png"  , i); // chuyen doi so thanh chuoi

        fopen_s(&fp , file_img , "rb");
        if ( fp == NULL){
            continue;
        }

        fclose(fp);

        tile_map[i].loadImage(file_img , screen);
    }
}

// fill hinh anh vao cac o
void GameMap::DrawMap(SDL_Renderer* screen){
    // do rong cua man hinh
    int x1 = 0;
    int x2 = 0;

    // do cao cua man hinh
    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;
    map_x = game_map_.start_x_/TILE_SIZE; // lấy ra chỉ số i của mảng
    map_y = game_map_.start_y_/TILE_SIZE; // lấy ra chỉ số j của mảng

    x1 = (game_map_.start_x_ % TILE_SIZE)*-1; //  lùi lại 1 đoạn x1 để đảm bảo bin không bị thiếu
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE); // tăng 1 đoạn để đảm bảo bin không bị thiếu

    y1 = (game_map_.start_y_ % TILE_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1 ; i < y2 ; i+=TILE_SIZE){
        map_x = game_map_.start_x_/TILE_SIZE;
        for ( int j = x1 ; j < x2 ; j+= TILE_SIZE){
            int val = game_map_.tile[map_y][map_x];

            if ( val > 0){
                tile_map[val].setRect(j , i); // ve tai vi tri co toa do i j
                tile_map[val].Render(screen , NULL);
            }
            map_x++;
        }
        map_y++;
    }
}





