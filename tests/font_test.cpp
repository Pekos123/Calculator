#include <gtest/gtest.h>
#include <SDL3/SDL_ttf.h>

bool init = TTF_Init();

TEST(Font, IS_INIT_PROPERLY)
{
    EXPECT_TRUE(init);
}
TEST(Font, Is_Font_Loading)
{
    TTF_Font* font = TTF_OpenFont("../font.otf", 24);
    EXPECT_NE(font, nullptr);
}
