#include "MonsterThreadObject.h"

MonsterThreadObject::MonsterThreadObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos = 0.0;
    y_pos = 0.0;

    on_ground_ = false;
    time_comeback_ = 0;
    frame_ = 0;

    map_x = 0;
    map_y =0;

    bounded_left_move = 0;
    bounded_right_move = 0;
    input_type_.left_ = 0;
    type_move_ = STAND_STILL;

    times_beaten = 0;
}

MonsterThreadObject::~MonsterThreadObject()
{
    //dtor
}

bool MonsterThreadObject::loadImage(std::string path , SDL_Renderer* screen){
    bool ret = BaseObject::loadImage(path , screen);
    if (ret){
        width_frame_ = rect_.w/9;
        height_frame_ = rect_.h;
    }
    return ret;
}


void MonsterThreadObject::set_clip(){
    if (width_frame_ > 0 && height_frame_ > 0){
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        for ( int i = 1 ; i < 9 ; i++){
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void MonsterThreadObject::Show(SDL_Renderer* des){
    if (time_comeback_ == 0){
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        frame_++;
        if ( frame_ >= 9){
            frame_ = 0;
        }
        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect rendQuad = {rect_.x  , rect_.y , width_frame_ , height_frame_};
        SDL_RenderCopy(des , p_object_ , currentClip , &rendQuad);
    }
}

void MonsterThreadObject::DoPlayer(Map& gMap){
    if (time_comeback_ == 0){
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;

        if ( y_val_ >= MAX_FALL_SPEED){
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1){
            x_val_ -= 3;
        }else if (input_type_.right_ == 1){
            x_val_ += 3;
        }
        CheckToMap(gMap);
    }else if ( time_comeback_ > 0){
        time_comeback_ --;
        if ( time_comeback_ == 0){
            on_ground_ = false;
            x_val_ = 0;
            y_val_ = 0;
            if ( x_pos > 320){
                x_pos -= 320;
                bounded_left_move -=320;
                bounded_right_move -= 320;
            }else{
                x_pos =0;
            }
            y_pos = 0;
            if (type_move_ == MOVE){
                input_type_.left_ = 1; // mac dinh di sang trai truoc
            }
        }
    }

}

void MonsterThreadObject::CheckToMap(Map& map_data){
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // check theo chieu ngang
    int height_min  = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;


    // check xem  nhan vat nam tu o thu bao nhieu den o thu bao nhieu
    x1 = (x_pos + x_val_)/TILE_SIZE;
    x2 = (x_pos + x_val_ + width_frame_ - 1)/TILE_SIZE; // -1 de dam bao duong bien cua cua nhan vat khong trung duong bien cua chuong ngai vat

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min -1)/ TILE_SIZE;

    if ( x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_y){
        // moving to right
        if ( x_val_ > 0){
            if ((map_data.tile[y1][x2] > 0 && map_data.tile[y1][x2] < 20 && map_data.tile[y1][x2] != HP)
                ||(map_data.tile[y2][x2] > 0 && map_data.tile[y2][x2] < 20 && map_data.tile[y2][x2] != HP)){

                x_pos = x2*TILE_SIZE;
                x_pos -= (width_frame_ +1) ; // vi tri bat dau cua nhat vat bang vi tri cu cong them luong di chuyen
                x_val_ = 0;  // de khi gap chuong ngai vat du co an tiep cung khong di chuyen duoc
            }
        }else if (x_val_ < 0){
            if ((map_data.tile[y1][x1] > 0 && map_data.tile[y1][x1] < 20 && map_data.tile[y1][x1] != HP)
                || (map_data.tile[y2][x1] > 0 && map_data.tile[y2][x1] < 20 && map_data.tile[y2][x1] != HP )){

                x_pos = (x1+1)*TILE_SIZE;
                x_val_ = 0;
            }
        }
    }


    // check theo chieu doc
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

    // check xem nhat vat dang o o thu bao nhieu den o thu bao nhieu

    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos + y_val_)/TILE_SIZE;
    y2 = (y_pos + y_val_ + height_frame_ -1)/TILE_SIZE;


    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_y){
        if (y_val_ > 0){
            if ( (map_data.tile[y2][x1] > 0 && map_data.tile[y2][x1] < 20 && map_data.tile[y2][x1] != HP )
                || (map_data.tile[y2][x2] > 0 && map_data.tile[y2][x2] < 20 && map_data.tile[y2][x2] != HP)){
                y_pos = y2 * TILE_SIZE;
                y_pos -= (height_frame_ +1);
                y_val_ = 0;
                on_ground_ = true;
            }
        }else if ( y_val_ < 0){
            //on_ground = false;
            if ( (map_data.tile[y1][x1] > 0 && map_data.tile[y1][x1] < 20 && map_data.tile[y1][x1] != HP )
                || (map_data.tile[y1][x2] > 0 && map_data.tile[y1][x2] < 20 && map_data.tile[y1][x2] != HP)){
                y_pos = (y1+1)*TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos += x_val_;
    y_pos += y_val_;

    if ( x_pos < 0){
        x_pos = 0;
    }else if ( x_pos + width_frame_  >  map_data.max_x){
        x_pos = map_data.max_x - width_frame_ - 1;
    }

    // xu ly thoi gian chet
    if (y_pos > map_data.max_y){
        time_comeback_ = 60;

    }
}

void MonsterThreadObject::HandleMove(SDL_Renderer* screen , Map &map_data){
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // check theo chieu ngang
    int height_min  = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;


    // check xem  nhan vat nam tu o thu bao nhieu den o thu bao nhieu
    x1 = (x_pos + x_val_)/TILE_SIZE;
    x2 = (x_pos + x_val_ + width_frame_ - 1)/TILE_SIZE; // -1 de dam bao duong bien cua cua nhan vat khong trung duong bien cua chuong ngai vat

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min -1)/ TILE_SIZE;
    if (type_move_ == MOVE){
            if ( x_pos > bounded_right_move
                || (map_data.tile[y1][x2] > 0 && map_data.tile[y1][x2] < 20 && map_data.tile[y1][x2] != HP)
                ||(map_data.tile[y2][x2] > 0 && map_data.tile[y2][x2] < 20 && map_data.tile[y2][x2] != HP)){
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                loadImage("assets//slimemonster.jpg" , screen);
            }else if ( x_pos < bounded_left_move
                      ||(map_data.tile[y1][x1] > 0 && map_data.tile[y1][x1] < 20 && map_data.tile[y1][x1] != HP)
                    || (map_data.tile[y2][x1] > 0 && map_data.tile[y2][x1] < 20 && map_data.tile[y2][x1] != HP )){
                input_type_.left_ = 0;
                input_type_.right_ = 1;
                loadImage("assets//slimemonsterright.jpg" , screen);
            }
    }
}


void MonsterThreadObject::InitBullet(AttackObject* p_bullet , SDL_Renderer* screen){
    if (p_bullet != NULL){
        p_bullet->set_attack_type(AttackObject::GATTINGGUN);
        bool ret = p_bullet->LoadImageAttack(screen);
        if (ret){
            p_bullet->set_is_move(true);
            p_bullet->set_attack_direction(AttackObject::DIR_LEFT);
            p_bullet->setRect(this->get_x_pos() - map_x -20, this->get_y_pos() - map_y + 25);
            p_bullet->set_x_val(12);


            bullet_list_.push_back(p_bullet);
        }
    }
}

void MonsterThreadObject::MakeBullet(SDL_Renderer* screen , const int& x_bounded , const int& y_bounded , const float& x_player){
    for ( int i = 0 ; i < bullet_list_.size() ; i++){
        AttackObject* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL){
            if (p_bullet->get_is_move() == true && on_ground_ == true){
                int distance_attack = rect_.x + width_frame_ - p_bullet->getRect().x;
                int start_attack_ = rect_.x + width_frame_- x_player;
                if (start_attack_ > 0 && start_attack_ < 600 && distance_attack > 0 && distance_attack < 500){
                    p_bullet->HandleMove(x_bounded , y_bounded);
                    p_bullet->Render(screen , NULL);
                }else{
                    p_bullet->set_is_move(false);
                }
            }else{
                // neu dan cua monster di qua khoang gioi han thi bat dau ban tiep
                p_bullet->set_is_move(true);
                p_bullet->setRect(this->get_x_pos() - map_x -20, this->get_y_pos() - map_y + 25);
            }
        }
    }
}


// remove attack
void MonsterThreadObject::RemoveAttack(const int& index){
    int size_ = bullet_list_.size();
    if (size_ > 0 && index < size_){
        AttackObject* p_attack = bullet_list_.at(index);
        bullet_list_.erase(bullet_list_.begin() + index);

        if (p_attack){
            delete p_attack;
            p_attack = NULL;
        }
    }
}

void MonsterThreadObject::InitState(StateHp* p_state , SDL_Renderer* screen , const int& state_hp){
    if (p_state != NULL){
        p_state->set_state_hp(state_hp);
        bool ret = p_state->loadImageState(screen);
        if (ret){
            p_state->setRect(this->get_x_pos() - map_x + 10 , this->get_y_pos() - map_y -10);
            list_state_hp.push_back(p_state);
        }
    }
}

void MonsterThreadObject::HandleStateHp(SDL_Renderer* screen){
    for ( int i =0 ; i < list_state_hp.size() ; i++){
        StateHp* p_state = list_state_hp.at(i);
        if ( p_state != NULL){
            p_state->Render(screen , NULL);
            p_state->setRect(this->get_x_pos() - map_x + 10 , this->get_y_pos() - map_y - 10);
        }
    }
}





