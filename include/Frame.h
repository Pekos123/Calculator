#ifndef FRAME_H
#define FRAME_H
#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "../include/GUIElement.h"

enum Aligment
{
    Horizontal,
    Vertical,
    Center
};

class GUIElement;
class Frame
{
private:
    std::vector<GUIElement*> elements;
    SDL_FRect bounds;
    float padding; 
    
    void CalculatePositions();
    void AlignCenter();
    void AlignHorizontal();
    void AlignVertical();
public:
    Frame(const SDL_FRect& bounds, const float padding = 0.0f);
    
    Aligment elementsAligment = Aligment::Center;

    void AddElement(GUIElement* element);
    void AlignElements();
};

#endif
