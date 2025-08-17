#include "../include/Button.h"

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

    this->hoverTexture = CreateColorTexture(hoverColor);
    this->clickedTexture = CreateColorTexture(clickedColor); 

    CalculatePositions();
}
void Button::CalculatePositions()
{
    text->SetPosition(rect.x + ((rect.w - text->GetRect().w) / 2), rect.y);
}
void Button::SetPosition(float x, float y)
{
    GUIElement::SetPosition(x, y);
    CalculatePositions();
}
SDL_Texture* Button::CreateColorTexture(SDL_Color color) {
    // Create a temporary surface
    SDL_Surface* surface = SDL_CreateSurface(rect.w, rect.h, SDL_PIXELFORMAT_RGBA8888);
    SDL_PixelFormat format = surface->format;

    SDL_FillSurfaceRect(surface, NULL, SDL_MapRGBA(SDL_GetPixelFormatDetails(format), nullptr, color.r, color.g, color.b, color.a));
    
    // Convert to texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    
    return texture;
}

void Button::Draw()
{ 
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &rect); // doeasnt render well idk why
    // same with text its having not that color

    text->Draw(); // Segmentantion fault core dumped
    
    switch (currentState) {
        case Hovering:
            DrawHover(hoverTexture);
            break;
        case Clicked:
            DrawHover(clickedTexture);
            break;
        default:
            break;
    } 
}

void Button::DrawHover(SDL_Texture* texture)
{
    SDL_RenderTexture(renderer, texture, NULL, &rect);
}
bool Button::IsMouseHoveringButton(const SDL_Event* ev)
{
    return (ev->button.x >= GUIElement::GetRect().x &&
                ev->button.x <= (GUIElement::GetRect().x + GUIElement::GetRect().w) &&
                ev->button.y >= GUIElement::GetRect().y &&
                ev->button.y <= (GUIElement::GetRect().y + GUIElement::GetRect().h));
}
bool Button::IsButtonPressed(const SDL_Event* ev)
{
     if(ev->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT && IsMouseHoveringButton(ev)) {
            event.Invoke();
            return true;
        }
    }
    return false;
}
void Button::ButtonStateHandler(const SDL_Event* ev)
{
    if(IsMouseHoveringButton(ev))
    {
        currentState = ButtonState::Hovering;
        if(IsButtonPressed(ev))
        {
            currentState = ButtonState::Clicked;
            return;
        }
        return;
    }
    currentState = ButtonState::Default;
}
void Button::EventHandler(const SDL_Event* ev)
{
    ButtonStateHandler(ev);
}

SDL_Color Button::GetBackgroundColor()
{
    return backgroundColor;
}
