#include "PlayerObject.h"
#include "MenuGame.h"

//const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

PlayerObject::PlayerObject()
{
    x_val_ = 0;
    y_val_ = 0;

    x_pos = 0;
    y_pos = 0;
    width_frame_ = 0;
    heigth_frame_ = 0;
    status_ = FREE_FALL;

    key_events_.left_ = 0;
    key_events_.right_ = 0;
    key_events_.up_ = 0;
    key_events_.down_ = 0;
    key_events_.jump_ = 0;

    on_ground = false;

    map_x_ = 0;
    map_y_ = 0;

    time_come_back = 0;

    move_ = NULL;
    throwknife_ = NULL;
    die_ = NULL;

}

PlayerObject::~PlayerObject()
{
    //dtor
}

void PlayerObject::loadImageAttack(std::string path){
    BaseObject::loadImage(path , g_screen);
}

bool PlayerObject::loadImage(std::string path , SDL_Renderer* screen){
    bool ret = BaseObject::loadImage(path , screen);
    if (ret == true){
        width_frame_ = rect_.w / 7;
        heigth_frame_ = rect_.h;
    }

    return ret;
}



void PlayerObject::Set_Clips(){
    if ( width_frame_ > 0 &&  heigth_frame_ > 0){
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = heigth_frame_;

        for ( int i = 1 ; i < 7 ; i++){
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = heigth_frame_;
        }
    }
}

void PlayerObject::Show(SDL_Renderer* des){
    /*
    if (status_ == WALK_LEFT){
        loadImage("assets//assassinleftrun.jpg" , des);
    }else{
        loadImage("assets//assassinrightrun.jpg", des);
    }
    */
    UpdateImagePlayer(des);
    if ( key_events_.left_ == 1 || key_events_.right_ == 1){
        frame_++;
    }else{
        frame_ = 0;
    }

    if ( frame_ >= 7){
        frame_ = 0;
    }

    rect_.x = x_pos - map_x_; // khi chay nhan vat di man hinh bi cuon theo nen ta phai tru di luong bi cuon theo do
    rect_.y = y_pos - map_y_;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x , rect_.y , width_frame_ , heigth_frame_}; // kich thuoc chuan nhat cua tam anh

    SDL_RenderCopy(des , p_object_ , current_clip , &renderQuad);

}

void PlayerObject::HandelInputAction(SDL_Event events , SDL_Renderer* screen){
    if (events.type == SDL_KEYDOWN){
        switch(events.key.keysym.sym){
            case SDLK_RIGHT:{
                //move_ = Mix_LoadWAV("music//medium.wav");
                //Mix_PlayChannel(-1 , move_ , 0);
                status_ = WALK_RIGHT;
                key_events_.right_ = 1; // tang frame len
                key_events_.left_ = 0;
                UpdateImagePlayer(screen);
                break;
            }
            case SDLK_LEFT:{
                //move_ = Mix_LoadWAV("music//medium.wav");
                //Mix_PlayChannel(-1 , move_ , 0);
                status_ = WALK_LEFT;
                key_events_.left_ = 1; // tang frame len
                key_events_.right_ = 0;
                UpdateImagePlayer(screen);
                break;
            }
            case SDLK_UP:{
                if ( on_ground == true){
                    move_ = Mix_LoadWAV("music//jump.wav");
                    Mix_PlayChannel(-1 , move_ , 0);
                }
                key_events_.jump_ = 1;
                break;
            }
            default:
                break;
        }
    }else if ( events.type == SDL_KEYUP){
        switch(events.key.keysym.sym){
            case SDLK_RIGHT:{
                key_events_.right_ = 0;
                break;
            }
            case SDLK_LEFT:{
                key_events_.left_ = 0;
                break;
            }
            case SDLK_UP:{
                key_events_.jump_ = 0;
                break;
            }
            default:
                break;
        }
    }

    if ( events.type == SDL_MOUSEBUTTONDOWN){
        if ( events.button.button == SDL_BUTTON_LEFT){
            throwknife_ = Mix_LoadWAV("music//throwknife.wav");
            Mix_PlayChannel(-1 , throwknife_ , 0);
            AttackObject* p_attack = new AttackObject();

            if ( status_ == WALK_LEFT){
                p_attack->loadImage("assets//attackleft.jpg" , screen);
                p_attack->set_attack_direction(AttackObject::DIR_LEFT);
                p_attack->setRect(this->rect_.x , rect_.y + heigth_frame_*0.3);
            }else{
                p_attack->loadImage("assets//attackright.jpg" , screen);
                p_attack->set_attack_direction(AttackObject::DIR_RIGHT);
                p_attack->setRect(this->rect_.x + width_frame_ -20 , rect_.y + heigth_frame_*0.3);
            }

            p_attack->set_x_val(20);
            p_attack->set_is_move(true);
            p_attack_list.push_back(p_attack); // nap knife
        }
    }
}

