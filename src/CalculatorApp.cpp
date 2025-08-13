#include "../include/CalculatorApp.h"

CalculatorApp::CalculatorApp()
{
    if(Init())
        SDL_Quit();
}
CalculatorApp::~CalculatorApp()
{
    Cleanup();
}

bool CalculatorApp::Init()
{
    return InitSDL() && CreateWindow() && CreateRenderer() && LoadFont();
}

bool CalculatorApp::InitSDL()
{
    if(!TTF_Init())
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool CalculatorApp::CreateWindow()
{
    this->window = SDL_CreateWindow(Config::WINDOW_TITLE, 
                                          Config::WINDOW_WIDTH, 
                                          Config::WINDOW_HEIGHT, 
                                          Config::FLAGS);
    if(!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}
bool CalculatorApp::CreateRenderer()
{
    this->renderer = SDL_CreateRenderer(this->window, nullptr);
    if(!this->renderer)
    {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }
    return true;
}
bool CalculatorApp::LoadFont()
{
    this->font = TTF_OpenFont(Config::FONT_PATH, Config::FONT_SIZE);
    
    if(!this->font)
    {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        return false;
    }
    return true;
}

void CalculatorApp::Render()
{
    ClearScreen();
    DrawGUI();
    SDL_RenderPresent(this->renderer);
}
void CalculatorApp::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
void CalculatorApp::DrawGUI()
{
    for(const auto& element : guiElements)
        element->Draw();
}

void CalculatorApp::ButtonsSetup()
{
    // Setup buttons and add them to gui elements
    const SDL_FRect buttonRect = {0, 0, Config::BUTTON_SIZE, Config::BUTTON_SIZE};
}
void CalculatorApp::FramesSetup()
{
    // Setup 2 frames one for button and one for output text
    
}

void CalculatorApp::Cleanup()
{
    guiElements.clear();
        
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    
    TTF_Quit();
    SDL_Quit();
}
