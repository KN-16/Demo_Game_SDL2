#include "MainObject.h"

MainObject::MainObject()
{
	rect_.w = MAINOBJECT_WIDTH;
	rect_.h = MAINOBJECT_HEIGHT;
	x_val = 0;
	y_val = 0;
	explosion = false;
	explosion_frame = 0;
	exp_sound = false;
}
MainObject::~MainObject()
{
	for (int i = 0; i < main_amor.size(); i++)
		if (main_amor[i]) 
		{
			delete main_amor[i]; main_amor[i] = NULL;
		}
}
bool MainObject::MainObject_Move()
{	
	rect_.x += x_val;
	rect_.y += y_val;
	if (rect_.x > SCREEN_WIDTH - 200 - MAINOBJECT_WIDTH ||rect_.x<0)
		rect_.x -= x_val;
	if (rect_.y > SCREEN_HEIGHT - 100 - MAINOBJECT_HEIGHT || rect_.y < 0)
		rect_.y -= y_val;
	if (!Base_Show()) return false;
	else return true;
}
void MainObject::MainObject_MoveAction(SDL_Event& events)
{
	if (events.type == SDL_KEYDOWN)
	{
		std::cout << "KEYDOWN\n";
		switch (events.key.keysym.sym)
		{

		case SDLK_UP:
		case SDLK_w:
			y_val = -SPEED_MAIN;
			//y_val -= SPEED_MAIN;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			y_val = SPEED_MAIN;
			//	y_val += SPEED_MAIN;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			x_val = -SPEED_MAIN;
			//x_val -= SPEED_MAIN;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			x_val = SPEED_MAIN;
			//x_val += SPEED_MAIN;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		std::cout << "KEYUP\n";
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_w:
				//y_val += SPEED_MAIN;
				y_val = 0;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				//y_val -= SPEED_MAIN;
				y_val = 0;
				break;
			case SDLK_LEFT:
			case SDLK_a:
				//x_val += SPEED_MAIN;
				x_val = 0;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				//x_val -= SPEED_MAIN;
				x_val = 0;
				break;
			default:
				break;
			}
		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
	
		BulletObject* p_amor = new BulletObject;
		switch (events.button.button)
		{
		case SDL_BUTTON_LEFT:
			std::cout << "LEFTDOWN\n";
			p_amor->Base_Loadtexture("amor2_laser.png");
			p_amor->set_type_amor(BulletObject::LASE);
			p_amor->set_rect_size();
			p_amor->Set_rect_pos(this->rect_.x + this->rect_.w, this->rect_.y + this->rect_.h / 2-1);
			p_amor->set_is_amor(true);
			p_amor->set_x_val_amor(SPEED_BULLET_MAIN);
		Mix_PlayChannel(-1, g_sound_bullet[0], 0);
			break;
		case SDL_BUTTON_RIGHT:
			std::cout << "RIGHDOWN\n";
			p_amor->Base_Loadtexture("amor1_cau.png");
			p_amor->set_type_amor(BulletObject::CAU);
			p_amor->set_rect_size();
			p_amor->Set_rect_pos(this->rect_.x + this->rect_.w-5, this->rect_.y + this->rect_.h / 2-1);
			p_amor->set_x_val_amor(SPEED_BULLET_MAIN);
			p_amor->set_is_amor(true);
			Mix_PlayChannel(-1, g_sound_bullet[1], 0);
			break;
		default:
			break;
		}
		this->main_amor.push_back(p_amor);
	}
}
void MainObject::Main_Amor_Action()
{
	for (int i=0;i<main_amor.size();i++)
	{
		BulletObject* tmp = main_amor.at(i);
		if (tmp)
		{
			tmp->Amor_Move();
			if (!(tmp->get_is_amor()))
			{
				delete tmp; tmp = NULL;
				main_amor.erase(main_amor.begin() + i);
				i--;
			}
			else  tmp->Base_Show();
		}
		else
		{
			main_amor.erase(main_amor.begin() + i);
			i--;
		}
	}
}
void MainObject::Main_Impact(const SDL_Rect& tmp)
{
	if (Function_Common::Impact(tmp, this->rect_,true))
		this->explosion = true;
}
void MainObject::test_input(SDL_Event &events)
{
	if (events.type == SDL_KEYDOWN)
	{
		std::cout << "KEYDOWN\n";
		switch (events.key.keysym.sym)
		{

		case SDLK_UP:
		case SDLK_w:
			y_val = -SPEED_MAIN;
			//y_val -= SPEED_MAIN;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			y_val = SPEED_MAIN;
			//	y_val += SPEED_MAIN;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			x_val = -SPEED_MAIN*2;
			//x_val -= SPEED_MAIN;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			x_val = SPEED_MAIN;
			//x_val += SPEED_MAIN;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		std::cout << "KEYUP\n";
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_w:
				//y_val += SPEED_MAIN;
				y_val = 0;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				//y_val -= SPEED_MAIN;
				y_val = 0;
				break;
			case SDLK_LEFT:
			case SDLK_a:
				//x_val += SPEED_MAIN;
				x_val = 0;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				//x_val -= SPEED_MAIN;
				x_val = 0;
				break;
			default:
				break;
			}
		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{

		BulletObject* p_amor = new BulletObject;
		switch (events.button.button)
		{
		case SDL_BUTTON_LEFT:
			std::cout << "LEFTDOWN\n";
			p_amor->Base_Loadtexture("amor2_laser.png");
			p_amor->set_type_amor(BulletObject::LASE);
			p_amor->set_rect_size();
			p_amor->Set_rect_pos(this->rect_.x + this->rect_.w, this->rect_.y + this->rect_.h / 2 - 1);
			p_amor->set_is_amor(true);
			p_amor->set_x_val_amor(SPEED_BULLET_MAIN);
			Mix_PlayChannel(-1, g_sound_bullet[0], 0);
			break;
		case SDL_BUTTON_RIGHT:
			std::cout << "RIGHDOWN\n";
			p_amor->Base_Loadtexture("amor1_cau.png");
			p_amor->set_type_amor(BulletObject::CAU);
			p_amor->set_rect_size();
			p_amor->Set_rect_pos(this->rect_.x + this->rect_.w - 5, this->rect_.y + this->rect_.h / 2 - 1);
			p_amor->set_x_val_amor(SPEED_BULLET_MAIN);
			p_amor->set_is_amor(true);
			Mix_PlayChannel(-1, g_sound_bullet[1], 0);
			break;
		default:
			break;
		}
		this->main_amor.push_back(p_amor);
	}
}

