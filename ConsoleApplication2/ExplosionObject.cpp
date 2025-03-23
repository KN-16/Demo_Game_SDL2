#include "ExplosionObject.h"
ExplosionObject::ExplosionObject()
{
	flame_fame = 0;
}
ExplosionObject::~ExplosionObject()
{
	
}
void ExplosionObject::Set_flame_frame(int a)
{
	this->flame_fame = a;
	this->explosion_rect.resize(this->flame_fame);
}
void ExplosionObject::Set_size_per_frame(int rect_w, int rect_h)
{
	for (int i = 0; i < this->flame_fame; i++)
	{
		explosion_rect[i].x = i * rect_w;
		explosion_rect[i].y = 0;
		explosion_rect[i].w = rect_w;
		explosion_rect[i].h = rect_h;
	}
}
bool ExplosionObject::load_explosion(int rect_x ,int rect_y, int i)
{
	this->rect_.x = rect_x;
	this->rect_.y = rect_y;
	this->rect_.w = (this->explosion_rect)[i].w;
	this->rect_.h = this->explosion_rect[i].h;
	if (SDL_RenderCopy(g_rscreen, this->texture_, &this->explosion_rect[i], &rect_) == 0)
			return true;
	else
		return false; 
	
}
void ExplosionObject::Set_texture_exp(std::string path, int red, int green, int blue)
{
	this->texture_ = Function_Common::optimize_load_image_colorkey(path.c_str(), red, green, blue);
}
