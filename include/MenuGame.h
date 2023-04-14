#ifndef MENUGAME_H
#define MENUGAME_H
#include "BaseObject.h"
#include "TextObject.h"
#include "MenuGame.h"

class MenuGame : BaseObject
{
    public:
        MenuGame();
        virtual ~MenuGame();

        int ShowMenu(SDL_Renderer* screen , TTF_Font* font);
        int ShowMenuWinnerAndLose(SDL_Renderer* screen , TTF_Font* font);


    protected:

    private:
};

#endif // MENUGAME_H
