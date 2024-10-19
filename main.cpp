#include "BaseFunc.h"
#include "BaseObject.h"
#include "Character.h"
#include "Ball.h"
#include <iomanip>

BaseObject g_background;

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

            p_character_0.DoCharacter(&g_background, ball);
            p_character_1.DoCharacter(&g_background, ball);
            p_character_2.DoCharacter(&g_background, ball);
            p_character_3.DoCharacter(&g_background, ball);
            p_character_4.DoCharacter(&g_background, ball);
            p_character_5.DoCharacter(&g_background, ball);
            

            /*ball.CheckToCharacter(&p_character_0);
            ball.CheckToCharacter(&p_character_1);
            ball.CheckToCharacter(&p_character_2);
            ball.CheckToCharacter(&p_character_3);
            ball.CheckToCharacter(&p_character_4);
            ball.CheckToCharacter(&p_character_5);*/

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

    Close();

	return 0;
}