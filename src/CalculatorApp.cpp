#include <sstream>
#include <iomanip>

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
}

std::vector<ButtonConfig> CalculatorApp::ButtonConfigsSetup()
{
    return 
    {
        {"C",  Colors::LIGHT_GRAY, Colors::BLACK, [this]() { ClearEquation(); }},
        {"±",  Colors::LIGHT_GRAY, Colors::BLACK, [this]() { AddOperation(' '); } },
        {"%",  Colors::LIGHT_GRAY, Colors::BLACK, [this]() { AddOperation('%'); }},
        {"÷",  Colors::ORANGE,     Colors::WHITE, [this]() { AddOperation(':'); }},
        
        // Row 1 - Numbers 7,8,9 and multiply
        {"7",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('7'); }},
        {"8",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('8'); }},
        {"9",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('9'); }},
        {"×",  Colors::ORANGE,     Colors::WHITE, [this]() { AddOperation('x'); }},
        
        // Row 2 - Numbers 4,5,6 and subtract
        {"4",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('4'); }},
        {"5",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('5'); }},
        {"6",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('6'); }},
        {"-",  Colors::ORANGE,     Colors::WHITE, [this]() { AddOperation('-'); }},
        
        // Row 3 - Numbers 1,2,3 and add
        {"1",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('1'); }},
        {"2",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('2'); }},
        {"3",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddNumberToEquation('3'); }},
        {"+",  Colors::ORANGE,     Colors::WHITE, [this]() { AddOperation('+'); }},
        
        // Row 4 - 0, decimal, equals
        {"0",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddOperation('0'); }}, // This could be double-width
        {".",  Colors::DARK_GRAY,  Colors::WHITE, [this]() { AddOperation('.'); }},
        {"=",  Colors::ORANGE,     Colors::WHITE, [this]() { SumUpEquation(); }}
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
        guiElements.push_back(button);
        buttons.push_back(button);
    }

    Button* button = CreateButton(configs[configs.size()-1]);
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
        }
        for(Button* button : buttons)
            button->EventHandler(&event);
        // ALL ADD IsButtonPressed IN This
        // AND DO FUNCTION FOR CHECKING CHAR (TEXT)
        // SWITCH WITH CASES FOR MATHF SYMBOLS AND DEAFAULT FOR NUMS
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

std::string FloatToString(float f)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(Config::MAX_PRECISION); // Max precision
    oss << f;
    
    std::string s = oss.str();
    
    // Remove trailing zeros and possibly the decimal point
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (s.back() == '.') {
        s.pop_back();
    }
    
    return s;
}
void CalculatorApp::SumUpEquation()
{
    if(firstNum.empty() || secNum.empty())
    {
        equationString = "Error: invalid nums";
        return;
    }

    float first = std::stoi(this->firstNum);
    float sec = std::stoi(this->secNum);
    float eq = 0.0f;

    // core dumped stoi invalid argument
    switch(operation)
    {
        case ':':
            eq = first / sec;
            break;
        case 'x':
            eq = first * sec;
            break;
        case '+':
            eq = first + sec;
            break;
        case '-':
            eq = first - sec;
            break;

        default:
            ClearEquation();
            equationString = "Error: Wrong Operation";
            equationText->SetText(equationString.c_str());
            return; 
    }
    
    ClearEquation();

    equationString = FloatToString(eq);
    secNum = equationString;
    equationText->SetText(equationString.c_str());
}
void CalculatorApp::ClearEquation()
{
    equationString = "";
    operation = NULL;
    firstNum = "";
    secNum = "";

    equationText->SetText(equationString.c_str());
}
void CalculatorApp::AddOperation(const char operation)
{
    if(secNum != "") // pomysl nad tym
    {
        SumUpEquation();
        firstNum = secNum;
        secNum = "";
    }

    this->operation = operation;
    equationString += operation;
    
    equationText->SetText(equationString.c_str());
}
void CalculatorApp::AddNumberToEquation(const char num)
{
    if(firstNum != "")
        ClearEquation();
    if(operation == NULL)
        firstNum += num;
    else
        secNum += num;

    equationString += num;

    equationText->SetText(equationString.c_str());
}
