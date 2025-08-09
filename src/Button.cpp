#include "../include/Button.h"

Button::Button(SDL_Renderer* renderer, 
               const SDL_FRect& rect, 
               const SDL_Color& backgroundColor, 
               TTF_Font* font, 
               const SDL_Color& fontColor, 
               char* text,
               float textSize)
{
    this->rect = {rect.x - rect.w / 2, rect.y - rect.h / 2, rect.w, rect.h}; // centering button
    this->backgroundColor = backgroundColor;
    this->fontColor = fontColor;
    this->text = text;
    this->textRect = {rect.x - textSize / 2, rect.y - textSize / 2, textSize, textSize}; // centering ext

    SDL_Surface* surface;
    // faster but bad quality
    //surface = TTF_RenderText_Solid(font, this->text, SDL_strlen(text),this->fontColor);
    // best quality
    surface = TTF_RenderText_Blended(font, this->text, SDL_strlen(text),this->fontColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_GetTextureSize(texture, nullptr, nullptr); // looks like texture dont have size or doesnt render
}

void Button::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderTexture(renderer, texture, nullptr, &textRect);
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
SDL_Color Button::GetBackgroundColor()
{
    return backgroundColor;
}
SDL_Color Button::GetFontColor()
{
    return fontColor;
}
