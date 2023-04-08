#ifndef NUMBEROFPLAYERSLIVES_H
#define NUMBEROFPLAYERSLIVES_H
#include "CommonFuntion.h"
#include "BaseObject.h"

class NumberOfPlayersLives : BaseObject
{
    public:
        NumberOfPlayersLives();
        virtual ~NumberOfPlayersLives();

        void setNum(const int& Num){number_ = Num;}
        void addPos(const int& xPos);
        void Show(SDL_Renderer* screen);
        void Init(SDL_Renderer* screen);

        void IncreaseNumber();
        void DecreaseNumber();

    protected:

    private:
        int number_;
        std::vector<int> pos_list;  // vi tri render so mang

};

#endif // NUMBEROFPLAYERSLIVES_H
