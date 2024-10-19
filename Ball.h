#pragma once

#ifndef BALL_OBJECT_H_
#define BALL_OBJECT_H_

#include "BaseFunc.h"
#include "BaseObject.h"

class BallObject : public BaseObject
{
public:
	BallObject(const int pos_x, const int pos_y);
	~BallObject();

	void Show(SDL_Renderer* des);

private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;
};

#endif