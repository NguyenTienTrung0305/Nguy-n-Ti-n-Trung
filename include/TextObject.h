#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H
#include "CommonFuntion.h"

class TextObject
{
    public:
        TextObject();
        virtual ~TextObject();

        enum TextColor{
            RED_TEXT = 0 ,
            WHITE_TEXT = 1,
            BLACK_TEXT = 2,
        };
        bool LoadFromRenderText(TTF_Font* font , SDL_Renderer* screen); // chuyen text thanh texture
        void Free();

        void setColor(Uint8 red , Uint8 green , Uint8 blue);
        void setColor(int type);

        void RenderText(SDL_Renderer* screen ,
                        int xpos,
                        int ypos,
                        SDL_Rect* clip = NULL,
                        double angle = 0.0, // goc nghieng
                        SDL_Point* center = NULL,
                        SDL_RendererFlip flip = SDL_FLIP_NONE); // lat anh

        int get_width() const {return width_;}
        int get_height() const {return height_;}

        void setText(const std::string& text){char_sequance = text;}
        std::string getText() const {return char_sequance;}


    protected:

    private:
        std::string char_sequance;
        SDL_Color text_color;
        SDL_Texture* texture_;

        int width_;
        int height_;
};

#endif // TEXTOBJECT_H
