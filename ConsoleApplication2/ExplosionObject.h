#pragma once
#include "Function_Common.h"
#include "BaseObject.h"
class ExplosionObject:public BaseObject  
{	private:
	int flame_fame;
	std::vector<SDL_Rect> explosion_rect;
public:
	void Set_flame_frame(int);
	ExplosionObject();
	~ExplosionObject();
	bool load_explosion(int,int,int);
	void Set_size_per_frame(int,int );
	void Set_texture_exp(std::string, int, int, int);
};