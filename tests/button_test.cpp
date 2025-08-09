#include <gtest/gtest.h>
#include "../include/Button.h"

bool AreColorsEqual(SDL_Color colorA, SDL_Color colorB)
{
    return colorA.r == colorB.r && colorA.g == colorB.g && colorA.b == colorB.b && colorA.a == colorB.a; 
}
bool AreRectsEqual(SDL_FRect rectA, SDL_FRect rectB)
{
    return rectA.h == rectB.h && rectA.w == rectB.w && rectA.x == rectB.x && rectA.y == rectB.y; 
}

TEST(Button, Isnt_NULL)
{
    SDL_Renderer* renderer = nullptr;

    SDL_FRect rect{20, 20, 20, 20};
    SDL_Color color{255, 255, 255, 255};
    Button button(renderer, rect, color);  
    EXPECT_FALSE(AreRectsEqual(button.GetRect(), {0, 0, 0, 0}));
    EXPECT_FALSE(AreColorsEqual(button.GetColor(), {0, 0, 0, 0}));
}

