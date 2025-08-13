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
    std::shared_ptr<Text> text = std::make_shared<Text>("test", nullptr, color, rect, renderer);
    Button button(renderer, color, rect, text);  

    SDL_Color nullColor = null;
    EXPECT_FALSE(AreRectsEqual(button.GetRect(), null));
    EXPECT_FALSE(AreColorsEqual(button.GetBackgroundColor(), nullColor));
    EXPECT_FALSE(AreColorsEqual(button.text->GetFontColor(), nullColor));
}

