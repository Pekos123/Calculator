#include "../include/CalculatorApp.h"

CalculatorApp::CalculatorApp()
{
    if(!Init())
        SDL_Quit();

    ButtonsSetup();
    FramesSetup();
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
    this->window = SDL_CreateWindow(
        Config::WINDOW_TITLE, 
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

Button* CalculatorApp::CreateButton(const ButtonConfig& config)
{
    
    const SDL_FRect buttonRect = {0, 0, Config::BUTTON_SIZE, Config::BUTTON_SIZE};
    auto text = std::make_shared<Text>(config.text, this->font, config.fontColor, buttonRect, this->renderer);

    Button* button = new Button(
        this->renderer,
        config.buttonColor,
        buttonRect,
        std::move(text)
    );
    return button;
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
std::vector<ButtonConfig> CalculatorApp::ButtonConfigsSetup()
{
    return 
    {
        {"C",  Colors::LIGHT_GRAY, Colors::BLACK},
        {"±",  Colors::LIGHT_GRAY, Colors::BLACK},
        {"%",  Colors::LIGHT_GRAY, Colors::BLACK},
        {"÷",  Colors::ORANGE,     Colors::WHITE},
        
        // Row 1 - Numbers 7,8,9 and multiply
        {"7",  Colors::DARK_GRAY,  Colors::WHITE},
        {"8",  Colors::DARK_GRAY,  Colors::WHITE},
        {"9",  Colors::DARK_GRAY,  Colors::WHITE},
        {"×",  Colors::ORANGE,     Colors::WHITE},
        
        // Row 2 - Numbers 4,5,6 and subtract
        {"4",  Colors::DARK_GRAY,  Colors::WHITE},
        {"5",  Colors::DARK_GRAY,  Colors::WHITE},
        {"6",  Colors::DARK_GRAY,  Colors::WHITE},
        {"-",  Colors::ORANGE,     Colors::WHITE},
        
        // Row 3 - Numbers 1,2,3 and add
        {"1",  Colors::DARK_GRAY,  Colors::WHITE},
        {"2",  Colors::DARK_GRAY,  Colors::WHITE},
        {"3",  Colors::DARK_GRAY,  Colors::WHITE},
        {"+",  Colors::ORANGE,     Colors::WHITE},
        
        // Row 4 - 0, decimal, equals
        {"0",  Colors::DARK_GRAY,  Colors::WHITE}, // This could be double-width
        {".",  Colors::DARK_GRAY,  Colors::WHITE},
        {"=",  Colors::ORANGE,     Colors::WHITE}
    };
}
void CalculatorApp::ButtonsSetup()
{
    std::vector<ButtonConfig> configs = ButtonConfigsSetup();

    guiElements.reserve(configs.size());

    for(ButtonConfig config : configs)
    {
        Button* button = CreateButton(config);
        guiElements.push_back(button);
        buttons.push_back(button);
    }
}
void CalculatorApp::FramesSetup()
{
    // Setup 2 frames one for button and one for output text
    SDL_FRect bounds = {0, 150, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT-150};
    Frame buttonFrame(bounds);
    for(auto button : buttons)
        buttonFrame.AddElement(button);
    buttonFrame.elementsAligment = Aligment::Horizontal; // Bad aligment
    buttonFrame.AlignElements();
}

void CalculatorApp::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;        
        }
    }
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
