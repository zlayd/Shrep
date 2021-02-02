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

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

//#define WIN_W 1920
//#define WIN_H 1080
#define DECALS 30
#define ENTITIES 100
#define BLOCKS_X 200
#define BLOCKS_Y 15

struct ent {
	SDL_Rect rect;
	int lives;
	_Bool move_left, move_right, dir;
	float momentum_x, momentum_y;
	uint8_t alive;
	uint8_t type;
	int block_distance_right;
	int block_distance_up;
	int block_distance_down;
	int block_distance_left;
	float acceleration;
	float max_speed;
	_Bool fired;
	uint8_t anim;
	uint8_t anim_frame;
};

struct decal {
	_Bool active;
	SDL_Rect rect;
	uint8_t passport; //a.k.a. id a.k.a. type a.k.a. which image to draw
	double parallax;
	_Bool block;
	int block_x;
	int block_y;
};

_Bool level_save();

_Bool level_end();

_Bool text_int(int num, int x, int y, int r, int g, int b, int digits);

_Bool text_string(char string[], int x, int y, int r, int g, int b, int chars);

_Bool init();

_Bool level_load  ();

_Bool events();

void move();

_Bool text_input_string(_Bool spaces);

void misc();

_Bool draw(int actually_draw);

void quit_game();

_Bool menu();

_Bool options(_Bool mode);

void play_music(int music);

_Bool demo(int options);
