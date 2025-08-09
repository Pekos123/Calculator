#include <SDL3/SDL.h>
#include "../include/Button.h"
#include <iostream>

#define BLACK {0, 0, 0, 255}
#define GRAY {20, 20, 20, 255}
#define WHITE {255, 255, 255, 255}
#define RED {255, 0, 0, 255}

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 960

int main(int argc, char* argv[]) {
    
    TTF_Init();
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
   
    TTF_Font* font = TTF_OpenFont("font.otf", 256);
    if (!font) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL3 Calculator", // title
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0                  // flags (use 0 for default)
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool running = true;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr); 
    Button button(renderer,
                  {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 150, 150},
                  WHITE, 
                  font, GRAY, "Test", 50);

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if(button.IsButtonPressed(&event))
                std::cout << "Button Pressed\n";
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        button.Draw(renderer);
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // To not overload CPU
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
