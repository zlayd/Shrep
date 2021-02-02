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

// object PASSPORTS
// -1 - end of level
// 0 - nothing (how amazing)
// 1 - bricks
// 2 - coin
// 3 - grass
// 4 - umm? spawner
// 5 - mountain dew
// 6 - 'tos
// 7 - ammo
// 8 - dirt
// 9 - stoncc image spawner
// 10 - watermelon man spawner
// 11 - os
// 102 - collected coin
// 105 - collected mountain dew
// 106 - collected 'tos
// 107 - collected ammo
// 111 - collected os

_Bool level_load()
{
	FILE* block_reader;
	if(entities[0].alive) { block_reader=fopen(next_level, "r"); sprintf(current_level, "%s", next_level); }
	else { block_reader=fopen(current_level, "r"); entities[0].alive=2; }
	if(!block_reader) { printf("failed to load level\n"); return 1; }
	block_rect.x=0;
	block_rect.y=WIN_H-60;
	entities[0].rect.x=60;
	entities[0].rect.y=-135;
	entities[0].momentum_x=(float)0;
	entities[0].momentum_y=(float)0;
	for(int meme = 0 ; meme<BLOCKS_X ; meme++)
	{
		for(int memez = 0 ; memez<BLOCKS_Y ; memez++)
		{
			blocks[meme][memez]=0;
		}
	}
	for(int fug = 1 ; fug<ENTITIES ; fug++)
	{
		entities[fug].alive=0;
	}
	for(int money=0; money<DECALS; money++)
	{
		decals[money].active=0;
	}


	char epic[23];
	int oof=0;
	int i = 0;
	int j = 0;
	int x = 1;
	int z = 0;
	fscanf(block_reader, "%d %d %d %d %s", &level_length, &level_height, &level_type, &oof, epic);
	if(oof==0 || oof==1) { credits=oof; }
	else { return 1; }
	oof=0;
	if(level_length>BLOCKS_X) { level_length=BLOCKS_X; }
	if(level_height>BLOCKS_Y) { level_height=BLOCKS_Y; }
	sprintf(next_level, "levels/%s", epic);
	if(ammo<10){ammo=10;}
	level_proper_name_length=0;
	char temp;
	fscanf(block_reader, " %c", &temp);
	while(1)
	{
		fscanf(block_reader, "%c", &temp);
		if(temp=='"') { break; }
		else if(level_proper_name_length<20){ level_proper_name[level_proper_name_length]=temp; }
		else { printf("oof: level proper name too long"); return 1; }
		level_proper_name_length++;
	}
	level_proper_name[21]='\0';
	while(1)
	{
//		while(fgetc(block_reader)!='\n')
//		{
//			fgetc(block_reader);
//		}
		fscanf(block_reader, "%d", &i);
		if(i==-1) { break; }
		else if(i==-2 && z<DECALS) { decals[z].active=1; decals[z].block=0; fscanf(block_reader, "%d %d %d %d %lf %hhd", &decals[z].rect.x, &decals[z].rect.y, &decals[z].rect.w, &decals[z].rect.h, &decals[z].parallax, &decals[z].passport); z++; }
		else if(i==-3 && z<DECALS) { decals[z].active=1; decals[z].block=1; fscanf(block_reader, "%d %d %d %d %lf %hhd", &decals[z].block_x, &decals[z].block_y, &decals[z].rect.w, &decals[z].rect.h, &decals[z].parallax, &decals[z].passport); decals[z].rect.x=decals[z].block_x*60; decals[z].rect.y=decals[z].block_y*60; z++; }
		else if(i>=0) { fscanf(block_reader, "%d %d", &j, &oof); if(i<level_length && j<level_height) { blocks[i][j]=(uint8_t)oof; } else { return 1; } }
		if(oof==4) { entities[x].type=1; entities[x].alive=1; entities[x].rect.h=75; entities[x].rect.w=50; entities[x].rect.x=i*60+5; entities[x].rect.y=j*-60-15; entities[x].acceleration=0.05F; entities[x].max_speed=3.0F; x++; }
		if(oof==9) { entities[x].type=2; entities[x].alive=1; entities[x].rect.h=75; entities[x].rect.w=50; entities[x].rect.x=i*60+5; entities[x].rect.y=j*-60-15; entities[x].acceleration=0.1F; entities[x].max_speed=3.5F; x++; }
		if(oof==10) { entities[x].type=4; entities[x].alive=1; entities[x].rect.h=60; entities[x].rect.w=60; entities[x].rect.x=i*60+5; entities[x].rect.y=j*-60; entities[x].acceleration=0.1F; entities[x].max_speed=2.0F; x++; }
	}
/*	for(int z=0; z<DECALS; z++)
	{
		printf("z: %d, active: %d, block: %d, block_pos: %d, x: %d, y: %d, w: %d, h: %d, parallax: %lf, passport: %hhd\n", z, decals[z].active, decals[z].block, decals[z].block_pos, decals[z].rect.x, decals[z].rect.y, decals[z].rect.w, decals[z].rect.h, decals[z].parallax, decals[z].passport);
	}
*/	fclose(block_reader);

	if(!Mix_PausedMusic()) { Mix_FadeOutMusic(2000); SDL_Delay(3000); play_music(level_type); }

	item_anim=0;

	return 0;
}
