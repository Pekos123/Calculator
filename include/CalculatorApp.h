#ifndef CALCULATORAPP_H
#define CALCULATORAPP_H

#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <vector>

#include "../include/Button.h"
#include "../include/Frame.h"


namespace Config
{
    constexpr SDL_WindowFlags FLAGS = 0;

    constexpr int WINDOW_WIDTH = 640;
    constexpr int WINDOW_HEIGHT = 960;
    constexpr int BUTTON_SIZE = 150;
    constexpr int TARGET_FPS = 60;
    constexpr int FRAME_DELAY = 1000 / TARGET_FPS; // ~16ms
    constexpr int FRAME_SPACING = 50;
    
    constexpr char WINDOW_TITLE[] = "SDL3 Calculator";
    constexpr char FONT_PATH[] = "font.otf";
    constexpr int FONT_SIZE = 256;
}

namespace Colors 
{
    constexpr SDL_Color BLACK = {0, 0, 0, 255};
    constexpr SDL_Color GRAY = {20, 20, 20, 255};
    constexpr SDL_Color WHITE = {255, 255, 255, 255};
    constexpr SDL_Color ORANGE = {255, 149, 0, 255};
    constexpr SDL_Color DARK_GRAY = {51, 51, 51, 255};
    constexpr SDL_Color LIGHT_GRAY = {165, 165, 165, 255};
}

struct ButtonConfig
{
    const char* text;
    SDL_Color fontColor;
    SDL_Color buttonColor; 
};

class CalculatorApp
{
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font* font;

    std::vector<GUIElement*> guiElements; 
    //std::vector<std::unique_ptr<Text>> texts;
    std::vector<Button*> buttons;
    
    bool running = true;
public:
    ~CalculatorApp();
    CalculatorApp();

    void run()
    {
        while(running)
        {
            Render();
            HandleEvents();
            SDL_Delay(Config::FRAME_DELAY);
        }
    }
private:
    bool Init();
    bool InitSDL();
    bool CreateWindow();
    bool CreateRenderer();
    bool LoadFont();
    
    void Render();
    void ClearScreen();
    void DrawGUI();
    void HandleEvents();
    void FramesSetup();
    void ButtonsSetup();
    void Cleanup();

    Button* CreateButton(const ButtonConfig& config);
 
    std::vector<ButtonConfig> ButtonConfigsSetup();
};
#endif
