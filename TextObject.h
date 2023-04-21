#ifndef TEXTOBJECT_H_INCLUDED
#define TEXTOBJECT_H_INCLUDED

#include "SDL_Utils.h"
#include "BaseObject.h"

class TextObject : public BaseObject
{
public:
    TextObject();
    ~TextObject();
    enum TextColor
    {
        RED_TEXT=0,
        WHITE_TEXT=1,
        BLACK_TEXT=2,
    };

    bool LoadFromRenderText(TTF_Font* font,SDL_Renderer* renderer);
    void Free();

    void SetColor(uint8_t red,uint8_t green,uint8_t blue);
    void SetColor(int type);

    void RenderText(SDL_Renderer *renderer,
                    int xp,int yp,
                    SDL_Rect* clip=NULL,
                    double angle=0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);


     void SetText(std::string& text){strVal = text;}

private:
    std::string strVal;
    SDL_Color textColor;
    SDL_Texture* texture;
    int width;
    int height;
};

#endif // TEXTOBJECT_H_INCLUDED
