#include "BaseFunc.h"
#include "BaseObject.h"
#include "Character.h"
#include "Ball.h"
#include <iomanip>

BaseObject g_background;
SDL_Color textColor = { 255, 255, 255 };  // White color

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Mini Football",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
        return false;
    }
    else {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) {
            success = false;
        }
        else {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!IMG_Init(imgFlags) && imgFlags) {
                success = false;
            }
        }
    }

    if (TTF_Init() == -1) {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        return -1;
    }

    return success;
}

void Close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (InitData() == false)
        return -1;

    if (g_background.SetBackground(g_screen) == false)
    {
        return -1;
    }

    // Load the font
    TTF_Font* font = TTF_OpenFont("res/abc.ttf", 16);  // 24 is the font size
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return -1;
    }

    CharacterObject p_character_0(&g_background, 70, 177, 0);
    CharacterObject p_character_1(&g_background, 172, 75, 1);
    CharacterObject p_character_2(&g_background, 275, 177, 2);
    CharacterObject p_character_3(&g_background, 70, 435, 3);
    CharacterObject p_character_4(&g_background, 172, 539, 4);
    CharacterObject p_character_5(&g_background, 275, 435, 5);

    BallObject ball(168.5, 304);

    /*for (int i = 0; i < 6; i++)
    {
        double posX = g_background.GetPosX(i);
        double posY = g_background.GetPosY(i);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << posX << " " << posY << std::endl;
    }*/

    p_character_0.LoadImg("res/characters/loren/front.png", g_screen, &g_background);
    p_character_1.LoadImg("res/characters/loren/front.png", g_screen, &g_background);
    p_character_2.LoadImg("res/characters/loren/front.png", g_screen, &g_background);
    p_character_3.LoadImg("res/characters/argen/back.png", g_screen, &g_background);
    p_character_4.LoadImg("res/characters/argen/back.png", g_screen, &g_background);
    p_character_5.LoadImg("res/characters/argen/back.png", g_screen, &g_background);

    ball.LoadImg("res/ball.png", g_screen);

    /*for (int i = 0; i < 6; i++)
    {
        int width = g_background.GetWidth(i);
        std::cout << width << std::endl;
    }*/

    bool is_quit = false;
    int red_control = 0;
    int blue_control = 3;

    int red_score = 0;
    int blue_score = 0;

    SDL_Surface* redSurface = TTF_RenderText_Solid(font, std::to_string(red_score).c_str(), textColor);
    if (!redSurface) {
        std::cerr << "Unable to render text surface: " << TTF_GetError() << std::endl;
    }
    SDL_Surface* blueSurface = TTF_RenderText_Solid(font, std::to_string(blue_score).c_str(), textColor);
    if (!blueSurface) {
        std::cerr << "Unable to render text surface: " << TTF_GetError() << std::endl;
    }

    // Create texture from the surface
    SDL_Texture* redTexture = SDL_CreateTextureFromSurface(g_screen, redSurface);
    if (!redTexture) {
        std::cerr << "Unable to create texture from rendered text: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* blueTexture = SDL_CreateTextureFromSurface(g_screen, blueSurface);
    if (!blueTexture) {
        std::cerr << "Unable to create texture from rendered text: " << SDL_GetError() << std::endl;
    }

    // Get the width and height of the text
    int redScoreWidth = 0;
    int redScoreHeight = 0;
    SDL_QueryTexture(redTexture, NULL, NULL, &redScoreWidth, &redScoreHeight);
    int blueScoreWidth = 0;
    int blueScoreHeight = 0;
    SDL_QueryTexture(blueTexture, NULL, NULL, &blueScoreWidth, &blueScoreHeight);

    // Define the destination rectangle for the text on the screen
    SDL_Rect redQuad = { 276, 12, redScoreWidth, redScoreHeight };
    SDL_Rect blueQuad = { 308, 12, blueScoreWidth, blueScoreHeight };

    while (!is_quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            g_background.HandleUserInput(g_event, g_screen);

            if (g_background.GetMode() == INIT)
            {
                ball.Reset();

                p_character_0.Reset(70, 177, 0);
                p_character_1.Reset(172, 75, 1);
                p_character_2.Reset(275, 177, 2);
                p_character_3.Reset(70, 435, 3);
                p_character_4.Reset(172, 539, 4);
                p_character_5.Reset(275, 435, 5);

                p_character_0.LoadImg("res/characters/loren/front.png", g_screen, &g_background);
                p_character_1.LoadImg("res/characters/loren/front.png", g_screen, &g_background);
                p_character_2.LoadImg("res/characters/loren/front.png", g_screen, &g_background);
                p_character_3.LoadImg("res/characters/argen/back.png", g_screen, &g_background);
                p_character_4.LoadImg("res/characters/argen/back.png", g_screen, &g_background);
                p_character_5.LoadImg("res/characters/argen/back.png", g_screen, &g_background);

                red_control = 0;
                blue_control = 3;

                red_score = 0;
                blue_score = 0;
            }

            if (g_background.GetMode() == PVP || g_background.GetMode() == PVC)
            {
                // handle changing player
                if (g_event.type == SDL_KEYDOWN)
                {
                    switch (g_event.key.keysym.sym)
                    {
                    case SDLK_j:
                        blue_control = 3;
                        break;

                    case SDLK_k:
                        blue_control = 4;
                        break;

                    case SDLK_l:
                        blue_control = 5;
                        break;

                    case SDLK_1:
                        red_control = 0;
                        break;

                    case SDLK_2:
                        red_control = 1;
                        break;

                    case SDLK_3:
                        red_control = 2;
                        break;

                    default:
                        break;
                    }
                }

                // player control
                switch (red_control)
                {
                case 0:
                    p_character_0.HandleInputAction(g_event, g_screen);
                    break;

                case 1:
                    p_character_1.HandleInputAction(g_event, g_screen);
                    break;

                case 2:
                    p_character_2.HandleInputAction(g_event, g_screen);
                    break;

                default:
                    break;
                }

                switch (blue_control)
                {
                case 3:
                    p_character_3.HandleInputAction(g_event, g_screen);
                    break;

                case 4:
                    p_character_4.HandleInputAction(g_event, g_screen);
                    break;

                case 5:
                    p_character_5.HandleInputAction(g_event, g_screen);
                    break;

                default:
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        if (g_background.GetMode() == PVP || g_background.GetMode() == PVC)
        {
            ball.Move();
            ball.GoalCheck();

            if (ball.CheckRedGoal())
            {
                // handle red goal
                red_score += 1;
                redSurface = TTF_RenderText_Solid(font, std::to_string(red_score).c_str(), textColor);
                redTexture = SDL_CreateTextureFromSurface(g_screen, redSurface);
                ball.SetRedGoal();
            }

            if (ball.CheckBlueGoal())
            {
                // handle blue goal
                blue_score += 1;
                blueSurface = TTF_RenderText_Solid(font, std::to_string(blue_score).c_str(), textColor);
                blueTexture = SDL_CreateTextureFromSurface(g_screen, blueSurface);
                ball.SetBlueGoal();
            }

            p_character_0.DoCharacter(&g_background, ball);
            p_character_1.DoCharacter(&g_background, ball);
            p_character_2.DoCharacter(&g_background, ball);
            p_character_3.DoCharacter(&g_background, ball);
            p_character_4.DoCharacter(&g_background, ball);
            p_character_5.DoCharacter(&g_background, ball);

            SDL_RenderCopy(g_screen, redTexture, NULL, &redQuad);
            SDL_RenderCopy(g_screen, blueTexture, NULL, &blueQuad);

            p_character_0.Show(g_screen, &g_background);
            p_character_1.Show(g_screen, &g_background);
            p_character_2.Show(g_screen, &g_background);
            p_character_3.Show(g_screen, &g_background);
            p_character_4.Show(g_screen, &g_background);
            p_character_5.Show(g_screen, &g_background);

            ball.Show(g_screen);
        }

        SDL_RenderPresent(g_screen);
    }

    // Free the surface as it's no longer needed
    SDL_FreeSurface(redSurface);
    SDL_FreeSurface(blueSurface);
    SDL_DestroyTexture(redTexture);
    SDL_DestroyTexture(blueTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    Close();

	return 0;
}