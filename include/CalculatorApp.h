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
    constexpr SDL_Color RED = {255, 0, 0, 255};
}

struct ButtonConfig
{
    SDL_Color fontColor;
    SDL_Color buttonColor;
    const char* text;
};

class CalculatorApp
{
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font* font;

    std::vector<std::unique_ptr<GUIElement>> guiElements;
    std::vector<std::unique_ptr<Button>> buttons;
    
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
};
#endif
