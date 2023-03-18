#include "Timerfps.h"
#include "CommonFuntion.h"
Timerfps::Timerfps()
{
    start_tick_ = 0;
    paused_tick_= 0;
    is_paused_ = false;
    is_started_ = false;


}

Timerfps::~Timerfps()
{
    //dtor
}

void Timerfps::start(){
    is_started_ = true;
    is_paused_ = false;
    start_tick_ = SDL_GetTicks();
}

void Timerfps::stop(){
    is_paused_ = false;
    is_started_ = false;
}

void Timerfps::paused(){
    if (is_started_ = true && is_paused_ == false){
        is_paused_ = true;
        paused_tick_ = SDL_GetTicks() - start_tick_;
        //start_tick_ = 0;
    }
}

void Timerfps::unpaused(){
    if ( is_paused_ == true){
        is_paused_ == false;
        start_tick_ = SDL_GetTicks() - paused_tick_;
        paused_tick_ = 0; // de khi paused lan nua se lay thoi gian moi
    }
}

int Timerfps::get_tick(){
    if (is_started_ == true){
        if ( is_paused_ == true){
            return paused_tick_;
        }else{
            return SDL_GetTicks() - start_tick_;
        }
    }
    return 0;
}

bool Timerfps::is_started(){
    return is_started_;
}

bool Timerfps::is_paused(){
    return is_paused_;
}

