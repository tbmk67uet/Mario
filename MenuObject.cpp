#include "MenuObject.h"
#include "BaseObject.h"

int MenuObject::ShowMenu(SDL_Renderer* renderer,TTF_Font* font,BaseObject gBackground)
{
    std::string s1 = "Enter To Play";
    std::string s2 = "Escape to Exit";
    int xm=0,ym=0;
    const int menuItems = 2;
    SDL_Rect pos_arr[menuItems];

    pos_arr[0].x=200;
    pos_arr[0].y=200;

    pos_arr[1].x=200;
    pos_arr[1].y=250;

    TextObject textMenu[menuItems];

    textMenu[0].SetColor(TextObject::WHITE_TEXT);
    textMenu[0].SetText(s1);
    textMenu[0].LoadFromRenderText(font,renderer);

    textMenu[1].SetColor(TextObject::WHITE_TEXT);
    textMenu[1].SetText(s2);
    textMenu[1].LoadFromRenderText(font,renderer);


    bool selected = 0;
    SDL_Event e;
    bool x = gBackground.LoadImg("Image/Start.png",renderer);
    gBackground.render(renderer,NULL);


    while(true)
    {
        for(int i=0; i<menuItems; i++)
        {
            textMenu[i].RenderText(renderer,pos_arr[i].x,pos_arr[i].y);
        }

        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_KEYDOWN:
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
                if(e.key.keysym.sym == SDLK_RETURN)
                {
                    return 0;
                }
            }
            default:
                break;
            }

        }

        SDL_RenderPresent(renderer);
    }

    return 1;
}



