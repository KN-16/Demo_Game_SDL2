#pragma once
#include "Function_Common.h"
#include "BaseObject.h"
class HealthPlayerObject:public BaseObject 
{	private:
		int hp;
	public:
		HealthPlayerObject();
		~HealthPlayerObject();
		int &getr_hp() { return this->hp; }
		void hp_show();
		void set_hp(int);
};