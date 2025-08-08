#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include <SDL3/SDL.h>

class Button
{
private:
    SDL_FRect rect;
    SDL_Color color;
    // Add Event OnClick and Add Function to check if clicked
public:    
    Button(SDL_Renderer* renderer, const SDL_FRect& rect, const SDL_Color& color);

    void Draw(SDL_Renderer* renderer);

    SDL_FRect GetRect();
    SDL_Color GetColor();
};

#endif
