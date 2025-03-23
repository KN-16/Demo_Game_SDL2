#include "MenuObject.h"
MenuObject::MenuObject()
{
}
MenuObject::MenuObject(int num_of_TextObject)
{
	this->ListTextObject.resize(num_of_TextObject);

}
MenuObject::~MenuObject()
{

}
void MenuObject::Set_num_of_TextObject(int num_of_TextObject)
{
	this->ListTextObject.resize(num_of_TextObject);
}
void MenuObject::Action()
{
	SDL_Event event;
	while (true)
	{
		this->Show();

	}

}
bool MenuObject::Show()
{
	for (TextObject& text_tmp : this->ListTextObject)
	{
		if (!text_tmp.Base_Show())
		{
			Function_Common::load_error();
			return false;
		}
		return true;

	}
}