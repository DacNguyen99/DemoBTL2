#pragma once

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include <BaseFunc.h>

#define CHARACTER_SPEED 0.4

enum Mode {
	INIT,
	PVC,
	PVP,
};

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; };
	SDL_Rect GetRect() { return rect_; }
	SDL_Texture* GetObject() const { return p_object_; }
	Mode GetMode() { return mode_; };

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
	void HandleUserInput(SDL_Event events, SDL_Renderer* screen);
	bool SetBackground(SDL_Renderer* screen);
	void UpdateCharacterPos(int index, float pos_x, float pos_y) { characters_pos_x_[index] = pos_x; characters_pos_y_[index] = pos_y; };
	void UpdateWidthFrame(int index, int width_frame) { characters_width_frame[index] = width_frame; };

	float GetPosX(int index) { return characters_pos_x_[index]; };
	float GetPosY(int index) { return characters_pos_y_[index]; };
	int GetWidth(int index) { return characters_width_frame[index]; };

protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
	Mode mode_;

	float characters_pos_x_[6];
	float characters_pos_y_[6];
	int characters_width_frame[6];
};


#endif 