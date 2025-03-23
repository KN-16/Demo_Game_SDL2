#pragma once
#include "BaseObject.h"
#include "BulletObject.h"
#include "HealthPlayerObject.h"

#define MAINOBJECT_WIDTH 117
#define MAINOBJECT_HEIGHT 113
#define SPEED_MAIN 15
#define SPEED_BULLET_MAIN 10

class MainObject:public BaseObject 
{
private:
	int x_val;
	int y_val; 
	HealthPlayerObject hp_;
public:
	std::vector<BulletObject*> main_amor;
	bool explosion;
	int explosion_frame;
	bool exp_sound;
	bool MainObject_Move();
	void MainObject_MoveAction(SDL_Event &events);
	
	MainObject();
	~MainObject();
	void Main_Amor_Action();
	void Main_Impact(const SDL_Rect&);
	int get_rect_x() { return this->rect_.x; }
	int get_rect_y() { return this->rect_.y; }
	int get_size_amor() { return this->main_amor.size(); }
	HealthPlayerObject& getr_hp_main() { return this->hp_; }
	void test_input(SDL_Event&);
};