#pragma once
#include "BaseObject.h"
#include "BulletObject.h"
#define LASE_WIDTH 34
#define LASE_HEIGHT 3
#define CAU_WIDTH 12
#define CAU_HEIGHT 6
class BulletObject :public BaseObject {
private:
	int x_val_amor;
	int y_val_amor;
	bool is_amor;
	unsigned int type_amor;
public:
	enum Amor_Type
	{
		NONE ,
		LASE ,
		CAU
	};
	BulletObject();
	~BulletObject();
	void set_x_val_amor(int );
	void set_y_val_amor(int);
	void set_rect_size();
	void set_type_amor(Amor_Type a) { this->type_amor = a; }
	void set_is_amor(bool a) { this->is_amor = a; }
	bool get_is_amor() { return this->is_amor; }
	void Amor_Move();
	void Amor_Move1();
	int get_type_amor() { return this->type_amor; }
	SDL_Rect &get_rect() { return this->rect_; }
};
