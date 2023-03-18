#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "CommonFuntion.h"

class BaseObject
{
    public:
        BaseObject();
        virtual ~BaseObject();

        void setRect(const int &x  , const int& y){rect_.x = x , rect_.y = y;}
        SDL_Rect getRect() const {return rect_;} // bien const de dam bao chi lay du lieu
        SDL_Texture* getObject() const {return p_object_;}

        virtual bool loadImage(std::string path , SDL_Renderer* screen);
        void Render(SDL_Renderer* des , const SDL_Rect* clip = NULL);
        void Free();

    protected:
        SDL_Texture* p_object_;
        SDL_Rect rect_; // vi tri bin image

    private:
};

#endif // BASEOBJECT_H

