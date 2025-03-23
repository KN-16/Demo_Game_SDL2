#pragma once
#include "BaseObject.h"
#include "BulletObject.h"
#include "HealthPlayerObject.h"
#define THREAT_WIDTH 93
#define THREAT_HEIGHT 112
#define SPEED_THREAT 3
#define SPEED_BULLET_THREAT 10
#define DISTANCE_BULLET_THREAT 200
class ThreatObject :public BaseObject {
private:
	int x_val, y_val;
	int type_amor;
	bool threat_die;
	HealthPlayerObject hp_;
public:
	bool exp_sound;
	std::vector<BulletObject*> threat_amor;
	void Move_Action();
	void Threat_Amor_Action();
	void Threat_Amor_Move();
	void Threat_Move();
	void Set_x_val(int x) { this->x_val = x; }
	ThreatObject();
	~ThreatObject();
	int get_rect_x() { return this->rect_.x; }
	int get_rect_y() { return this->rect_.y; }
	bool explosion;
	int explosion_frame;
	void Threat_Amor_Show();
	void Threat_Impact(const SDL_Rect&);
	bool get_threat_die() { return this->threat_die; }
	HealthPlayerObject& getr_hp_threat() { return this->hp_; }
};