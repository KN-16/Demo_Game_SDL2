#include "Function_Common.h"
//Windows:
SDL_Window* g_screen = NULL;
SDL_Renderer* g_rscreen = NULL;
SDL_Texture* g_texture_background = NULL;
//Event:
SDL_Event g_event;
//BackGround:
SDL_Rect BG_;
SDL_Rect BG_2;
// Sound:
Mix_Chunk* g_sound_bullet[2] = {NULL,NULL};
Mix_Chunk* g_sound_exp[2] = {NULL,NULL};
Mix_Music* g_sound_game=NULL;
void Function_Common::load_error()
{
	std::cout << "Error: " << SDL_GetError();
}
bool Function_Common::Init()
{	// ALL SDL SUBSYSTEM
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		load_error();
		return true;
	}
	//TTF font
	if (TTF_Init() ==-1)
	{
		std::cout << TTF_GetError();
		return true;
	}
	// Sound
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << Mix_GetError();
		return true;
	}
	return false;
}
SDL_Texture* Function_Common::optimize_load_image(std::string path)
{
	SDL_Texture* kq = IMG_LoadTexture(g_rscreen, path.c_str());
	if (!kq) return NULL;
	return kq;
}
bool Function_Common::Apply_image(SDL_Texture* b, SDL_Rect* c)
{
	if (!b) return false;
	SDL_RenderCopy(g_rscreen, b, NULL, c);
	return true;
}
void Function_Common::Cleanup()
{
	if (g_screen)
	{
		SDL_DestroyWindow(g_screen);
		g_screen = NULL;
	}
	if (g_rscreen)
	{
		SDL_DestroyRenderer(g_rscreen);
		g_rscreen = NULL;
	}
	if (g_texture_background)
	{
		SDL_DestroyTexture(g_texture_background);

		g_texture_background = NULL;
	}
	if (g_sound_bullet[0])
	{
		Mix_FreeChunk(g_sound_bullet[0]);
		g_sound_bullet[0] = NULL;
	}
	if (g_sound_bullet[1])
	{	
		Mix_FreeChunk(g_sound_bullet[1]);
		g_sound_bullet[1] = NULL;
	}
	if (g_sound_exp[0])
	{
		Mix_FreeChunk(g_sound_exp[0]);
		g_sound_exp[0] = NULL;
	}
	if (g_sound_exp[1])
	{
		Mix_FreeChunk(g_sound_exp[1]);
		g_sound_exp[1] = NULL;
	}
	if (g_sound_game)
	{
		Mix_FreeMusic(g_sound_game);
		g_sound_game = NULL;
	}
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}
void Function_Common::Move_BG()
{
	BG_.x = BG_x;
	if (BG_x < -600)
	{
		if (BG_x <= -2000)
			BG_x = BG_.x=0;
		else 
		{
			Function_Common::Apply_image(g_texture_background, &BG_);
			BG_2.x = BG_x + BG_WIDTH;
			Function_Common::Apply_image(g_texture_background, &BG_2);
			BG_x -= 2;
			return;
		}
	}
		Function_Common::Apply_image(g_texture_background, &BG_);
		BG_x -= 2; //Speed up
}
// (Width and Height) of a<(Width and Height) of b ,Impact between amor and player 
bool Function_Common::Impact(const SDL_Rect& a,const SDL_Rect& b,bool is_main)
{
	int top_l_a_x = a.x, top_r_a_x = a.x + a.w - 1;
	int top_a_y = a.y, bottom_a_y = a.y + a.h - 1;
	int top_l_b_x = b.x, top_r_b_x = b.x + b.w - 1;
	int top_b_y = b.y, bottom_b_y = b.y + b.h - 1;
	if (!is_main)
	{
		if ((top_r_a_x >= top_l_b_x) && (top_r_a_x <= top_r_b_x))
		{
			if (top_a_y >= top_b_y && top_a_y <= bottom_b_y)
			{
				if (top_a_y <= top_b_y + b.h / 2 - 33)
				{
					if (top_r_a_x >= top_r_b_x - 16 && top_r_a_x <= top_r_b_x)
						return true;
				}
				else if (top_a_y <= top_b_y + b.h / 2 - 11)
				{
					if (top_r_a_x >= top_r_b_x - 42 && top_r_a_x <= top_r_b_x)
						return true;
				}
				else if (top_a_y <= top_b_y + b.h / 2 + 9)
				{
					if (top_r_a_x >= top_l_b_x && top_r_a_x <= top_r_b_x)
						return true;
				}
				else if (top_a_y <= top_b_y + b.h / 2 + 31)
				{
					if (top_r_a_x >= top_r_b_x - 42 && top_r_a_x <= top_r_b_x)
						return true;
				}
				else
					if (top_r_a_x >= top_r_b_x - 16 && top_r_a_x <= top_r_b_x)
						return true;
			}
		}
	else if (bottom_a_y >= top_b_y && bottom_a_y <= bottom_b_y)
		{
			if (bottom_a_y <= top_b_y + b.h / 2 - 33)
			{
				if (top_r_a_x >= top_r_b_x - 16 && top_r_a_x <= top_r_b_x)
					return true;
			}
			else if (bottom_a_y <= top_b_y + b.h / 2 - 11)
			{
				if (top_r_a_x >= top_r_b_x - 42 && top_r_a_x <= top_r_b_x)
					return true;
			}
			else if (bottom_a_y <= top_b_y + b.h / 2 + 9)
			{
				if (top_r_a_x >= top_l_b_x && top_r_a_x <= top_r_b_x)
					return true;
			}
			else if (bottom_a_y <= top_b_y + b.h / 2 + 31)
			{
				if (top_r_a_x >= top_r_b_x - 42 && top_r_a_x <= top_r_b_x)
					return true;
			}
			else
				if (top_r_a_x >= top_r_b_x - 16 && top_r_a_x <= top_r_b_x)
					return true;
		}
	}
	else 
		if ((top_l_a_x >= top_l_b_x) && (top_l_a_x <= top_r_b_x))
		{
			if (top_a_y >= top_b_y && top_a_y <= bottom_b_y)
			{
				if (top_a_y <= top_b_y + b.h / 2 - 33)
				{
					if (top_l_a_x <= top_l_b_x + 27 && top_l_a_x >= top_l_b_x)
						return true;
				}
				else if (top_a_y <= top_b_y + b.h / 2 - 11)
				{
					if (top_l_a_x <= top_l_b_x + 56 && top_l_a_x >= top_l_b_x)
						return true;
				}
				else if (top_a_y <= top_b_y + b.h / 2 + 9)
				{
					if (top_l_a_x >= top_l_b_x && top_l_a_x <= top_r_b_x)
						return true;
				}
				else if (top_a_y <= top_b_y + b.h / 2 + 31)
				{
					if (top_l_a_x <= top_l_b_x + 56 && top_l_a_x >= top_l_b_x)
						return true;
				}
				else
					if (top_l_a_x <= top_l_b_x + 27 && top_l_a_x >= top_l_b_x)
						return true;
			}
			else if (bottom_a_y >= top_b_y && bottom_a_y <= bottom_b_y)
			{
				if (bottom_a_y <= top_b_y + b.h / 2 - 33)
				{
					if (top_l_a_x <= top_l_b_x + 27 && top_l_a_x >= top_l_b_x)
						return true;
				}
				else if (bottom_a_y <= top_b_y + b.h / 2 - 11)
				{
					if (top_l_a_x <= top_l_b_x + 56 && top_l_a_x >= top_l_b_x)
						return true;
				}
				else if (bottom_a_y <= top_b_y + b.h / 2 + 9)
				{
					if (top_l_a_x >= top_l_b_x && top_l_a_x <= top_r_b_x)
						return true;
				}
				else if (bottom_a_y <= top_b_y + b.h / 2 + 31)
				{
					if (top_l_a_x <= top_l_b_x + 56 && top_l_a_x >= top_l_b_x)
						return true;
				}
				else
					if (top_l_a_x <= top_l_b_x + 27 && top_l_a_x >= top_l_b_x)
						return true;
			}
		}
	return false ;
}
SDL_Texture* Function_Common::optimize_load_image_colorkey(std::string path,int red, int green, int blue)
{
	SDL_Surface* tmp = IMG_Load(path.c_str());
	if (!tmp) return NULL;
	SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, red, green, blue));
	SDL_Texture* tmp1 = SDL_CreateTextureFromSurface(g_rscreen, tmp);
	SDL_FreeSurface(tmp);
	tmp = NULL;
	return tmp1;
}
