#include "Ball.h"

BallObject::BallObject(const int pos_x, const int pos_y)
{
	x_pos_ = pos_x;
	y_pos_ = pos_y;
	x_val_ = 0;
	y_val_ = 0;
}

BallObject::~BallObject()
{

}

void BallObject::Show(SDL_Renderer* des)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	SDL_Rect renderQuad = { rect_.x, rect_.y, 21, 20 };

	SDL_RenderCopy(des, p_object_, nullptr, &renderQuad);
}
