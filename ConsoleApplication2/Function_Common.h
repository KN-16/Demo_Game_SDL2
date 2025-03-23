#pragma once
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_events.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <SDL_ttf.h>
#include <ctime>
// BackGround:
const int BG_WIDTH = 2000;
const int BG_HEIGHT = 800;
extern SDL_Rect BG_;
extern SDL_Rect BG_2;
extern SDL_Texture* g_texture_background;
extern int BG_x;
//Screen:
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;
extern SDL_Window* g_screen ;
extern SDL_Renderer* g_rscreen ;
//Event: 
extern SDL_Event g_event;
//Sound:
extern Mix_Chunk* g_sound_exp[2];
extern Mix_Chunk* g_sound_bullet[2];
extern Mix_Music* g_sound_game;
//Function:
namespace Function_Common 
{
	bool Init(); // Intial ALL Subsystem
	SDL_Texture* optimize_load_image(std::string path); //Load image
	bool Apply_image(SDL_Texture* b,SDL_Rect * c); //Show image 
	void load_error();
	void Cleanup();
	void Move_BG();
	bool Impact(const SDL_Rect&,const SDL_Rect&,bool is_main);
	SDL_Texture* optimize_load_image_colorkey(std::string ,int, int, int);
}
