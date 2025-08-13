#ifndef TEXT_H
#define TEXT_H
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include "../include/GUIElement.h"

class Text : public GUIElement
{
private:
    SDL_Color color;
    TTF_Font* font = nullptr;
    SDL_Texture* texture = nullptr;
    const char* text = nullptr;
    float textSize = 80.0f;

    void CreateTexture();
public:
    Text(const char* text, TTF_Font* font, const SDL_Color& color, SDL_FRect rect, SDL_Renderer* renderer);

    void Draw() override;
    void SetColor(const SDL_Color& color);

    SDL_Color GetFontColor();
     
};

#endif
