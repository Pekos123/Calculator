#include <gtest/gtest.h>
#include "../include/Button.h"

#define null {0, 0, 0, 0}

bool AreColorsEqual(SDL_Color colorA, SDL_Color colorB)
{
    return colorA.r == colorB.r 
        && colorA.g == colorB.g 
        && colorA.b == colorB.b 
        && colorA.a == colorB.a; 
}
bool AreRectsEqual(SDL_FRect rectA, SDL_FRect rectB)
{
    return rectA.h == rectB.h 
        && rectA.w == rectB.w 
        && rectA.x == rectB.x 
        && rectA.y == rectB.y; 
}

TEST(Button, Isnt_NULL)
{
    // Init 
    SDL_Renderer* renderer = nullptr;
    SDL_FRect rect{20, 20, 20, 20};
    SDL_Color color{255, 255, 255, 255};
    Button button(renderer, rect, color, nullptr, color);  
     
    EXPECT_FALSE(AreRectsEqual(button.GetRect(), null));
    EXPECT_FALSE(AreColorsEqual(button.GetBackgroundColor(), null));
    EXPECT_FALSE(AreColorsEqual(button.GetFontColor(), null));
}

