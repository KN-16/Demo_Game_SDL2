#pragma once
#include "Function_Common.h"
#include "BaseObject.h"
class TextObject :public BaseObject 
{ private:
	SDL_Color text_color;
	std::string str_val_;
	SDL_Surface* text_surface;
public:
	enum Text_Color
	{
		Red, White, Yellow, Blue,Black
	};
	void set_color(TextObject::Text_Color);
	TextObject();
	~TextObject();
	void Create_text(TTF_Font*,std::string);
	void set_str(std::string str) { this->str_val_ = str; }
};