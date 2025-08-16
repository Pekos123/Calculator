#include <gtest/gtest.h>
#include <memory>
#include "../include/Frame.h"
#include "../include/Button.h"

#define BLACK {0, 0, 0, 255}
#define GRAY {20, 20, 20, 255}
#define WHITE {255, 255, 255, 255}
#define RED {255, 0, 0, 255}

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 960

SDL_FRect CenterRect(SDL_FRect rect)
{
    return {rect.x - rect.w / 2, rect.y - rect.h / 2, rect.w, rect.h};
}

TEST(Frame, Does_Frame_Changes_Button_Rect)
{
    TTF_Init();

    SDL_Renderer* renderer = nullptr; 

    const uint8_t buttonSize = 150;
    const SDL_FRect rect = { 0, 0, buttonSize, buttonSize};
    Button button(
        renderer,
        WHITE,
        rect,
        nullptr
    );
    
    Frame frame({0, 0, 1000, 1000});
    frame.AddElement(&button);
    frame.AlignElements();
    
    EXPECT_NE(button.GetRect().x, rect.x);
    EXPECT_NE(button.GetRect().y, rect.y);
}

