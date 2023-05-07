#include "AttackObject.h"

AttackObject::AttackObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    attack_type = KNIFE;
}

AttackObject::~AttackObject()
{
    //dtor
}

bool AttackObject::LoadImageAttack(SDL_Renderer* screen){
    bool ret = false;
    if (attack_type == GATTINGGUN){
        ret = loadImage("assets//bulletgatting.png" , screen);
    }else if ( attack_type == FIREBALL){
        ret = loadImage("assets//fireball.jpg" , screen);
    }
    return ret;
}

void AttackObject::HandleMove(const int& x_border  , const int& y_border){
    if (attack_direction == DIR_RIGHT){
        rect_.x += x_val_;
        if ( rect_.x  > x_border){
            is_move_ = false;
        }
    }else if ( attack_direction == DIR_LEFT){
        rect_.x -= x_val_;
        if (rect_.x < 0){
            is_move_ = false;
        }
    }

}
