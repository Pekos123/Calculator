#include "../include/Button.h"

Button::Button(SDL_Renderer* renderer, const SDL_FRect& rect, const SDL_Color& color)
{
    this->rect = {rect.x - rect.w / 2, rect.y - rect.h / 2, rect.w, rect.h};
    this->color = color;
}

void Button::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_FRect Button::GetRect()
{
    return rect;
}
SDL_Color Button::GetColor()
{
    return color;
}
