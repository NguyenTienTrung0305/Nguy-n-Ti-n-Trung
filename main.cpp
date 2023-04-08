#include "CommonFuntion.h"
#include "BaseObject.h"
#include "game_map.h"
#include "PlayerObject.h"
#include "Timerfps.h"
#include "MonsterThreadObject.h"
#include "TextObject.h"
#include "NumberOfPlayersLives.h"


using namespace std;

Mix_Music *gMusic1 = NULL;
Mix_Music *gMusic2 = NULL;
Mix_Music *gMusic3 = NULL;


BaseObject baseobject;


TTF_Font* font_time;



bool InitData(){
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if ( ret < 0 ) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY , "1");

    // initialize SDL_mixer
    if ( Mix_OpenAudio(44100 , MIX_DEFAULT_FORMAT , 2 , 2048) < 0){
        printf("SDL_mixer could not initialize! SDL_mixer error: %s\n" , Mix_GetError());
        success = false;
    }

    g_window = SDL_CreateWindow("Demo" , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH , SCREEN_HEIGHT , false);
    if ( g_window == NULL){
        success = false;
    }else{
        g_screen = SDL_CreateRenderer(g_window , -1 , 0);
        if (g_screen == NULL){
            success = false;
        }else{
            SDL_SetRenderDrawColor(g_screen , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR);
        }


        // init fonts
        if (TTF_Init() == -1){
            success = false;
        }

        font_time = TTF_OpenFont("fonts//font3.ttf" , 15);
        if (font_time == NULL){
            success = false;
        }
    }
    return success;
}

bool LoadMeida(){
    // flags
    bool success = true;

    // load music
    gMusic1 = Mix_LoadMUS("music//music1.mp3");
    if ( gMusic1 == NULL){
        success = false;
    }

    gMusic2 = Mix_LoadMUS("music//music2.mp3");
    if ( gMusic2 == NULL){
        success = false;
    }

    gMusic3 = Mix_LoadMUS("music//music3.mp3");
    if ( gMusic3 == NULL){
        success = false;
    }
    return success;
}


bool LoadBackground(){
    bool ret = baseobject.loadImage("assets//Background_0.png" , g_screen);
    if ( ret = false)return false;
    return true;
}


void Close(){
    baseobject.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    // free music
    Mix_FreeMusic(gMusic1);
    Mix_FreeMusic(gMusic2);
    Mix_FreeMusic(gMusic3);
    gMusic1 = NULL;
    gMusic2 = NULL;
    gMusic3 = NULL;


    IMG_Quit();
    SDL_Quit();
}




// create object MonsterThreadObject
vector<MonsterThreadObject*> MakeThreadList(){
    vector<MonsterThreadObject*> list_threads;
    // monster move
    MonsterThreadObject* monster_move_1 = new MonsterThreadObject[40];
    for ( int i = 0 ; i < 40 ; i++){
        MonsterThreadObject* monster1 = (monster_move_1+i);
        if ( monster1 != NULL){
            monster1->loadImage("assets//slimemonster.jpg" , g_screen);
            monster1->set_clip();
            monster1->set_input_left(1);
            monster1->set_type_move(MonsterThreadObject::MOVE);
            monster1->set_x_pos(500 + 603*i);
            monster1->set_y_pos(200);

            int boundedleft = monster1->get_x_pos() - 60;
            int boundedright = monster1->get_x_pos() + 60;
            monster1->set_bounded_position(boundedleft , boundedright);

            StateHp* p_state = new StateHp();
            monster1->InitState(p_state , g_screen , 0);

            list_threads.push_back(monster1);
        }

    }

    // monster stand still
    MonsterThreadObject* thread_objs = new MonsterThreadObject[21];
    for ( int i =0 ; i < 21 ; i++){
        MonsterThreadObject* p_thread = (thread_objs + i);
        if ( p_thread != NULL){
            p_thread->loadImage("assets//monster.jpg" , g_screen);
            p_thread->set_clip();
            p_thread->set_type_move(MonsterThreadObject::STAND_STILL);
            p_thread->set_input_left(0);

            p_thread->set_x_pos(760+ i*1190);
            p_thread->set_y_pos(250);


            AttackObject* p_bullet = new AttackObject();
            p_thread->InitBullet(p_bullet , g_screen);

            StateHp* p_state = new StateHp();
            p_thread->InitState(p_state , g_screen , 0);


            list_threads.push_back(p_thread);
        }
    }
    return list_threads;
}




