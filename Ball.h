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

	void UpdateBallPos() { 
		ball_rect_.x = static_cast<int>(x_pos_); 
		ball_rect_.y = static_cast<int>(y_pos_);
	};

	void Show(SDL_Renderer* des);
	void Move();
	void CheckToMap();
	//void CheckToCharacter(CharacterObject* player);

	// Getter for ball rectangle (bounding box)
	SDL_Rect GetRect() const { return ball_rect_; }

	// Getter and Setter for X velocity
	float GetXVal() const { return x_val_; }
	void SetXVal(float val) { x_val_ = val; }

	// Getter and Setter for Y velocity
	float GetYVal() const { return y_val_; }
	void SetYVal(float val) { y_val_ = val; }

	void Reset();

private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	SDL_Rect ball_rect_;
};

#endif