#pragma once
#include "Function_Common.h"
#include "TextObject.h"
class MenuObject 
{ private:
	std::vector<TextObject> ListTextObject;
public:
	MenuObject();
	MenuObject(int num_of_TextObject);
	~MenuObject();
	void Action();
	bool Show();
	void Set_num_of_TextObject(int);
};