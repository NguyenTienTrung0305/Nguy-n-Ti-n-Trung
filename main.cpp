#include "CommonFuntion.h"
#include "BaseObject.h"
#include "game_map.h"
#include "PlayerObject.h"
#include "Timerfps.h"


Mix_Music *gMusic1 = NULL;
Mix_Music *gMusic2 = NULL;
Mix_Music *gMusic3 = NULL;


BaseObject baseobject;



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
        p_player.HandleAttack(g_screen);
        p_player.setMapXY(map_data.start_x_ , map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap(map_data); // cap nhat lai map
        game_map.DrawMap(g_screen); // ve lai map

        SDL_RenderPresent(g_screen);

        int real_int_time = timer_fbs.get_tick(); // thoi gian thuc te chay het 1 frame
        int one_frame_run_howlong = 1000 / FRAME_PER_SECOND; // ms
        if(real_int_time < one_frame_run_howlong){
            int delay_time = one_frame_run_howlong - real_int_time;
            if ( delay_time >= 0 ) SDL_Delay(delay_time);
        }
    }

    Close();
    return 0;
}