int main(int argc , char* argv[]){
    if (InitData() == false) return -1;

    if (!LoadMeida()) return -1;
    if (LoadBackground() == false) return -1;

    Timerfps timer_fbs;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);


    PlayerObject p_player;
    p_player.loadImage("assets//assassinrightrun.jpg" , g_screen);
    p_player.Set_Clips();

    p_player.InitPlayerLives(g_screen);

    // number of player's lives
    //NumberOfPlayersLives players_lives;
    //players_lives.Init(g_screen); // khoi tao so mang cua nhanh vat


    vector<MonsterThreadObject*> list_ = MakeThreadList();


    // Text Time
    TextObject time_game;
    time_game.setColor(255 , 228 , 255);

    bool isQuit = false;
    while (!isQuit){
        timer_fbs.start();
        while (SDL_PollEvent(&g_event) != 0 ){
            if (g_event.type == SDL_QUIT){
                isQuit = true;
            }else if (g_event.type == SDL_KEYDOWN){
                switch (g_event.key.keysym.sym){
                    case SDLK_7:{
                        Mix_HaltMusic();
                        // if there is no music playing
                        if (Mix_PlayingMusic() == 0){
                            // play the music
                            Mix_PlayMusic(gMusic1 , -1);
                        }
                        // if music is being played
                        else{
                            // if music is paused
                            if (Mix_PausedMusic() == 1){
                                // resume music
                                Mix_ResumeMusic();
                            }
                            // if music is playing
                            else{
                                // pause the music
                                Mix_PausedMusic();
                            }
                        }
                        break;
                    }
                    case SDLK_8:{
                        Mix_HaltMusic();
                        // if there is no music playing
                        if (Mix_PlayingMusic() == 0){
                            // play the music
                            Mix_PlayMusic(gMusic2 , -1);
                        }
                        // if music is being played
                        else{
                            // if music is paused
                            if (Mix_PausedMusic() == 1){
                                // resume music
                                Mix_ResumeMusic();
                            }
                            // if music is playing
                            else{
                                // pause the music
                                Mix_PausedMusic();
                            }
                        }
                        break;
                    }
                    case SDLK_9:{
                        Mix_HaltMusic();
                        // if there is no music playing
                        if (Mix_PlayingMusic() == 0){
                            // play the music
                            Mix_PlayMusic(gMusic3 , -1);
                        }
                        // if music is being played
                        else{
                            // if music is paused
                            if (Mix_PausedMusic() == 1){
                                // resume music
                                Mix_ResumeMusic();
                            }
                            // if music is playing
                            else{
                                // pause the music
                                Mix_PausedMusic();
                            }
                        }
                        break;
                    }
                    case SDLK_0:{
                        // stop the music
                        Mix_HaltMusic();
                        break;
                    }
                }
            }


            p_player.HandelInputAction(g_event , g_screen);
        }

        SDL_SetRenderDrawColor(g_screen ,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR );
        SDL_RenderClear(g_screen);

        baseobject.Render(g_screen , NULL);


        Map map_data = game_map.getMap();

        p_player.setMapXY(map_data.start_x_ , map_data.start_y_);
        p_player.DoPlayer(map_data);



        game_map.SetMap(map_data); // cap nhat lai map
        game_map.DrawMap(g_screen); // ve lai map

        p_player.HandleAttack(g_screen); // show image attack
        p_player.Show(g_screen); // show player

        float x_player = p_player.getRect().x;

        //number of player's lives
        p_player.ShowPlayerLives(g_screen);


        // monster
        for ( int i = 0 ; i < list_.size() ; i++){
            MonsterThreadObject* p_thread = list_.at(i);
            if ( p_thread != NULL){
                p_thread->setMap(map_data.start_x_ , map_data.start_y_);
                p_thread->HandleMove(g_screen , map_data);
                p_thread->MakeBullet(g_screen , SCREEN_WIDTH, SCREEN_HEIGHT , x_player);
                p_thread->HandleStateHp(g_screen);
                p_thread->DoPlayer(map_data);
                p_thread->Show(g_screen);


                // lay ra vi tri cua player
                SDL_Rect rect_player;
                rect_player.x = p_player.getRect().x;
                rect_player.y = p_player.getRect().y;
                rect_player.w = p_player.getRect().w /7;
                rect_player.h = p_player.getRect().h;


                // check va chạm player với attack enemy
                bool check1 = false;
                vector<AttackObject* > p_list_attack = p_thread->get_bullet_list();
                for ( int j = 0 ; j < p_list_attack.size() ; j++){
                    AttackObject* p_attack = p_list_attack.at(j);
                    if (p_attack){
                        check1 = SDLCommonFuncion::CheckCollision(p_attack->getRect() , rect_player);
                        if (check1){
                            p_thread->RemoveAttack(j);
                            AttackObject* p_attack = new AttackObject();
                            p_thread->InitBullet(p_attack , g_screen);
                            break;
                        }
                    }
                }


                // check va cham player voi enemy
                SDL_Rect rect_thread;
                rect_thread.x = p_thread->getRect().x;
                rect_thread.y = p_thread->getRect().y;
                rect_thread.w = p_thread->getRect().w/9;
                rect_thread.h = p_thread->getRect().h;


                bool check2 = SDLCommonFuncion::CheckCollision(rect_player , rect_thread);
                if ( check1 || check2){
                    p_player.num_die_++;
                    if ( p_player.num_die_ <= 5){
                        p_player.die_ = Mix_LoadWAV("music//die.wav");
                        Mix_PlayChannel(-1 , p_player.die_ , 0);
                        p_player.set_y_pos(641);
                        p_player.set_time_comeback(50);

                        p_player.DecreaseNumber();
                        continue;
                    }else{
                       p_thread->Free();
                       Close();
                       SDL_Quit();
                       return 0;
                    }
                }

            }
        }


        vector<AttackObject* > attack_arr  = p_player.get_attack_list();
        for ( int i = 0 ; i < attack_arr.size() ; i++){
            AttackObject* p_attack = attack_arr.at(i);
            if (p_attack!= NULL){
                for ( int j = 0 ; j < list_.size() ; j++){
                    MonsterThreadObject* obj_monster = list_.at(j);
                    if (obj_monster != NULL){

                        // rect monster
                        SDL_Rect mRect;
                        mRect.x = obj_monster->getRect().x;
                        mRect.y = obj_monster->getRect().y;
                        mRect.w = obj_monster->get_width_frame();
                        mRect.h = obj_monster->get_height_frame();

                        // rect attack
                        SDL_Rect attackRect = p_attack->getRect();


                        bool check = SDLCommonFuncion::CheckCollision(attackRect , mRect);

                        if ( check){
                            p_player.RemoveAttack(i);
                            int x =  obj_monster->get_times_beaten();
                            x++;
                            obj_monster->set_times_beaten(x);

                            vector<StateHp*> list_state = obj_monster->get_list_state_hp();
                            for ( int i = 0; i < list_state.size() ; i++){
                                StateHp* p_state = list_state.at(i);
                                obj_monster->InitState(p_state , g_screen , x);
                            }

                            if (x >= 4){
                                obj_monster->Free();
                                list_.erase(list_.begin() + j);
                            }
                        }

                    }
                }
            }
        }


        // show time
        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000; // thoi diem hien tai
        std::string char_sequance = std::to_string(time_val);
        str_time += char_sequance;
        time_game.setText(str_time);
        time_game.LoadFromRenderText(font_time , g_screen);
        time_game.RenderText(g_screen , SCREEN_WIDTH - 120 , 15 );



        SDL_RenderPresent(g_screen);

        int real_int_time = timer_fbs.get_tick(); // thoi gian thuc te chay het 1 frame
        int one_frame_run_howlong = 1000 / FRAME_PER_SECOND; // ms
        if(real_int_time < one_frame_run_howlong){
            int delay_time = one_frame_run_howlong - real_int_time;
            if ( delay_time >= 0 ) SDL_Delay(delay_time);
        }
    }

    for ( int i = 0 ; i <list_.size() ; i++){
        MonsterThreadObject* p_thread = list_.at(i);
        if (p_thread){
            p_thread->Free();
            p_thread = NULL;
        }
    }
    list_.clear();

    Close();
    return 0;
}




