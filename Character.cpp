#include "Character.h"

CharacterObject::CharacterObject(BaseObject* base, const int pos_x, const int pos_y, const int num)
{
	base_ = base;
	frame_ = 0;
	x_pos_ = pos_x;
	y_pos_ = pos_y;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;

	switch (num)
	{
	case 0:
		status_ = WALK_DOWN;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 1:
		status_ = WALK_DOWN;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 2:
		status_ = WALK_DOWN;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 3:
		status_ = WALK_UP;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 4:
		status_ = WALK_UP;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 5:
		status_ = WALK_UP;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	default:
		break;
	}

	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	num_ = num;
}

CharacterObject::~CharacterObject()
{

}

bool CharacterObject::LoadImg(std::string path, SDL_Renderer* screen, BaseObject* base)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w / FRAMES;
		height_frame_ = rect_.h;
	}

	base->UpdateWidthFrame(num_, width_frame_);

	return ret;
}

void CharacterObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2 * width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;
	}
}

void CharacterObject::Show(SDL_Renderer* des, BaseObject* base)
{
	if (num_ == 0 || num_ == 1 || num_ == 2)
	{
		if (status_ == WALK_LEFT)
		{
			LoadImg("res/characters/loren/walk_left.png", des, base);
		}
		else if (status_ == WALK_RIGHT)
		{
			LoadImg("res/characters/loren/walk_right.png", des, base);
		}
		else if (status_ == WALK_DOWN)
		{
			LoadImg("res/characters/loren/front.png", des, base);
		}
		else if (status_ == WALK_UP)
		{
			LoadImg("res/characters/loren/back.png", des, base);
		}
	}
	else
	{
		if (status_ == WALK_LEFT)
		{
			LoadImg("res/characters/argen/walk_left.png", des, base);
		}
		else if (status_ == WALK_RIGHT)
		{
			LoadImg("res/characters/argen/walk_right.png", des, base);
		}
		else if (status_ == WALK_DOWN)
		{
			LoadImg("res/characters/argen/front.png", des, base);
		}
		else if (status_ == WALK_UP)
		{
			LoadImg("res/characters/argen/back.png", des, base);
		}
	}

	set_clips();

	if (input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.up_ == 1 || input_type_.down_ == 1)
	{
		frame_++;
	}
	else {
		frame_ = 0;
	}

	if (frame_ >= FRAMES)
	{
		frame_ = 0;
	}

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = &frame_clip_[frame_];

	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void CharacterObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (num_ == 0 || num_ == 1 || num_ == 2)
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_RIGHT:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				input_type_.up_ = 0;
				input_type_.down_ = 0;
			}
			break;

			case SDLK_LEFT:
			{
				status_ = WALK_LEFT;
				input_type_.right_ = 0;
				input_type_.left_ = 1;
				input_type_.up_ = 0;
				input_type_.down_ = 0;
			}
			break;

			case SDLK_UP:
			{
				status_ = WALK_UP;
				input_type_.right_ = 0;
				input_type_.left_ = 0;
				input_type_.up_ = 1;
				input_type_.down_ = 0;
			}
			break;

			case SDLK_DOWN:
			{
				status_ = WALK_DOWN;
				input_type_.right_ = 0;
				input_type_.left_ = 0;
				input_type_.up_ = 0;
				input_type_.down_ = 1;
			}
			break;

			default:
				break;
			}
		}
		else if (events.type == SDL_KEYUP)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_RIGHT:
			{
				input_type_.right_ = 0;
			}
			break;

			case SDLK_LEFT:
			{
				input_type_.left_ = 0;
			}
			break;

			case SDLK_UP:
			{
				input_type_.up_ = 0;
			}
			break;

			case SDLK_DOWN:
			{
				input_type_.down_ = 0;
			}
			break;

			default:
				break;
			}
		}
	}
	else if (num_ == 3 || num_ == 4 || num_ == 5)
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_d:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				input_type_.up_ = 0;
				input_type_.down_ = 0;
			}
			break;

			case SDLK_a:
			{
				status_ = WALK_LEFT;
				input_type_.right_ = 0;
				input_type_.left_ = 1;
				input_type_.up_ = 0;
				input_type_.down_ = 0;
			}
			break;

			case SDLK_w:
			{
				status_ = WALK_UP;
				input_type_.right_ = 0;
				input_type_.left_ = 0;
				input_type_.up_ = 1;
				input_type_.down_ = 0;
			}
			break;

			case SDLK_s:
			{
				status_ = WALK_DOWN;
				input_type_.right_ = 0;
				input_type_.left_ = 0;
				input_type_.up_ = 0;
				input_type_.down_ = 1;
			}
			break;

			default:
				break;
			}
		}
		else if (events.type == SDL_KEYUP)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_d:
			{
				input_type_.right_ = 0;
			}
			break;

			case SDLK_a:
			{
				input_type_.left_ = 0;
			}
			break;

			case SDLK_w:
			{
				input_type_.up_ = 0;
			}
			break;

			case SDLK_s:
			{
				input_type_.down_ = 0;
			}
			break;

			default:
				break;
			}
		}
	}
}

