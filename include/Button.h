#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

class Button
{
private:
    SDL_FRect rect;
    SDL_Color color;
    // Add Event OnClick and Add Function to check if clicked
public:    
    Button(SDL_Renderer* renderer, const SDL_FRect& rect, const SDL_Color& color);

    void Draw(SDL_Renderer* renderer);
    bool IsButtonPressed(const SDL_Event* ev);

    SDL_FRect GetRect();
    SDL_Color GetColor();
};

#endif
