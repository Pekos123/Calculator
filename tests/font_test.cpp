#include <gtest/gtest.h>
#include <SDL3/SDL_ttf.h>

TEST(SDL_TTF, IS_INIT_PROPERLY)
{
    EXPECT_TRUE(TTF_Init());
}
TEST(Font, Is_Font_Loading)
{
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("font.otf", 24);
    EXPECT_NE(font, nullptr);
}
