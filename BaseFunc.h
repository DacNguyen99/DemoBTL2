#pragma once
#ifndef BASE_FUNCTION_H_
#define BASE_FUNCTION_H_

#include <Windows.h>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// Screen
const int SCREEN_WIDTH = 360;
const int SCREEN_HEIGHT = 629;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 230;
const int COLOR_KEY_G = 230;
const int COLOR_KEY_B = 230;

const int RENDER_DRAW_COLOR = 0xFF;

const int LEFT_X = 21;
const int RIGHT_X = 339;

const int TOP_Y = 47;
const int BOTTOM_Y = 580;

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
};

#endif