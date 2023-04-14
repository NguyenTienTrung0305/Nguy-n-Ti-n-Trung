#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include "CommonFuntion.h"
#include "BaseObject.h"
#include "AttackObject.h"
#include "NumberOfPlayersLives.h"
#include <vector>

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED  8
#define PLAYER_JUMP_VAL 15



class PlayerObject : public BaseObject
{
    public:
        PlayerObject();
        virtual ~PlayerObject();

        enum WalkType{
            FREE_FALL = 0 ,
            WALK_RIGHT = 1 ,
            WALK_LEFT = 2 ,

        };

        bool loadImage(std::string path , SDL_Renderer* screen); // load anh
        void Show(SDL_Renderer* des); // show anh
        void HandelInputAction(SDL_Event events , SDL_Renderer* screen); // xu ly su kien
        void Set_Clips();  // cat anh

        void DoPlayer(Map& map_data);  // cộng trừ lượng nhân vật di chuyển
        void CheckToMap(Map& map_data);  // check va cham


        void setMapXY(const int map_x , const int map_y){map_x_ = map_x , map_y_ = map_y;}
        void CenterEntityOnMap(Map& map_data); // tinh toan thong so khi khi chuyen nhan vat

        void UpdateImagePlayer(SDL_Renderer* des);

        // xu ly tan cong monster
        void set_attack_list(std::vector<AttackObject*> attackList){p_attack_list = attackList;}
        std::vector<AttackObject*>  get_attack_list() const {return p_attack_list;}
        void HandleAttack(SDL_Renderer* des);


        // remove attack
        void RemoveAttack(const int& index);

        void set_time_comeback(const int& timeComeback){time_come_back = timeComeback;}

        void loadImageAttack(std::string path);

        Mix_Chunk* die_;

        void set_y_pos(const float& yPos){y_pos = yPos;}

        int num_die_ = 0;
        bool is_die = false;


        // number of Player's Lives
        void InitPlayerLives(SDL_Renderer* screen);
        void ShowPlayerLives(SDL_Renderer* screen);

        void DecreaseNumber();
        void IncreaseNumber();

    protected:

    private:
        // list luu so luong knife
        std::vector<AttackObject*> p_attack_list;

        // toc do di chuyen cua player
        float x_val_;
        float y_val_;

        // vi tri hien tai
        float x_pos;
        float y_pos;

        int width_frame_;
        int heigth_frame_;

        SDL_Rect frame_clip_[7]; // Lưu các frame
        keyEvents key_events_;
        int frame_; // luu chi so cua frame_clip
        int status_; // trang thai di chuyen cua nhan vat

        bool on_ground;


        // vị trí mép của bản đồ khi nhân vật di chuyển
        int map_x_;
        int map_y_;

        // thoi gian delay moi khi chet truoc khi quay tro lai man hinh
        int time_come_back;


        Mix_Chunk* move_;
        Mix_Chunk* throwknife_;

        NumberOfPlayersLives players_lives;

};

#endif // PLAYEROBJECT_H
