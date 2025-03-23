#include "HealthPlayerObject.h"
#define HP_WIDTH 21
#define HP_HEIGHT 21
HealthPlayerObject::HealthPlayerObject()
{
	this->hp = 0;
	this->texture_ = Function_Common::optimize_load_image_colorkey("hp.png", 217, 217, 217);
	this->rect_.w = HP_WIDTH;
	this->rect_.h = HP_HEIGHT;
}
HealthPlayerObject::~HealthPlayerObject()
{
	
}
void HealthPlayerObject::hp_show()
{
	for (int i = 1; i < this->hp; i++)
	{
		this->rect_.x = (HP_WIDTH+6)*i;
		Function_Common::Apply_image(this->texture_, &this->rect_);
	}
}
void HealthPlayerObject::set_hp(int tmp)
{
	this->hp = tmp;
}