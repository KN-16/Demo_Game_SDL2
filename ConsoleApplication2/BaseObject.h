#pragma once
#include "Function_Common.h"
class BaseObject
{	
protected:
	SDL_Texture* texture_;
	SDL_Rect rect_;
public:
	BaseObject();
	~BaseObject();
	bool Base_Loadtexture(std::string a);
	bool Base_Show();
	void Set_rect_pos(int x, int y);
	void Set_rect_size(int, int);
	int get_rect_x() { return this->rect_.x; }
};
