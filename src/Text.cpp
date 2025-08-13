#include "../include/Text.h"

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
    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(font, this->text, SDL_strlen(text),this->color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
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

SDL_Color Text::GetFontColor()
{
    return color;
}
