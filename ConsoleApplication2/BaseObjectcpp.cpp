#include "BaseObject.h"
BaseObject::BaseObject() // Constructor default
{
	texture_ = NULL;
	rect_.x = rect_.y = rect_.w = rect_.h = 0;
}
BaseObject::~BaseObject()
{	
	if (texture_)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}
bool BaseObject::Base_Loadtexture(std::string a)
{
	this->texture_=Function_Common::optimize_load_image(a);
	if (!texture_) return false;
	return true;
}
bool BaseObject::Base_Show()
{
	if (!Function_Common::Apply_image(texture_, &rect_)) return false;
	return true;
}
void BaseObject::Set_rect_pos(int x, int y)
{
	this->rect_.x = x;
	this->rect_.y = y;
}
void BaseObject::Set_rect_size(int w, int h)
{
	this->rect_.w = w;
	this->rect_.h = h;
}
