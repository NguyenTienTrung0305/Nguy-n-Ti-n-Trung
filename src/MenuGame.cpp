#include "MenuGame.h"

MenuGame::MenuGame()
{
    //ctor
}

MenuGame::~MenuGame()
{
    //dtor
}

int MenuGame::ShowMenu(SDL_Renderer* screen , TTF_Font* font){
    BaseObject::loadImage("assets//menu.jpg" , screen);

    const int numberItem = 2;
    SDL_Rect arr_menu[numberItem];
    arr_menu[0].x = 200;
    arr_menu[0].y = 200;
    arr_menu[1].x = 200;
    arr_menu[1].y = 400;

    TextObject text_menu[numberItem];
    text_menu[0].setText("Play Game");
    text_menu[0].setColor(TextObject::WHITE_TEXT);
    text_menu[0].LoadFromRenderText(font , screen);

    text_menu[1].setText("Exit");
    text_menu[1].setColor(TextObject::WHITE_TEXT);
    text_menu[1].LoadFromRenderText(font , screen);


    SDL_Event events_;

    int xm = 0;
    int ym = 0;
    while(true){

        BaseObject::Render(screen , NULL);
        text_menu[0].RenderText(screen , arr_menu[0].x , arr_menu[0].y);
        text_menu[1].RenderText(screen , arr_menu[1].x , arr_menu[1].y);

        SDL_RenderPresent(screen);

        while(SDL_PollEvent(&events_)){
            switch(events_.type){
                case SDL_QUIT:
                    return 0;
                case SDL_MOUSEMOTION:{
                    xm = events_.motion.x;
                    ym = events_.motion.y;

                    if (xm >= 190 && xm <= 380 && ym >= 200 && ym <= 250){
                        //BaseObject::Free();
                        text_menu[0].setColor(TextObject::RED_TEXT);
                        text_menu[0].LoadFromRenderText(font , screen);
                    }
                    else if (xm >= 190 && xm <= 300 && ym >= 400 && ym <= 450){
                        //BaseObject::Free();
                        text_menu[1].setColor(TextObject::RED_TEXT);
                        text_menu[1].LoadFromRenderText(font , screen);
                    }else{
                        text_menu[0].setColor(TextObject::WHITE_TEXT);
                        text_menu[1].setColor(TextObject::WHITE_TEXT);
                        text_menu[0].LoadFromRenderText(font , screen);
                        text_menu[1].LoadFromRenderText(font , screen);
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:{
                    xm = events_.button.x;
                    ym = events_.button.y;
                    if (xm >= 190 && xm <= 380 && ym >= 200 && ym <= 250){
                        BaseObject::Free();
                        text_menu[0].Free();
                        text_menu[1].Free();
                        IMG_Quit();
                        return 1;
                    }
                    if ( xm >= 190 && xm <= 300 && ym >= 400 && ym <= 450){
                        BaseObject::Free();
                        text_menu[0].Free();
                        text_menu[1].Free();
                        IMG_Quit();
                        return 0;
                    }
                    break;
                }

            }
        }
    }
    BaseObject::Free();
    text_menu[0].Free();
    text_menu[1].Free();
    IMG_Quit();
    return 1;
}

int MenuGame::ShowMenuWinnerAndLose(SDL_Renderer* screen , TTF_Font* font){
        BaseObject::loadImage("assets//menulose.jpg" , screen);

    const int numberItem = 2;
    SDL_Rect arr_menu[numberItem];
    arr_menu[0].x = 530;
    arr_menu[0].y = 300;
    arr_menu[1].x = 570;
    arr_menu[1].y = 450;

    TextObject text_menu[numberItem];
    text_menu[0].setText("Play Again!!");
    text_menu[0].setColor(TextObject::WHITE_TEXT);
    text_menu[0].LoadFromRenderText(font , screen);

    text_menu[1].setText("Exit");
    text_menu[1].setColor(TextObject::WHITE_TEXT);
    text_menu[1].LoadFromRenderText(font , screen);


    SDL_Event events_;

    int xm = 0;
    int ym = 0;
    while(true){

        BaseObject::Render(screen , NULL);
        text_menu[0].RenderText(screen , arr_menu[0].x , arr_menu[0].y);
        text_menu[1].RenderText(screen , arr_menu[1].x , arr_menu[1].y);

        SDL_RenderPresent(screen);

        while(SDL_PollEvent(&events_)){
            switch(events_.type){
                case SDL_QUIT:
                    return 0;
                case SDL_MOUSEMOTION:{
                    xm = events_.motion.x;
                    ym = events_.motion.y;

                    if (xm >= 520 && xm <= 710 && ym >= 300 && ym <= 350){
                        //BaseObject::Free();
                        text_menu[0].setColor(144,238,144);
                        text_menu[0].LoadFromRenderText(font , screen);
                    }
                    else if (xm >= 560 && xm <= 670 && ym >= 450 && ym <= 500){
                        //BaseObject::Free();
                        text_menu[1].setColor(144,238,144);
                        text_menu[1].LoadFromRenderText(font , screen);
                    }else{
                        text_menu[0].setColor(TextObject::WHITE_TEXT);
                        text_menu[1].setColor(TextObject::WHITE_TEXT);
                        text_menu[0].LoadFromRenderText(font , screen);
                        text_menu[1].LoadFromRenderText(font , screen);
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:{
                    xm = events_.button.x;
                    ym = events_.button.y;
                    if (xm >= 520 && xm <= 710 && ym >= 300 && ym <= 350){
                        BaseObject::Free();
                        text_menu[0].Free();
                        text_menu[1].Free();
                        IMG_Quit();
                        return 1;
                    }
                    if ( xm >= 560 && xm <= 670 && ym >= 450 && ym <= 500){
                        BaseObject::Free();
                        text_menu[0].Free();
                        text_menu[1].Free();
                        IMG_Quit();
                        return 0;
                    }
                    break;
                }

            }
        }
    }
    BaseObject::Free();
    text_menu[0].Free();
    text_menu[1].Free();
    IMG_Quit();
    return 1;
}

