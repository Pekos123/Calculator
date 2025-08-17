#ifndef GUIELEMENT_H
#define GUIELEMENT_H    

#include <SDL3/SDL.h>

class GUIElement
{
protected:
    SDL_FRect rect;
    SDL_Renderer* renderer;
public:
    virtual void Draw() {}

    virtual void SetPosition(float x, float y);
    void SetSize(float w, float h);
    
    SDL_FRect GetRect(); 
};

#endif
