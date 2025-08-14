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
        case Aligment::Grid:
            AlignGrid(); 
            break;
        case Aligment::Horizontal:
            AlignHorizontal(); 
            break;
        case Aligment::Vertical:
            AlignVertical();
            break;
    }
}
void Frame::AlignGrid() 
{
    float width = 0;
    int rows = 1;
    int col = 0;

    for(GUIElement* element : elements)
    {
        if(width + element->GetRect().w > bounds.w)
        {
            rows++;
            col = 0;
            width = 0;
        }

        float x = width + padding * (col + 1);
        float y = bounds.y + element->GetRect().h * (rows-1);

        width += element->GetRect().w;
        col++;

        element->SetPosition(x, y);
    }
}
void Frame::AlignVertical()
{
    for(int i = 0; i < elements.size(); ++i)
    {
        GUIElement* element = elements[i];
        
        float x = bounds.x + (bounds.w - element->GetRect().w) / 2;
        float y = element->GetRect().h * (i+1) + padding * (i + 1);
        
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
