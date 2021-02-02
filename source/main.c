/*
	Copyright 2021 Xavier "Zlayd" Allegretta

	This file is part of Shrep.

	Shrep is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Shrep is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Shrep.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "main.h"

//vars
//SDL misc
SDL_Window* win;
SDL_Renderer* rend;
SDL_Texture* hud_tex_b;
SDL_Texture* hud_tex_y;
SDL_Texture* player_tex;
SDL_Texture* player_tex2;
SDL_Texture* player_tex3;
SDL_Texture* umm_tex;
SDL_Texture* stoncc_tex;
SDL_Texture* melon_tex;
SDL_Texture* brick_tex;
SDL_Texture* grass_tex;
SDL_Texture* dirt_tex;
SDL_Texture* sky_tex;
SDL_Texture* sky_noon_tex;
SDL_Texture* sky_night_tex;
SDL_Texture* sky_hell_tex;
SDL_Texture* sun_tex;
SDL_Texture* moon_tex;
SDL_Texture* coin_tex;
SDL_Texture* ammo_tex;
SDL_Texture* dew_tex;
SDL_Texture* tos_tex;
SDL_Texture* tos_dark_tex;
SDL_Texture* os_tex;
SDL_Texture* os_dark_tex;
SDL_Texture* fire_tex;
SDL_Texture* cloud_tex;
SDL_Texture* tomb_tex;
SDL_Texture* nuke_tex;
Mix_Music* mus1=0;
Mix_Music* mus2=0;
Mix_Music* mus3=0;
Mix_Music* mus4=0;
Mix_Chunk* shoot_sfx=0;
Mix_Chunk* tos_sfx=0;
Mix_Chunk* dew_sfx=0;
Mix_Chunk* coin_sfx=0;
Mix_Chunk* bullet_sfx=0;
Mix_Chunk* hurt_sfx=0;
Mix_Chunk* jump_sfx=0;
Mix_Chunk* ded_sfx=0;
Mix_Chunk* fuck_sfx=0;
Mix_Chunk* keyboard_sfx=0;
Mix_Chunk* nuke_sfx=0;
SDL_GameController* gamepad = 0;
int WIN_W = 1280;
int WIN_H = 720;
uint32_t fullscreen = 0;
SDL_Rect sky_rect = {0, 0, 1920, 1080};
SDL_Rect fire_rect = {0, 0, 14, 14};

_Bool ls = 0;
_Bool rs = 0;

//ents
struct ent entities[ENTITIES];
struct decal decals[DECALS];

//block vars
SDL_Rect block_rect;
int level_length;
int level_height;
uint8_t blocks[BLOCKS_X][BLOCKS_Y];

//misc
uint8_t edit_id=3;
_Bool mb;
int mpos_x = 0;
int mpos_y = 0;
_Bool edit = 0;
_Bool quit;
_Bool input;
char input_string[21];
char next_level[30] = "levels/lvl_1";
char current_level[30] = "levels/lvl_1";
char input_message[30];
char demo_name[21];
char level_proper_name[21];
int level_proper_name_length;
int level_type=0;
int coins = 0;
_Bool rec = 0;
_Bool play = 0;
FILE* demo_file;
uint8_t dew = 0;
uint8_t item_anim = 0;
int item_angle = 20;
uint8_t hurt_frames = 100;
_Bool sfx=1;
int vol_sfx=MIX_MAX_VOLUME/8;
int vol_music=MIX_MAX_VOLUME/4;

time_t seed;
int rec_frames=1;
int ammo = 10;
int os = 0;
_Bool fire_o = 0;
_Bool move_gamepad = 0;
_Bool move_keyboard = 0;
_Bool credits = 0;
_Bool seen_disclaimer=0;

int main()
{
	if(init()) { quit_game(); return 1; }
	if(level_load()) { quit_game(); return 1; }

	options(0);

	draw(0);

	clock_t start=0;

	int ms=10;

	//epilepsy warning
	for(int i=0; i<500; i++)
	{
		//draw warning
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderClear(rend);
		text_string("warning:", WIN_W/2-47, WIN_H/3, 255, 0, 0, 8);
		text_string("shrep may cause epileptic seizures", WIN_W/2-203, WIN_H/3+44, 255, 255, 255, 34);
		text_string("in some individuals", WIN_W/2-113, WIN_H/3+66, 255, 255, 255, 19);
		text_string("play at your own risk", WIN_W/2-125, WIN_H/3+110, 255, 255, 255, 21);
		text_string("press escape to quit", WIN_W/2-119, WIN_H/3+154, 255, 255, 255, 20);
		if(!seen_disclaimer) { text_string("wait a couple seconds to start", WIN_W/2-179, WIN_H/3+176, 255, 255, 255, 30); }
		else { text_string("press space to skip", WIN_W/2-113, WIN_H/3+176, 255, 255, 255, 19); }
		SDL_RenderPresent(rend);

		//input
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT || event.key.keysym.scancode==SDL_SCANCODE_ESCAPE) { quit_game(); return 0; }
			if(event.key.keysym.scancode==SDL_SCANCODE_SPACE && seen_disclaimer) { goto skip_warning; }
		}

		SDL_Delay(10);
	}
	seen_disclaimer=1;
	skip_warning:

	while(1)
	{
		start = clock();

		move();
		misc();

		if(events()) { quit_game(); return 1; }
		if(quit) { quit_game(); return 0; }
		if(play) { if(demo(2)) { quit_game(); return 1; } }

		if(entities[0].alive) { if(draw(1)) { quit_game(); return 1;} } else { if(level_end()) { quit_game(); return 1;} }

		ms=10-(((clock()-start)*(clock_t)100)/CLOCKS_PER_SEC);

		if(ms>0) { SDL_Delay(ms); }
		else { SDL_Delay(10); }
	}

	return 0;
}
