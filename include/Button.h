#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include "../include/GUIElement.h"
#include "../include/Text.h"

class Button : public GUIElement
{
private:
    // Bakcground
    SDL_Color backgroundColor;
public:
    Button(SDL_Renderer* renderer, 
           const SDL_Color& backgroundColor,
           const SDL_FRect& rect,
           Text* text);

    Text* text = nullptr;
    
    void Draw() override;
    bool IsButtonPressed(const SDL_Event* ev);
 
    SDL_Color GetBackgroundColor();
};

#endif
