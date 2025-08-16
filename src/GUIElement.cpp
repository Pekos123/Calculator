#include "../include/GUIElement.h"

void GUIElement::SetPosition(float x, float y)
{
    rect.x = x;
    rect.y = y;
}
void GUIElement::SetSize(float w, float h)
{
    rect.w = w;
    rect.h = h;
}
SDL_FRect GUIElement::GetRect()
{
    return rect;
}
