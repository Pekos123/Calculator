#include "../include/Button.h"

Button::Button(SDL_Renderer* renderer, const SDL_FRect& rect, const SDL_Color& color)
{
    this->rect = {rect.x - rect.w / 2, rect.y - rect.h / 2, rect.w, rect.h}; // centering button
    this->color = color;
}

void Button::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
bool Button::IsButtonPressed(const SDL_Event* ev)
{
     if(ev->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
                ev->button.x >= rect.x &&
                ev->button.x <= (rect.x + rect.w) &&
                ev->button.y >= rect.y &&
                ev->button.y <= (rect.y + rect.h)) {
            return true;
        }
    }
    return false;
}

SDL_FRect Button::GetRect()
{
    return rect;
}
SDL_Color Button::GetColor()
{
    return color;
}
