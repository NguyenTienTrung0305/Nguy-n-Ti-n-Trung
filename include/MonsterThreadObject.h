#ifndef MONSTERTHREADOBJECT_H
#define MONSTERTHREADOBJECT_H

#include "CommonFuntion.h"
#include "BaseObject.h"
#include "AttackObject.h"
#include "StateHp.h"


using namespace std;

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 8
#define TOTAL_FRAME 9
class MonsterThreadObject : public BaseObject
{
    public:
        MonsterThreadObject();
        virtual ~MonsterThreadObject();

        enum TypeMove{
            STAND_STILL = 0 , // dung yen
            MOVE = 1,
        };

        enum TypeMonster{
            BOSS = 0,
            SOLDIER = 1,
        };


        void set_x_val(float xVal){x_val_ = xVal;}
        void set_y_val(float yVal){y_val_ = yVal;}

        void set_x_pos(float xPos){x_pos = xPos;}
        void set_y_pos(float yPos){y_pos = yPos;}
        float get_x_pos() const {return x_pos;}
        float get_y_pos() const {return y_pos;}

        void setMap(const int& mp_x , const int& mp_y ){
            map_x = mp_x;
            map_y = mp_y;
        }

        void set_clip();
        bool loadImage(std::string path , SDL_Renderer* screen);
        void Show(SDL_Renderer* des);

        int get_width_frame() const {return width_frame_;}
        int get_height_frame() const {return height_frame_;}

        void DoPlayer(Map& gMap);
        void CheckToMap(Map& gMap);


        void set_type_move (const int& typeMove){type_move_ = typeMove;}
        void set_bounded_position(const int& leftPos , const int& rightPos){ bounded_left_move = leftPos , bounded_right_move = rightPos;}

        // check trang thai di chuyen , neu nhan vat di den diem gioi han ben trai thi phai cho no bang 0 , dong thoi input_type.right_ = 1
        // de no di chuyen sang phai
        void set_input_left(const int& ipleft){input_type_.left_ = ipleft;}

        // xu ly van de di chuyen trong khoang gioi han
        void HandleMove ( SDL_Renderer* screen , Map &gmap);


        std::vector<AttackObject*> get_bullet_list() const {return bullet_list_;}
        void set_bullet_list(const std::vector<AttackObject*> bulletList){bullet_list_ = bulletList;}

        void InitBullet(AttackObject* p_bullet , SDL_Renderer* screen , int type_attack);
        // tầm bắn
        void MakeBullet(SDL_Renderer* screen , const int& x_bounded , const int& y_bounded , const float& x_player);

         // time beaten
        void set_times_beaten(const int& timeBeaten){times_beaten = timeBeaten;}
        int get_times_beaten() const {return times_beaten;}

        // xoa dan moi khi ban trung
        void RemoveAttack(const int& index);


        std::vector<StateHp*> get_list_state_hp() const {return list_state_hp;}
        void set_list_state_hp(const std::vector<StateHp*> listStateHp){list_state_hp = listStateHp;}
        void InitState(StateHp* p_state , SDL_Renderer* screen , const int& state_hp);
        void HandleStateHp(SDL_Renderer* screen);

        // boss
        void InitStateBoss(StateHp* p_state , SDL_Renderer* screen , const int& state);
        void HandleStateHpBoss(SDL_Renderer* screen);

        // type monster
        void set_type_monster(int typeMonster){
            type_monster = typeMonster;
        }
        int get_type_monster(){return type_monster;}

    protected:

    private:
        float x_pos;
        float y_pos;
        float x_val_;
        float y_val_;

        int map_x;
        int map_y;

        bool on_ground_;
        int time_comeback_;
        SDL_Rect frame_clip_[TOTAL_FRAME];
        int width_frame_;
        int height_frame_;
        int frame_;

        int type_move_;
        int bounded_left_move ;
        int bounded_right_move;

        int input_left_;
        keyEvents input_type_ ;

        // số lần bị tấn công
        int times_beaten;

        // type monster
        int type_monster;

        // xu ly tan cong
        std::vector<AttackObject*> bullet_list_;

        std::vector<StateHp*> list_state_hp;


};

#endif // MONSTERTHREADOBJECT_H
