#include <SDL3/SDL.h>
#include <iostream>

int main() {
    if (SDL_Init(0) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "SDL initialized!" << std::endl;
    SDL_Quit();
    return 0;
}
