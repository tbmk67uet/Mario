#include "TextObject.h"

TextObject::TextObject()
{
    textColor.r=255;
    textColor.g=255;
    textColor.b=255;
    texture = NULL;
}

TextObject::~TextObject()
{

}

bool TextObject::LoadFromRenderText(TTF_Font* font,SDL_Renderer* renderer)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,strVal.c_str(),textColor);
    if(text_surface)
    {
        texture = SDL_CreateTextureFromSurface(renderer,text_surface);
        width = text_surface->w;
        height = text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return texture != NULL;
}

void TextObject::Free()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void TextObject::SetColor(uint8_t red,uint8_t green,uint8_t blue)
{
    textColor.r=red;
    textColor.g=green;
    textColor.b=blue;
}

void TextObject::SetColor(int type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color = {255,0,0};
        textColor = color;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color = {255,255,255};
        textColor = color;
    }
    else if(type == BLACK_TEXT)
    {
        SDL_Color color = {0,0,0};
        textColor = color;
    }
}

void TextObject::RenderText(SDL_Renderer *renderer,
                            int xp,int yp,
                            SDL_Rect* clip,
                            double angle,
                            SDL_Point* center,
                            SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {xp,yp,width,height};
    if(clip != NULL)
    {
        renderQuad.w=clip->w;
        renderQuad.h=clip->h;
    }
    SDL_RenderCopyEx(renderer,texture,clip,&renderQuad,angle,center,flip);
}
