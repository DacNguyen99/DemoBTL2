#include "Ball.h"

BallObject::BallObject(const int pos_x, const int pos_y)
{
	x_pos_ = pos_x;
	y_pos_ = pos_y;
	x_val_ = 0;
	y_val_ = 0;
    ball_rect_ = {pos_x, pos_y, 21, 20};
    red_goal_ = false;
    blue_goal_ = false;
}

BallObject::~BallObject()
{

}

void BallObject::Show(SDL_Renderer* des)
{
	SDL_RenderCopy(des, p_object_, nullptr, &ball_rect_);
}

void BallObject::Move() {
    x_pos_ += x_val_;
    y_pos_ += y_val_;

    x_val_ *= 0.999f;
    y_val_ *= 0.999f;

    if (fabs(x_val_) < 0.01f) x_val_ = 0;
    if (fabs(y_val_) < 0.01f) y_val_ = 0;

    CheckToMap();

    UpdateBallPos();
}

void BallObject::CheckToMap() {
    if (x_pos_ < LEFT_X) {
        x_pos_ = LEFT_X;
        x_val_ = -x_val_;
    }
    else if (x_pos_ + ball_rect_.w > RIGHT_X) {
        x_pos_ = RIGHT_X - ball_rect_.w;
        x_val_ = -x_val_;
    }

    if (y_pos_ < TOP_Y) {
        y_pos_ = TOP_Y;
        y_val_ = -y_val_;
    }
    else if (y_pos_ + ball_rect_.h > BOTTOM_Y) {
        y_pos_ = BOTTOM_Y - ball_rect_.h;
        y_val_ = -y_val_;
    }
}

void BallObject::Reset()
{
    x_val_ = 0;
    y_val_ = 0;

    x_pos_ = 168.5f;
    y_pos_ = 304.0f;

    ball_rect_ = { (int)x_pos_, (int)y_pos_, 21, 20 };

    red_goal_ = false;
    blue_goal_ = false;
}

void BallObject::GoalCheck()
{
    if (y_pos_ == TOP_Y && (x_pos_ >= 154 && x_pos_ <= 185))
    {
        std::cout << "red" << std::endl;
        blue_goal_ = true;
    }

    if (y_pos_ == (BOTTOM_Y - ball_rect_.h) && (x_pos_ >= 154 && x_pos_ <= 185))
    {
        std::cout << "blue" << std::endl;
        red_goal_ = true;
    }
}