void CharacterObject::DoCharacter(BaseObject* base, BallObject& ball)
{
	x_val_ = 0;
	y_val_ = 0;

	if (input_type_.left_ == 1)
	{
		x_val_ -= CHARACTER_SPEED;
	}
	else if (input_type_.right_ == 1)
	{
		x_val_ += CHARACTER_SPEED;
	}
	else if (input_type_.up_ == 1)
	{
		y_val_ -= CHARACTER_SPEED;
	}
	else if (input_type_.down_ == 1)
	{
		y_val_ += CHARACTER_SPEED;
	}

	CheckToMap();
	//CheckToOtherCharacters(base);

	HandleBallCollision(ball);

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	base->UpdateCharacterPos(num_, x_pos_, y_pos_);
}

void CharacterObject::CheckToMap()
{
	// check horizontal
	if (x_pos_ < LEFT_X)
	{
		x_pos_ = LEFT_X;
		x_val_ = 0;
	}
	else if (x_pos_ > (RIGHT_X - width_frame_))
	{
		x_pos_ = RIGHT_X - width_frame_;
		x_val_ = 0;
	}

	// check vertical
	if (y_pos_ < TOP_Y)
	{
		y_pos_ = TOP_Y;
		y_val_ = 0;
	}
	else if (y_pos_ > (BOTTOM_Y - height_frame_))
	{
		y_pos_ = BOTTOM_Y - height_frame_;
		y_val_ = 0;
	}
}

//void CharacterObject::CheckToOtherCharacters(BaseObject* base)
//{
//	for (int i = 0; i < 6; i++)
//	{
//		if (i == num_)
//		{
//			continue;
//		}
//		else
//		{
//			// A.max.x < B.min.x && A.min.x > B.max.x && A.max.y < B.min.y && A.min.y > B.max.y
//			// check if there is a collison
//			if (x_pos_ + width_frame_ < base->GetPosX(i) || 
//				x_pos_ > base->GetPosX(i) + base->GetWidth(i) || 
//				y_pos_ < base->GetPosY(i) + height_frame_ || 
//				y_pos_ + height_frame_ > base->GetPosY(i)) 
//			{
//				continue;
//			}
//			else {
//				// there is collison, check direction
//				std::cout << "collison" << std::endl;
//
//				// right
//				if (x_val_ > 0)
//				{
//					x_pos_ = base->GetPosX(i) - base->GetWidth(i);
//					x_val_ = 0;
//					continue;
//				}
//
//				// left
//				if (x_val_ < 0)
//				{
//					x_pos_ = base->GetPosX(i) + base->GetWidth(i);
//					x_val_ = 0;
//					continue;
//				}
//
//				// up
//				if (y_val_ < 0)
//				{
//					y_pos_ = base->GetPosY(i) + height_frame_;
//					y_pos_ = 0;
//					continue;
//				}
//
//				// down
//				if (y_val_ > 0)
//				{
//					y_pos_ = base->GetPosY(i) - height_frame_;\
//					y_pos_ = 0;
//					continue;
//				}
//			}
//		}
//	}
//}

// Function to check collision between the ball and the player
bool CheckCollision(const SDL_Rect& ball_rect, const SDL_Rect& player_rect)
{
	// Check if the two rectangles overlap (simple AABB collision detection)
	if (ball_rect.x + ball_rect.w < player_rect.x ||
		ball_rect.x > player_rect.x + player_rect.w ||
		ball_rect.y + ball_rect.h < player_rect.y ||
		ball_rect.y > player_rect.y + player_rect.h)
	{
		return false; // No collision
	}
	return true; // Collision detected
}

void CharacterObject::HandleBallCollision(BallObject& ball)
{
	// Get the bounding rectangles for the player and the ball
	SDL_Rect player_rect = { x_pos_, y_pos_, width_frame_, height_frame_ };
	SDL_Rect ball_rect = ball.GetRect();

	// Check for collision
	if (CheckCollision(ball_rect, player_rect))
	{
		float player_center_x = x_pos_ + width_frame_ / 2;
		float player_center_y = y_pos_ + height_frame_ / 2;

		float ball_center_x = ball_rect.x + ball_rect.w / 2;
		float ball_center_y = ball_rect.y + ball_rect.h / 2;

		float vec_x = ball_center_x - player_center_x;
		float vec_y = ball_center_y - player_center_y;

		float angle = atan2(vec_y, vec_x);

		float speed = 0.6f;

		ball.SetXVal(speed * cos(angle));
		ball.SetYVal(speed * sin(angle));
	}
}

void CharacterObject::Reset(const int pos_x, const int pos_y, const int num)
{
	x_val_ = 0;
	y_val_ = 0;

	x_pos_ = pos_x;
	y_pos_ = pos_y;

	frame_ = 0;

	width_frame_ = 0;
	height_frame_ = 0;

	switch (num)
	{
	case 0:
		status_ = WALK_DOWN;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 1:
		status_ = WALK_DOWN;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 2:
		status_ = WALK_DOWN;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 3:
		status_ = WALK_UP;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 4:
		status_ = WALK_UP;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	case 5:
		status_ = WALK_UP;
		base_->UpdateCharacterPos(num, pos_x, pos_y);
		break;

	default:
		break;
	}

	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	num_ = num;
}