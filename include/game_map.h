#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "CommonFuntion.h"
#include "BaseObject.h"

// ke thua lai cac ham trong BaseObject
class TileMap : public BaseObject{
public:
    //TileMap();
    //~TileMap();

};

class GameMap{
public:


    // đọc thông tin trong tin trong file lưu chỉ số
    void LoadMap(char* path);

    // load hình ảnh
    void LoadTiles(SDL_Renderer* screen);

    // fill hình ảnh vào các vị trí
    void DrawMap(SDL_Renderer* screen);

    // lay ra map
    Map getMap() const {return game_map_;};

    void SetMap(Map& map_data){game_map_ = map_data;}
private:
    Map game_map_;
    TileMap tile_map[50]; // mảng các hình ảnh của map
};

#endif // GAME_MAP_H
