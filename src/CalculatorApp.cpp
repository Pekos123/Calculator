#include "../include/CalculatorApp.h"


CalculatorApp::CalculatorApp()
{
    if(!Init())
        SDL_Quit();

    ButtonsSetup();
    FramesSetup();
    OutputTextSetup();
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

    button->event.AddListener(config.func);

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
void CalculatorApp::DrawTextBackground()
{
    SDL_FRect backgroundRect = {0, 0, Config::WINDOW_WIDTH, Config::TEXT_FIELD_SIZE};
    SDL_SetRenderDrawColor(this->renderer, Colors::LIGHT_GRAY.r, Colors::LIGHT_GRAY.g, Colors::LIGHT_GRAY.b, Colors::LIGHT_GRAY.a);
    SDL_RenderFillRect(this->renderer, &backgroundRect);
}
void CalculatorApp::DrawGUI()
{
    DrawTextBackground();
    for(const auto& element : guiElements)
        element->Draw();
}

void CalculatorApp::OutputTextSetup()
{
    SDL_FRect bounds = {0, 0, Config::WINDOW_WIDTH, Config::TEXT_FIELD_SIZE};

    equationText = std::make_unique<Text>(equationString.c_str(), this->font, Colors::BLACK, bounds, this->renderer);
    guiElements.push_back(equationText.get());
    RefreshText();
}

std::vector<ButtonConfig> CalculatorApp::ButtonConfigsSetup()
{
    return 
    {
        {"C",  Colors::LIGHT_GRAY, Colors::BLACK, [this]() { calEngine.ClearEquation(); }},
        {"±",  Colors::LIGHT_GRAY, Colors::BLACK, [this]() { calEngine.ChangeNumberSign(); } },
        {"%",  Colors::LIGHT_GRAY, Colors::BLACK, [this]() { calEngine.SetOperation('%'); }},
        {"÷",  Colors::ORANGE,     Colors::WHITE, [this]() { calEngine.SetOperation(':'); }},
        
        // Row 1 - Numbers 7,8,9 and multiply
        {"7",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('7'); }},
        {"8",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('8'); }},
        {"9",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('9'); }},
        {"×",  Colors::ORANGE,     Colors::WHITE, [this]() { calEngine.SetOperation('x'); }},
        
        // Row 2 - Numbers 4,5,6 and subtract
        {"4",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('4'); }},
        {"5",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('5'); }},
        {"6",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('6'); }},
        {"-",  Colors::ORANGE,     Colors::WHITE, [this]() { calEngine.SetOperation('-'); }},
        
        // Row 3 - Numbers 1,2,3 and add
        {"1",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('1'); }},
        {"2",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('2'); }},
        {"3",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('3'); }},
        {"+",  Colors::ORANGE,     Colors::WHITE, [this]() { calEngine.SetOperation('+'); }},
        
        // Row 4 - 0, decimal, equals
        {"0",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterNumber('0'); }}, // This could be double-width
        {".",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { calEngine.EnterDecimalPoint(); }},
        {"=",  Colors::ORANGE,     Colors::WHITE, [this]() { calEngine.SumUpEquation(); }}
    };
}
void CalculatorApp::ButtonsSetup()
{
    std::vector<ButtonConfig> configs = ButtonConfigsSetup();

    guiElements.reserve(configs.size());

    for(int i = 0; i < configs.size()-1; i++)
    {
        ButtonConfig config = configs[i];

        Button* button = CreateButton(config);
        button->event.AddListener([this]() {RefreshText();});
        guiElements.push_back(button);
        buttons.push_back(button);
    }
    // Createing equal(=) button
    Button* button = CreateButton(configs[configs.size()-1]);
    button->event.AddListener([this]() {RefreshText();});
    button->SetSize(Config::BUTTON_SIZE*2, button->GetRect().h);
    guiElements.push_back(button);
    buttons.push_back(button);

}
void CalculatorApp::FramesSetup()
{
    // Setup 2 frames one for button and one for output text
    SDL_FRect bounds = {0, Config::TEXT_FIELD_SIZE, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT-Config::TEXT_FIELD_SIZE};
    Frame buttonFrame(bounds);

    for(auto button : buttons)
        buttonFrame.AddElement(button);
    
    buttonFrame.elementsAligment = Aligment::Grid;
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
            case SDL_EVENT_KEY_DOWN:
                if(event.key.key == SDLK_ESCAPE)
                    running = false;
                break;
        }
        for(Button* button : buttons)
            button->EventHandler(&event); 
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
