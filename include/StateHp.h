#ifndef STATEHP_H
#define STATEHP_H
#include "BaseObject.h"

class StateHp : public BaseObject
{
    public:
        StateHp();
        virtual ~StateHp();

        enum State{
            HP_0 = 0,
            HP_1 = 1,
            HP_2 = 2,
            HP_3 = 3,
        };

        bool loadImageState(SDL_Renderer* screen);
        void set_state_hp(const int& stateHP){state_hp = stateHP;}
        int get_state_hp() const {return state_hp;}

    protected:

    private:
        int state_hp;

};

#endif // STATEHP_H
