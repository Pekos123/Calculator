#include <memory>
#include <gtest/gtest.h>

#include "../include/Button.h"
#include "../include/Text.h"

#define null {0, 0, 0, 0}
#define WHITE {255, 255, 255, 255}

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
    SDL_Renderer* renderer = nullptr; 

    const uint8_t buttonSize = 150;
    const SDL_FRect rect = { 0, 0, buttonSize, buttonSize};
    TTF_Font* font = nullptr;

    auto text = std::shared_ptr<Text>(new Text("test", font, WHITE, rect, renderer));
    Button button(
        renderer,
        WHITE,
        rect,
        std::move(text)
    );

    SDL_Color nullColor = {0, 0, 0, 0};
    EXPECT_FALSE(AreRectsEqual(button.GetRect(), null));
    EXPECT_FALSE(AreColorsEqual(button.GetBackgroundColor(), nullColor));
    EXPECT_FALSE(AreColorsEqual(button.text->GetFontColor(), nullColor));
}

