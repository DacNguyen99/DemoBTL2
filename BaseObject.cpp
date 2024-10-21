#include "BaseObject.h"

BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	mode_ = INIT;
}

BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	Free();
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL) {
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL) {
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}

	p_object_ = new_texture;
	return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };

	SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::HandleUserInput(SDL_Event events, SDL_Renderer* screen)
{
	if (mode_ == INIT)
	{
		if (events.type == SDL_MOUSEBUTTONDOWN)
		{
			if (events.button.button == SDL_BUTTON_LEFT)
			{
				// pvp
				if ((events.button.x >= 0 && events.button.x <= 143) && (events.button.y >= 0 && events.button.y <= 107))
				{
					mode_ = PVP;
					std::cout << "pvp \n";
				}

				// pvc
				if ((events.button.x >= 216 && events.button.x <= 360) && (events.button.y >= 523 && events.button.y <= 629))
				{
					mode_ = PVC;
					std::cout << "pvc \n";
				}
			}
		}
	}
	else
	{
		if (events.type == SDL_MOUSEBUTTONDOWN)
		{
			if (events.button.button == SDL_BUTTON_RIGHT)
			{
				mode_ = INIT;
				std::cout << "init \n";
			}
		}
	}

	if (SetBackground(screen) == false)
	{
		std::cout << "set bg fail \n";
		return;
	}
}

bool BaseObject::SetBackground(SDL_Renderer* screen)
{
	bool ret = true;
	switch (mode_)
	{
	case INIT:
		if (LoadImg("res/menu.png", screen) == false)
		{
			std::cout << "load menu fail \n";
			ret = false;
		}
		break;
	case PVC:
		if (LoadImg("res/field1.png", screen) == false)
		{
			std::cout << "load pvc fail \n";
			ret = false;
		}
		break;
	case PVP:
		if (LoadImg("res/field1.png", screen) == false)
		{
			std::cout << "load pvp fail \n";
			ret = false;
		}
		break;
	case RED:
		if (LoadImg("res/rwin.png", screen) == false)
		{
			std::cout << "load red fail \n";
			ret = false;
		}
		break;
	case BLUE:
		if (LoadImg("res/bwin.png", screen) == false)
		{
			std::cout << "load blue fail \n";
			ret = false;
		}
		break;
	default:
		break;
	}

	return ret;
}

void BaseObject::Free()
{
	if (p_object_ != NULL) {
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}