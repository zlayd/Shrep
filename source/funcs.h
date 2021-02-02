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
extern SDL_Window* win;
extern SDL_Renderer* rend;
extern SDL_Texture* hud_tex_b;
extern SDL_Texture* hud_tex_y;
extern SDL_Texture* player_tex;
extern SDL_Texture* player_tex2;
extern SDL_Texture* player_tex3;
extern SDL_Texture* umm_tex;
extern SDL_Texture* stoncc_tex;
extern SDL_Texture* melon_tex;
extern SDL_Texture* brick_tex;
extern SDL_Texture* grass_tex;
extern SDL_Texture* dirt_tex;
extern SDL_Texture* sky_tex;
extern SDL_Texture* sky_noon_tex;
extern SDL_Texture* sky_night_tex;
extern SDL_Texture* sky_hell_tex;
extern SDL_Texture* sun_tex;
extern SDL_Texture* moon_tex;
extern SDL_Texture* coin_tex;
extern SDL_Texture* ammo_tex;
extern SDL_Texture* dew_tex;
extern SDL_Texture* tos_tex;
extern SDL_Texture* tos_dark_tex;
extern SDL_Texture* os_tex;
extern SDL_Texture* os_dark_tex;
extern SDL_Texture* fire_tex;
extern SDL_Texture* cloud_tex;
extern SDL_Texture* tomb_tex;
extern SDL_Texture* nuke_tex;
extern Mix_Music* mus1;
extern Mix_Music* mus2;
extern Mix_Music* mus3;
extern Mix_Music* mus4;
extern Mix_Chunk* shoot_sfx;
extern Mix_Chunk* tos_sfx;
extern Mix_Chunk* dew_sfx;
extern Mix_Chunk* coin_sfx;
extern Mix_Chunk* bullet_sfx;
extern Mix_Chunk* hurt_sfx;
extern Mix_Chunk* jump_sfx;
extern Mix_Chunk* ded_sfx;
extern Mix_Chunk* fuck_sfx;
extern Mix_Chunk* keyboard_sfx;
extern Mix_Chunk* nuke_sfx;
extern SDL_GameController* gamepad;
extern unsigned int WIN_W;
extern unsigned int WIN_H;
extern uint32_t fullscreen;
extern SDL_Rect sky_rect;
extern SDL_Rect fire_rect;

extern _Bool ls;
extern _Bool rs;

//ents
extern struct ent entities[ENTITIES];
extern struct decal decals[DECALS];

//block vars
extern SDL_Rect block_rect;
extern int level_length;
extern int level_height;
extern uint8_t blocks[BLOCKS_X][BLOCKS_Y];

//misc
extern uint8_t edit_id;
extern _Bool mb;
extern int mpos_x;
extern int mpos_y;
extern _Bool edit;
extern _Bool quit;
extern _Bool input;
extern char input_string[21];
extern char next_level[30];
extern char current_level[30];
extern char input_message[30];
extern char demo_name[21];
extern char level_proper_name[21];
extern int level_proper_name_length;
extern int level_type;
extern int coins;
extern _Bool rec;
extern _Bool play;
extern FILE* demo_file;
extern uint8_t dew;
extern uint8_t item_anim;
extern int item_angle;
extern uint8_t hurt_frames;
extern _Bool sfx;
extern int vol_sfx;
extern int vol_music;

extern time_t seed;
extern int rec_frames;
extern int ammo;
extern int os;
extern _Bool fire_o;
extern _Bool move_gamepad;
extern _Bool move_keyboard;
extern _Bool credits;
extern _Bool seen_disclaimer;
