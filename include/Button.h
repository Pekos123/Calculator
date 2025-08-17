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
    enum ButtonState
    {
        Default,
        Hovering,
        Clicked,
        Realsed,
    };

    ButtonState currentState = ButtonState::Default;

    SDL_Color backgroundColor;
    SDL_Color currentBackgroundColor = {0, 0, 0, 0};
    SDL_Color hoverColor = {255, 255, 255, 50};
    SDL_Color clickedColor = {255, 255, 255, 90};
    SDL_Texture* hoverTexture;
    SDL_Texture* clickedTexture;

    SDL_Texture* CreateColorTexture(SDL_Color color);
    bool IsMouseHoveringButton(const SDL_Event* ev);
    bool IsButtonPressed(const SDL_Event* ev);
    void ButtonStateHandler(const SDL_Event* ev);
    void DrawHover(SDL_Texture* texture);
    void CalculatePositions();
public:
    Button(SDL_Renderer* renderer, 
           const SDL_Color& backgroundColor,
           const SDL_FRect& rect,
           std::shared_ptr<Text> text);

    std::shared_ptr<Text> text = nullptr; 
    Event event;

    void Draw() override;
    void SetPosition(float x, float y) override;
    void EventHandler(const SDL_Event* ev);
    
    SDL_Color GetBackgroundColor();
};

#endif
