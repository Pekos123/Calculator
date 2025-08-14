#include "../include/Button.h"
#include <iostream>

Button::Button(SDL_Renderer* renderer, 
               const SDL_Color& backgroundColor,
               const SDL_FRect& rect,
               std::shared_ptr<Text> text)
{
    GUIElement::SetPosition(rect.x, rect.y);
    GUIElement::SetSize(rect.w, rect.h);
    this->renderer = renderer;
    this->backgroundColor = backgroundColor;
    this->text = text;
}

void Button::Draw()
{
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &rect); // doeasnt render well idk why
    // same with text its having not that color

    text->SetPosition(rect.x + ((rect.w - text->GetRect().w) / 2), rect.y);
    text->Draw(); // Segmentantion fault core dumped

    if(hover)
        DrawHover();
}

void Button::DrawHover()
{
    SDL_Surface* surface = SDL_CreateSurface(rect.w, rect.h, SDL_PIXELFORMAT_RGBA8888);
    // u have to do it by texture but will work

    SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
    SDL_RenderFillRect(renderer, &rect);
}

bool Button::IsButtonPressed(const SDL_Event* ev)
{
     if(ev->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
                ev->button.x >= GUIElement::GetRect().x &&
                ev->button.x <= (GUIElement::GetRect().x + GUIElement::GetRect().w) &&
                ev->button.y >= GUIElement::GetRect().y &&
                ev->button.y <= (GUIElement::GetRect().y + GUIElement::GetRect().h)) {
            hover = true;
            return true;
        }
    }
    hover = false;
    return false;
}

SDL_Color Button::GetBackgroundColor()
{
    return backgroundColor;
}
