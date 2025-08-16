#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <memory>

#include "../include/GUIElement.h"
#include "../include/Text.h"
#include "../include/Event.h"

class Button : public GUIElement
{
private:
    bool hover = false;

    SDL_Color backgroundColor;
    SDL_Color hoverColor = {255, 255, 255, 80};
    SDL_Texture* hoverTexture;

    SDL_Texture* CreateColorTexture(SDL_Color color);
    void DrawHover();
public:
    Button(SDL_Renderer* renderer, 
           const SDL_Color& backgroundColor,
           const SDL_FRect& rect,
           std::shared_ptr<Text> text);

    std::shared_ptr<Text> text = nullptr; 
    Event event;

    void Draw() override;
    bool IsButtonPressed(const SDL_Event* ev);
 
    SDL_Color GetBackgroundColor();
};

#endif
