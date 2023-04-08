#include "StateHp.h"

StateHp::StateHp()
{
    int state_hp = 0;
}

StateHp::~StateHp()
{
    //dtor
}

bool StateHp::loadImageState(SDL_Renderer* screen){
    bool ret = false;
    if (state_hp == HP_0){
        ret = loadImage("assets//Bars1.png" , screen);
    }else if (state_hp == HP_1){
        ret = loadImage("assets//Bars2.png" , screen);
    }else if (state_hp == HP_2){
        ret = loadImage("assets//Bars3.png" , screen);
    }else if (state_hp == HP_3){
        ret = loadImage("assets//Bars4.png" , screen);
    }
    return ret;
}
