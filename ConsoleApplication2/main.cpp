#include "Function_Common.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "BulletObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
int BG_x = 0;
int main(int arc, char* arcv[])
{
	srand(time(NULL));
	//Intial Subsystem
	if (Function_Common::Init()) return 0;
	
	//Screen
	g_screen = SDL_CreateWindow("Game DEMO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!g_screen)
	{
		Function_Common::load_error();
		return 0;
	}
	g_rscreen = SDL_CreateRenderer(g_screen, -1, SDL_RENDERER_TARGETTEXTURE);
		if (!g_rscreen)
		{
			Function_Common::load_error();
			return 0;
		}
	//Sound of game
	g_sound_exp[0] = Mix_LoadWAV("Explosion_main.wav");
	if (!g_sound_exp[0])
	{
		std::cout << Mix_GetError(); return 0;
	}
	g_sound_exp[1] = Mix_LoadWAV("Explosion_threat.wav");
	if (!g_sound_exp[1])
	{
		std::cout << Mix_GetError(); return 0;
	}
	g_sound_bullet[0] = Mix_LoadWAV("laser.wav");
	if (!g_sound_bullet[0])
	{
		std::cout << Mix_GetError(); return 0;
	}
	g_sound_bullet[1] = Mix_LoadWAV("cau.wav");
	if (!g_sound_bullet[1])
	{
		std::cout << Mix_GetError(); return 0;
	}
	g_sound_game = Mix_LoadMUS("playgame.wav");
	if (!g_sound_game)
	{
		std::cout << Mix_GetError();
		return 0;
	}

	//BackGround
	g_texture_background = Function_Common::optimize_load_image("bground.jpg");
		if (!Function_Common::Apply_image(g_texture_background, NULL))
	{
		Function_Common::load_error();
		return 0;
	}
	BG_.x = BG_2.x = 0;
	BG_.y = BG_2.y = 0;
	BG_.w = BG_2.w = BG_WIDTH;
	BG_.h = BG_2.h = BG_HEIGHT; 
	
		//Intial MainObject		
	MainObject Main_Object;
	std::invoke([&Main_Object]() 
		{
		if (!Main_Object.Base_Loadtexture("Main.png"))				//load figure
		{
			Function_Common::load_error();
			return 0;
		}
		Main_Object.Set_rect_pos(200, 300);
		if (!Main_Object.Base_Show())
		{
			Function_Common::load_error();
			return 0;
		}   
		Main_Object.getr_hp_main().set_hp(9);
		}); 
	
	// Intial Explosion of main and threat
	ExplosionObject exp_main, exp_threat;
	std::invoke([&exp_main, &exp_threat]()
		{exp_main.Set_texture_exp("exp_main.png", 0, 255, 255);
	exp_main.Set_flame_frame(4);
	exp_main.Set_size_per_frame(165, 165);
	exp_threat.Set_texture_exp("exp_threat.png", 0, 255, 255);
	exp_threat.Set_flame_frame(4);
	exp_threat.Set_size_per_frame(165, 165);
		} );
	
	// Intial font 
	TTF_Font* font1 = NULL;
	TTF_Font* font2 = NULL;
	font1 = TTF_OpenFont("Font1.ttf", 25);
		if (font1==NULL)
		{
			std::cout << TTF_GetError();
			return 0;
		}
	font2 = TTF_OpenFont("Font2.ttf", 20);
	if (font2 == NULL) 
	{
		std::cout << TTF_GetError();
		return 0;
	}
	//Intial TextObject
		TextObject mark_1, mark_2, mark_3;
		mark_1.set_str("SCORES: ");
		mark_2.set_str("HIGHSCORE: ");
		mark_3.set_str("TIME: ");
		mark_1.set_color(TextObject::White);
		mark_2.set_color(TextObject::Red);
		mark_3.set_color(TextObject::Yellow);
		mark_1.Set_rect_pos(200, 300);
	//Intial Threat
	int NumberMax_of_Threat = 2;
	std::vector<ThreatObject*> ThreatObject_;
	//Run game
	std::vector<int> rect_y_threat;
	bool is_run = true, t = 0;
	bool is_key_up = false;
	Mix_PlayMusic(g_sound_game, -1);
	while (is_run)
	{	
		while (ThreatObject_.size() < NumberMax_of_Threat)
		{	
			ThreatObject* tmp = new ThreatObject;
			tmp->Set_x_val(SPEED_THREAT);	//speed of Threat
			tmp->getr_hp_threat().set_hp(2); // Set hp for Threat 
			for (int i=0;i<rect_y_threat.size();i++)
				if (((tmp->get_rect_y() <= rect_y_threat[i] + THREAT_HEIGHT - 1) && (tmp->get_rect_y() >= rect_y_threat[i]))||(tmp->get_rect_y()+ THREAT_HEIGHT-1<= rect_y_threat[i] + THREAT_HEIGHT - 1&& tmp->get_rect_y() + THREAT_HEIGHT - 1>= rect_y_threat[i] ))
					{
						tmp->Set_rect_pos(tmp->get_rect_x(), rand() % (SCREEN_HEIGHT - THREAT_HEIGHT));
						i = -1;
					}
			rect_y_threat.push_back(tmp->get_rect_y());
			ThreatObject_.push_back(tmp);	
		}
		for (int i = 0; i < ThreatObject_.size(); i++)
		{
			ThreatObject* tmp = ThreatObject_.at(i);
			if (tmp)
			{
				if (!tmp->explosion)
				{
					tmp->Threat_Move();
					if (tmp->get_threat_die())
					{
						delete tmp;
						tmp = NULL;
						ThreatObject_.erase(ThreatObject_.begin() + i);
						rect_y_threat.erase(rect_y_threat.begin() + i);
						i--;
					}
					else
					{
						ThreatObject_[i]->Threat_Amor_Action();
						for (auto& x : Main_Object.main_amor)
						{
							if (x && x->get_is_amor())
								tmp->Threat_Impact(x->get_rect());
							if (tmp->explosion)
							{	x->set_is_amor(false);
							if (tmp->getr_hp_threat().getr_hp()>1)
							{
								tmp->explosion = false;
								tmp->getr_hp_threat().getr_hp()--;
							}
							else break;
							}
						}
					}
				}
				else
				{
					if (tmp->explosion_frame == 4)
					{
						if (!tmp->threat_amor.size())
						{

							delete tmp;
							tmp = NULL;
							ThreatObject_.erase(ThreatObject_.begin() + i);
							rect_y_threat.erase(rect_y_threat.begin() + i);
							i--;
						}
					}
				}
			}
			else
			{
				ThreatObject_.erase(ThreatObject_.begin() + i);
				rect_y_threat.erase(rect_y_threat.begin() + i);
				i--;

			}
		}
		for (int i = 0; i < ThreatObject_.size(); i++)
		{
			if (ThreatObject_[i])
			{
				ThreatObject_[i]->Threat_Amor_Move();
				for (auto& x : ThreatObject_[i]->threat_amor)
				{
					if (Main_Object.explosion)
						break;
					if (x && x->get_is_amor())
						Main_Object.Main_Impact(x->get_rect());
					if (Main_Object.explosion)
					{
						x->set_is_amor(false);
						if (Main_Object.getr_hp_main().getr_hp()>1)
						{
							Main_Object.getr_hp_main().getr_hp()--;	
							Main_Object.explosion = false;
						}
					}
				}
			}
		}
		if (!Main_Object.explosion)
			while (SDL_PollEvent(&g_event))
			{
				if (g_event.type == SDL_QUIT)
				{
					is_run = 0;
					break;
				}
				Main_Object.MainObject_MoveAction(g_event);
				if (g_event.type == SDL_KEYUP)
					is_key_up = true;
			}
		mark_1.Create_text(font1, "ASD");
		Function_Common::Move_BG(); //-----------------------
		Main_Object.getr_hp_main().hp_show();
		for (auto& x : ThreatObject_)
		{
			if (x)
			{
				if (!x->explosion)
					x->Base_Show();
				if ((x->explosion) && (x->explosion_frame < 4))
				{if (!x->exp_sound)
				{
					Mix_PlayChannel(2, g_sound_exp[1], 0);
					x->exp_sound = true;
				}
					exp_threat.load_explosion(x->get_rect_x(), x->get_rect_y(), x->explosion_frame);
					x->explosion_frame++;
				}
				x->Threat_Amor_Show();
			}
		}
		if (!Main_Object.explosion)
		{
			if (is_key_up)
			{
				while (SDL_PollEvent(&g_event))
				{
					if (g_event.type == SDL_QUIT)
					{
						is_run = 0;
						break;
					}
					Main_Object.test_input(g_event);
				}
			}
			if (!Main_Object.MainObject_Move())
			{
				Function_Common::load_error();
				return 0;
			}
		}
		else
		{
			if (Main_Object.explosion_frame == 4)
			{
				if (!Main_Object.main_amor.size())
					return 0;
			} //game over
			else
			{
				if (!Main_Object.exp_sound)
				{
					Mix_PlayChannel(2, g_sound_exp[0], 0);
					Main_Object.exp_sound = true;
				}

				exp_main.load_explosion(Main_Object.get_rect_x(), Main_Object.get_rect_y(), Main_Object.explosion_frame);
				Main_Object.explosion_frame++;
			}
		}
		Main_Object.Main_Amor_Action();
		SDL_RenderPresent(g_rscreen);
		SDL_Delay(15); //FPS
		is_key_up = false;
		std::cout << "\n";
}
	
	Function_Common::Cleanup();
	return 0;
}

