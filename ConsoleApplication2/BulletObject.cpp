#include "BulletObject.h"

BulletObject::BulletObject()
{
	x_val_amor = 0;
	y_val_amor = 0;
	is_amor = false;
	type_amor = BulletObject::NONE;
}
BulletObject::~BulletObject()
{
	;
}
void BulletObject::set_x_val_amor(int a)
{
	x_val_amor = a;
}
void BulletObject::set_y_val_amor(int b)
{
	y_val_amor = b;
}
void  BulletObject::set_rect_size()
{
	if (type_amor == BulletObject::LASE)
	{
		this->rect_.w = LASE_WIDTH;
		this->rect_.h = LASE_HEIGHT;
	}
	else if (type_amor == BulletObject::CAU)
	{
		this->rect_.w = CAU_WIDTH;
		this->rect_.h = CAU_HEIGHT;
	}
}
void BulletObject::Amor_Move()
{
	rect_.x += x_val_amor;
	rect_.y += y_val_amor;
	if (rect_.x + rect_.w-1 > SCREEN_WIDTH || rect_.y + rect_.h-1 > SCREEN_HEIGHT) 
	this->is_amor = false;
}
void BulletObject::Amor_Move1()
{
	rect_.x -= x_val_amor;
	rect_.y -= y_val_amor;
	if (rect_.x + rect_.w < 0 || rect_.y + rect_.h < 0)
		is_amor = false;

}