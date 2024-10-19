#pragma once

#ifndef CHARACTER_OBJECT_H_
#define CHARACTER_OBJECT_H_

#include "BaseFunc.h"
#include "BaseObject.h"

#define FRAMES 4

class CharacterObject : public BaseObject
{
public:
	CharacterObject(BaseObject* base, const int pos_x, const int pos_y, const int num);
	~CharacterObject();

	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4,
	};

	bool LoadImg(std::string path, SDL_Renderer* screen, BaseObject* base);
	void Show(SDL_Renderer* des, BaseObject* base);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	void DoCharacter(BaseObject* base);
	void CheckToMap();
	void CheckToOtherCharacters(BaseObject* base);

	float GetXPos() { return x_pos_; };
	float GetYPos() { return y_pos_; };
	int GetWidthFrame() { return width_frame_; };

private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[FRAMES];
	Input input_type_;
	int frame_;
	int status_;
	int num_;

	BaseObject* base_;
};

#endif


