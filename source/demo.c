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

#include "funcs.h"

// options
// 0 - start recording
// 1 - start playing
// 2 - read ent data (call every iteration after playing has started)
// 3 - stop

_Bool demo(int option)
{
	if(option==0)
	{
		rec_frames=0;

		sprintf(input_message, "input demo name");
		if(text_input_string(0)) { return 0; }
		sprintf(next_level, "%s", current_level);
		rec=1;
		play=0;
		if(level_load()) { return 1; }
		char temp[30];
		sprintf(temp, "demos/%s", input_string);
		demo_file = fopen(temp, "w");
		if(!demo_file) { return 1; }
		seed = time(NULL);
		srand(seed);
		fprintf(demo_file, "%s %ld %d %d\n\n", current_level, seed, WIN_W, WIN_H);

		entities[0].alive=2;
	}
	else if(option==1)
	{
		sprintf(input_message, "input demo name");
		if(text_input_string(0)) { return 0; }
		rec=0;
		play=1;
		char temp[30];
		sprintf(temp, "demos/%s", input_string);
		demo_file = fopen(temp, "r");
		if(!demo_file) { return 1; }
		fscanf(demo_file, "%s", next_level);
		if(level_load()) { return 1; }
		int oldw=WIN_W, oldh=WIN_H;
		fscanf(demo_file, "%ld %d %d %d", &seed, &WIN_W, &WIN_H, &rec_frames);
		srand(seed);

		if((WIN_W!=640 && WIN_W!=1280 && WIN_W!=1600 && WIN_W!=1920 && WIN_W!=2560) || (WIN_H!=480 && WIN_H!=720 && WIN_H!=900 && WIN_H!=1080 && WIN_H!=1440)) { printf("%d %d\n", WIN_W, WIN_H); WIN_W=oldw; WIN_H=oldh; return 1; }

		if(WIN_W!=oldw && WIN_H!=oldh)
		{
			SDL_RenderSetLogicalSize(rend, WIN_W, WIN_H);
			SDL_SetWindowSize(win, WIN_W, WIN_H);
			block_rect.x=-(entities[0].rect.x+entities[0].rect.w/2-WIN_W/2);
			if(block_rect.x>0) { block_rect.x=0; }
			block_rect.y=-(entities[0].rect.y+entities[0].rect.h/2-WIN_H/2);
			if(block_rect.y<WIN_H-60) { block_rect.y=WIN_H-60; }
			sky_rect.w=WIN_W; sky_rect.h=WIN_H;
		}else if(WIN_W!=oldw || WIN_H!=oldh)
		{
			printf("what?\n");
			WIN_W=oldw;
			WIN_H=oldh;
			return 1;
		}

		hurt_frames=100;
		entities[0].alive=2;
	}
	else if(option==2)
	{
		if(play)
		{
			if(rec_frames) { rec_frames--; return 0; }

			int i=-1, j=-1, k=-1, l=-1, m=-1;

			fscanf(demo_file, "%d %d %d %d %d %d", &i, &j, &k, &l, &m, &rec_frames);
			if(i!=0 && i!=1) { goto end; }
			if(j!=0 && j!=1) { goto end; }
			if(k!=0 && k!=1) { goto end; }
			if(l!=0 && l!=1) { goto end; }
			if(m!=0 && m!=1) { goto end; }

			entities[0].move_left=(_Bool)i;
			if(i) { entities[0].dir=1; }
			entities[0].move_right=(_Bool)j;
			if(j) { entities[0].dir=0; }
			if(k && entities[0].block_distance_down==0) { entities[0].momentum_y=16; if(sfx) { Mix_PlayChannel(-1, jump_sfx, 0); } }
			entities[0].fired=(_Bool)l;
			fire_o=m;

			return 0;
		}else
		{
			return 1;
		}
		end:
		play=0;
		fclose(demo_file);
		entities[0].move_left=0;
		entities[0].move_right=0;
	}
	else if(option==3)
	{
		if(rec || play)
		{
			fclose(demo_file);
			if(play)
			{
				entities[0].move_left=0;
				entities[0].move_right=0;
			}
			rec=0;
			play=0;
		}else
		{
			return 1;
		}
	}

	return 0;
}
