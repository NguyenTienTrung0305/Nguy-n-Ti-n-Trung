#include "NumberOfPlayersLives.h"

NumberOfPlayersLives::NumberOfPlayersLives()
{
    number_ = 0;
}

NumberOfPlayersLives::~NumberOfPlayersLives()
{
    //dtor
}

void NumberOfPlayersLives::addPos(const int& xPos){
    pos_list.push_back(xPos);
}

void NumberOfPlayersLives::Init(SDL_Renderer* screen){
    loadImage("assets//Portrait.png" , screen);
    number_ = 6;
    if (pos_list.size() > 0){
        pos_list.clear();
    }
    for ( int i = 0 ; i < 6 ; i++){
        addPos(40*i + 20);
    }
}

void NumberOfPlayersLives::Show(SDL_Renderer* screen){
    for ( int i =0 ; i < pos_list.size() ; i++){
        rect_.x = pos_list.at(i);
        rect_.y = 0;
        Render(screen , NULL);
    }
}

void NumberOfPlayersLives::DecreaseNumber(){
    number_ --;
    pos_list.pop_back();
}

void NumberOfPlayersLives::IncreaseNumber(){
    number_ ++;
    int last_list = pos_list.back();
    pos_list.push_back(last_list + 40);
}


