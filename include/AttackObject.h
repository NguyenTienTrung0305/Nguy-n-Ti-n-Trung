#ifndef ATTACKOBJECT_H
#define ATTACKOBJECT_H

#include "BaseObject.h"

class AttackObject : public BaseObject
{
    public:
        AttackObject();
        virtual ~AttackObject();

        // huong attack
        enum AttackDir{
            DIR_RIGHT = 0,
            DIR_LEFT = 1 ,
        };

        void set_x_val(const int& xVal){x_val_ = xVal;}
        void set_y_val(const int& yVal){y_val_ = yVal;}
        int get_x_val() const {return x_val_;}
        int get_y_val() const {return y_val_;}

        void set_is_move(const bool& isMove){is_move_ = isMove;}
        bool get_is_move() const {return is_move_;}

        void set_attack_direction(const int attackDirection) {attack_direction = attackDirection;}
        int get_attack_direction() const {return attack_direction;}

        void HandleMove(const int& x_border , const int& y_border);

    protected:

    private:
        int x_val_;
        int y_val_;
        bool is_move_;

        int attack_direction; // huong tan cong
};

#endif // ATTACKOBJECT_H
