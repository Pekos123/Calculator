#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

class Button
{
private:
    // Bakcground
    SDL_FRect rect;
    SDL_Color backgroundColor;
    
    //Font
    SDL_Color fontColor;
    SDL_Texture* texture;
    SDL_FRect textRect;
    float textSize;
    char* text = nullptr;
        

public:    
    Button(SDL_Renderer* renderer, 
           const SDL_FRect& rect, 
           const SDL_Color& backgroundColor, 
           TTF_Font* font, 
           const SDL_Color& fontColor, 
           char* text = nullptr,
           float textSize = 26);

    void Draw(SDL_Renderer* renderer);
    bool IsButtonPressed(const SDL_Event* ev);

    SDL_FRect GetRect();
    SDL_Color GetBackgroundColor();
    SDL_Color GetFontColor();
};

#endif
