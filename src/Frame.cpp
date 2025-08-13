#include "../include/Frame.h"
#include <iostream>

Frame::Frame(const SDL_FRect& bounds, const float padding)
{
    this->bounds = bounds;
    this->padding = padding;
}

void Frame::AddElement(GUIElement* element)
{
    elements.push_back(element);
}
void Frame::CalculatePositions()
{
    switch(elementsAligment)
    {
        case Aligment::Center:
            AlignCenter(); 
            break;
        case Aligment::Horizontal:
            AlignHorizontal(); 
            break;
        case Aligment::Vertical:
            AlignVertical();
            break;
    }
}
void Frame::AlignCenter() // This deasnt work, fix it
{
    for(GUIElement* element : elements) 
    {
        for(int i = 0; i < elements.size(); ++i)
        {
            GUIElement* element = elements[i];
        
            float x = element->GetRect().w * i + padding * (i + 1);
            float y = element->GetRect().h * i + padding * (i + 1);        
            element->SetPosition(x, y);
        }    
    }
}
void Frame::AlignVertical()
{
    for(int i = 0; i < elements.size(); ++i)
    {
        GUIElement* element = elements[i];
        
        float x = bounds.x + (bounds.w - element->GetRect().w) / 2;
        float y = element->GetRect().h * i + padding * (i + 1);
        
        element->SetPosition(x, y);
    }
}
void Frame::AlignHorizontal()
{
    for(int i = 0; i < elements.size(); ++i)
    {
        GUIElement* element = elements[i];
        
        float x = element->GetRect().w * i + padding * (i + 1);
        float y = bounds.y + (bounds.h - element->GetRect().h) / 2;
        
        element->SetPosition(x, y);
    }
}
void Frame::AlignElements()
{
    CalculatePositions();
}
