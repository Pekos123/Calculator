#include "../include/Text.h"
#include <iostream>

Text::Text(const char* text,
           TTF_Font* font,
           const SDL_Color& color,
           SDL_FRect rect,
           SDL_Renderer* renderer)
{
    this->text = text;
    this->font = font;
    this->color = color;
    this->rect = rect;
    this->renderer = renderer;

    CreateTexture();
}

void Text::CreateTexture()
{
    if(!font)
    {
        SDL_LogError(1, "ERROR: Null font");
        return;
    }

    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(font, this->text, SDL_strlen(text),this->color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    if(SDL_strlen(text) > 0)
    {
        float width = surface->w / 2;
        //if(width > Config::WINDOW_WIDTH) // find good condition
        //    width = surface->w / (surface->w);
        //else 
            rect.w = width;
    }
    SDL_DestroySurface(surface);
    SDL_GetTextureSize(texture, NULL, NULL);
}
void Text::Draw()
{
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}
void Text::SetColor(const SDL_Color& color)
{
    this->color = color;
    CreateTexture();
}
void Text::SetText(const char* text)
{
    this->text = text;
    CreateTexture();
}

SDL_Color Text::GetFontColor()
{
    return color;
}
