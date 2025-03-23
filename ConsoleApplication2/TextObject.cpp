#include "TextObject.h"
TextObject::TextObject()
{
	this->str_val_ = "";
	this->text_color = { 0,0,0 };
}
TextObject:: ~TextObject()
{
}
void TextObject::set_color(TextObject::Text_Color tmp)
{
	switch (tmp)
	{case TextObject::Red:
		this->text_color = { 255,0,0 };
		break;
	case TextObject::Blue:
		this->text_color = { 0,0,255 };
		break;
	case TextObject::Yellow:
		this->text_color = { 255,255,0 };
		break;
	case TextObject::White:
		this->text_color = { 255,255,255 };
		break;
	case TextObject::Black:
		this->text_color = { 0,0,0 };
		break;
	default:
		break;
	}

}
void TextObject::Create_text(TTF_Font* font_,std::string str)
{
	SDL_Surface* tmp = TTF_RenderText_Solid(font_, (this->str_val_+str).c_str(), this->text_color);
	this->texture_ = SDL_CreateTextureFromSurface(g_rscreen, tmp);
	this->rect_.w = tmp->w;
	this->rect_.h = tmp->h;
	SDL_FreeSurface(tmp);
	tmp = NULL;
}