#include "ThreatObject.h"
ThreatObject::ThreatObject()
{
	 x_val = y_val = 0;
	 rect_.x = SCREEN_WIDTH-THREAT_WIDTH;
	 do 
	 {
		 this->rect_.y = rand() % (SCREEN_HEIGHT - THREAT_HEIGHT);
	 } while (rect_.y<0 || rect_.y>SCREEN_HEIGHT - THREAT_HEIGHT - 2);
	 this->Base_Loadtexture("Threat.png");
	 type_amor = rand() % 2;
	 rect_.w = THREAT_WIDTH;
	 rect_.h = THREAT_HEIGHT;
	 threat_die = 0;
	 explosion = false;
	 explosion_frame = 0;
	 exp_sound = false;
}
ThreatObject::~ThreatObject()
{
	for (int i=0;i<threat_amor.size();i++)
		if (threat_amor[i]) 
		{
			delete threat_amor[i]; threat_amor[i] = NULL;
			threat_amor.erase(threat_amor.begin() + i);
			i--;
		}
}
void ThreatObject::Threat_Amor_Action()
{
	if (!this->threat_amor.size()) {
		BulletObject* tmp = new BulletObject;
		if (this->type_amor == 1)
		{
			tmp->Base_Loadtexture("amor2_laser.png");
			tmp->set_type_amor(BulletObject::LASE);
		}
		else {
			tmp->Base_Loadtexture("amor1_cau.png");
			tmp->set_type_amor(BulletObject::CAU);
		}
		tmp->set_rect_size();
		if (tmp->get_type_amor() == 1)
			tmp->Set_rect_pos(this->rect_.x + SPEED_BULLET_THREAT-LASE_WIDTH, this->rect_.y + THREAT_HEIGHT * 0.5 - 1);
		else
			tmp->Set_rect_pos(this->rect_.x + SPEED_BULLET_THREAT-CAU_WIDTH, this->rect_.y + THREAT_HEIGHT * 0.5 - 1);
		tmp->set_x_val_amor(SPEED_BULLET_THREAT);
		tmp->set_is_amor(true);
		this->threat_amor.push_back(tmp);
	}
	else
	{
		if ((this->type_amor == 1) && (this->threat_amor[threat_amor.size() - 1]->get_rect_x() + LASE_WIDTH - 1 + DISTANCE_BULLET_THREAT <= this->rect_.x + SPEED_BULLET_THREAT - LASE_WIDTH))
		{
			BulletObject* tmp = new BulletObject;
			tmp->Base_Loadtexture("amor2_laser.png");
			tmp->set_type_amor(BulletObject::LASE);
			tmp->set_rect_size();
			tmp->Set_rect_pos(this->rect_.x + SPEED_BULLET_THREAT-LASE_WIDTH, this->rect_.y + THREAT_HEIGHT * 0.5 - 1);
			tmp->set_x_val_amor(SPEED_BULLET_THREAT);
			tmp->set_is_amor(true);
			this->threat_amor.push_back(tmp);
			return;
		}	if ((this->type_amor == 0) && (this->threat_amor[threat_amor.size() - 1]->get_rect_x() + CAU_WIDTH - 1 + DISTANCE_BULLET_THREAT <= this->rect_.x + SPEED_BULLET_THREAT - CAU_WIDTH))
		{
			BulletObject* tmp = new BulletObject;
			tmp->Base_Loadtexture("amor1_cau.png");
			tmp->set_type_amor(BulletObject::CAU);
			tmp->set_rect_size();
			tmp->Set_rect_pos(this->rect_.x + SPEED_BULLET_THREAT-CAU_WIDTH, this->rect_.y + THREAT_HEIGHT * 0.5 - 1);
			tmp->set_x_val_amor(SPEED_BULLET_THREAT);
			tmp->set_is_amor(true);
			this->threat_amor.push_back(tmp);
			return;
		}
	}

}
void ThreatObject::Threat_Amor_Move()
{
	for (int i = 0; i < threat_amor.size(); i++)
	{
		BulletObject* tmp = threat_amor.at(i);
		tmp->Amor_Move1();
		if (tmp != NULL) 
		{
			if (!(tmp->get_is_amor())) 
			{
				delete tmp; tmp = NULL;
				threat_amor.erase(threat_amor.begin() + i);
				i--;
			}
		}
	}
}
void ThreatObject::Threat_Move()
{
	this->rect_.x -= x_val;
	if (this->rect_.x < 0)
		threat_die = 1; 
}
void ThreatObject::Threat_Amor_Show()
{
	for (int i = 0; i < threat_amor.size(); i++)
	{
		BulletObject* tmp = threat_amor.at(i);
		if (tmp != NULL)
		{
			if (!(tmp->get_is_amor()))
			{
				delete tmp; tmp = NULL;
				threat_amor.erase(threat_amor.begin() + i);
				i--;
			}
			else 
				tmp->Base_Show();
		}
		else 
		{
			threat_amor.erase(threat_amor.begin() + i);
			i--;
		}
	}
}
void ThreatObject::Threat_Impact(const SDL_Rect& tmp)
{	
	if (Function_Common::Impact(tmp, this->rect_,false))
		this->explosion = true;
}