void PlayerObject::DoPlayer(Map& map_data){
    // neu nhan vat van con song
    if (time_come_back == 0){
        x_val_ = 0;
        y_val_ += 0.8;

        if (y_val_ >= MAX_FALL_SPEED){
            y_val_ = MAX_FALL_SPEED;
        }

        if ( key_events_.left_ == 1){
            x_val_ -= PLAYER_SPEED;
        }else if ( key_events_.right_ == 1){
            x_val_ += PLAYER_SPEED;
        }
        if ( key_events_.jump_ == 1){
            if ( on_ground == true){
                y_val_ = - PLAYER_JUMP_VAL;
            }
            on_ground = false;
            key_events_.jump_ = 0;
        }
        CheckToMap(map_data);
        CenterEntityOnMap(map_data);
    }

    // neu nhan vat chet
    if (time_come_back > 0){
        time_come_back --;
        if (time_come_back == 0){
            on_ground = false; // bat dau roi tu tren xuong
            if ( x_pos > 256){
                x_pos -= 256; // lui lai 4 o
            }else{
                x_pos = 0;
            }
            y_pos = 0;
            y_val_ = 0;
            x_val_ = 0;
        }
    }
}



void PlayerObject::CheckToMap(Map& map_data){
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // check theo chieu ngang
    int height_min  = heigth_frame_ < TILE_SIZE ? heigth_frame_ : TILE_SIZE;


    // check xem  nhan vat nam tu o thu bao nhieu den o thu bao nhieu
    x1 = (x_pos + x_val_)/TILE_SIZE;
    x2 = (x_pos + x_val_ + width_frame_ - 1)/TILE_SIZE; // -1 de dam bao duong bien cua cua nhan vat khong trung duong bien cua chuong ngai vat

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min -1)/ TILE_SIZE;

    if ( x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_y){
        // eat hp
        if (map_data.tile[y1][x2] == HP || map_data.tile[y2][x2] == HP || map_data.tile[y1][x1] == HP || map_data.tile[y2][x1] == HP){
            num_die_--;
            players_lives.IncreaseNumber();
            map_data.tile[y1][x2] = 0;
            map_data.tile[y2][x2] = 0;
            map_data.tile[y1][x1] = 0;
            map_data.tile[y2][x1] = 0;
        }

        // winner
        if (map_data.tile[y1][x2] == PRINCESS || map_data.tile[y2][x2] == PRINCESS || map_data.tile[y1][x1] == PRINCESS || map_data.tile[y2][x1] == PRINCESS){
            Free();
            SDL_DestroyRenderer(g_screen);
            g_screen = NULL;
            SDL_DestroyWindow(g_window);
            g_window = NULL;
            IMG_Quit();
            SDL_Quit();
        }
        // moving to right
        if ( x_val_ > 0){
            if ((map_data.tile[y1][x2] > 0 && map_data.tile[y1][x2] < 20) ||(map_data.tile[y2][x2] > 0 && map_data.tile[y2][x2] < 20)){
                x_pos = x2*TILE_SIZE;
                x_pos -= (width_frame_ +1) ; // vi tri bat dau cua nhat vat bang vi tri cu cong them luong di chuyen
                x_val_ = 0;  // de khi gap chuong ngai vat du co an tiep cung khong di chuyen duoc
            }
        }else if (x_val_ < 0){
            if ((map_data.tile[y1][x1] > 0 && map_data.tile[y1][x1] < 20) || (map_data.tile[y2][x1] > 0 && map_data.tile[y2][x1] < 20 )){
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
    y2 = (y_pos + y_val_ + heigth_frame_ -1)/TILE_SIZE;


    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_y){
        if (map_data.tile[y2][x1] == HP || map_data.tile[y2][x2] == HP || map_data.tile[y1][x1] == HP || map_data.tile[y1][x2] == HP){
            map_data.tile[y2][x1] = 0;
            map_data.tile[y2][x2] = 0;
            map_data.tile[y1][x1] = 0;
            map_data.tile[y1][x2] = 0;
        }
        if (y_val_ > 0){
            if ( (map_data.tile[y2][x1] > 0 && map_data.tile[y2][x1] < 20) || (map_data.tile[y2][x2] > 0 && map_data.tile[y2][x2] < 20)){
                y_pos = y2 * TILE_SIZE;
                y_pos -= (heigth_frame_ +1);
                y_val_ = 0;
                on_ground = true;
                if ( status_ == FREE_FALL){
                    status_ = WALK_RIGHT;
                }
            }
        }else if ( y_val_ < 0){
            //on_ground = false;
            if ( (map_data.tile[y1][x1] > 0 && map_data.tile[y1][x1] < 20) || (map_data.tile[y1][x2] > 0 && map_data.tile[y1][x2] < 20)){
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
        num_die_ += 1;
        players_lives.DecreaseNumber();
        if (num_die_ > 5){
            Free();
            SDL_DestroyRenderer(g_screen);
            g_screen = NULL;
            SDL_DestroyWindow(g_window);
            g_window = NULL;
            IMG_Quit();
            SDL_Quit();
        }
        die_ = Mix_LoadWAV("music//die.wav");
        Mix_PlayChannel(-1 , die_ , 0);
        time_come_back = 60;

    }
}


void PlayerObject::CenterEntityOnMap(Map& map_data){
    map_data.start_x_ = x_pos - (SCREEN_WIDTH)/2;  // sau khi nhân vật đi đến nửa màn hình thì màn hình bị cuốn theo
    if ( map_data.start_x_ < 0){
        map_data.start_x_ = 0;
    }
    if ( map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x){
        map_data.start_x_ = map_data.max_x - SCREEN_WIDTH;
    }


    map_data.start_y_ = y_pos - (SCREEN_HEIGHT)/2;
    if (map_data.start_y_ < 0){
        map_data.start_y_ = 0;
    }
    if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y){
        map_data.start_y_ = map_data.max_y - SCREEN_HEIGHT;
    }
}

void PlayerObject::UpdateImagePlayer(SDL_Renderer* des){
    if ( on_ground == true){
        if ( status_ == WALK_LEFT){
            loadImage("assets//assassinleftrun.jpg" , des);
        }
        else if ( status_ == WALK_RIGHT){
             loadImage("assets//assassinrightrun.jpg" , des);
        }
    }else {
        if ( status_ == WALK_LEFT){
            loadImage("assets//assassinjumpleft.jpg" , des);
        }else{
            loadImage("assets//assassinjumpright.jpg" , des);
        }
    }
}


// xu ly attack
void PlayerObject::HandleAttack(SDL_Renderer* des){
    for ( int i = 0 ; i < p_attack_list.size() ; i++){
        AttackObject* p_attack = p_attack_list.at(i);
        if ( p_attack != NULL){
            if (p_attack->get_is_move() == true){
                p_attack->HandleMove(SCREEN_WIDTH , SCREEN_HEIGHT);
                p_attack->Render(des , NULL);
            }else{
                p_attack_list.erase(p_attack_list.begin() + i);
                if ( p_attack != NULL){
                    delete p_attack;
                    p_attack = NULL;
                }
            }
        }
    }
}

// remove attack
void PlayerObject::RemoveAttack(const int& index){
    int size_ = p_attack_list.size();
    if (size_ > 0 && index < size_){
        AttackObject* p_attack = p_attack_list.at(index);
        p_attack_list.erase(p_attack_list.begin() + index);
    }
}

void PlayerObject::InitPlayerLives(SDL_Renderer* screen){
    players_lives.Init(screen);
}
void PlayerObject::ShowPlayerLives(SDL_Renderer* screen){
    players_lives.Show(screen);
}
void PlayerObject::DecreaseNumber(){
    players_lives.DecreaseNumber();
}
void PlayerObject::IncreaseNumber(){
    players_lives.IncreaseNumber();
}
