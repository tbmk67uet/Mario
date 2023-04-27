#ifndef MENUOBJECT_H_INCLUDED
#define MENUOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "TextObject.h"
#include "SDL_ttf.h"

namespace MenuObject
{
    bool LoadImg(std::string path,SDL_Renderer* renderer);
    int ShowMenu(SDL_Renderer* renderer,TTF_Font* font,BaseObject gBackground);
}



#endif // MENUOBJECT_H_INCLUDED
