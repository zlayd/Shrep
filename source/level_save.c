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

_Bool level_save()
{
	//get level name
	strncpy(input_message, "enter level name", 30);
	if(text_input_string(0)) { return 1; }
	char fuck[40]="skfoiahifgiadhgiuaw";
	sprintf(fuck, "levels/%s",input_string);
	//get level proper name
	strncpy(input_message, "enter level proper name", 30);
	if(text_input_string(1)) { return 1; }
	char shit_name[21];
	sprintf(shit_name, "%s",input_string);
	//get following level
	strncpy(input_message, "enter next level name", 30);
	if(text_input_string(0)) { return 1; }
	FILE* block_writer=fopen(fuck, "w");

	for(int i=0 ; i<BLOCKS_X ; i++)
	{
		for(int j=0 ; j<BLOCKS_Y ; j++)
		{
			if(blocks[i][j]>100) { blocks[i][j]-=100; }
		}
	}

	int i = 0;
	int j = 0;
	fprintf(block_writer, "%d %d %d %d %s \"%s\"\n\n", level_length, level_height, level_type, credits, input_string, shit_name);

	for(int z=0; z<DECALS; z++)
	{
		if(decals[z].passport!=1)
		{
			if(decals[z].active && !decals[z].block) { fprintf(block_writer, "-2 %d %d %d %d %lf %hhd\n", decals[z].rect.x, decals[z].rect.y, decals[z].rect.w, decals[z].rect.h, decals[z].parallax, decals[z].passport); }
			else if(decals[z].active && decals[z].block) { fprintf(block_writer, "-3 %d %d %d %d %lf %hhd\n", decals[z].block_x, decals[z].block_y, decals[z].rect.w, decals[z].rect.h, decals[z].parallax, decals[z].passport); }
		}
	}

	while(i<level_length)
	{
		while(j<level_height)
		{
			if(blocks[i][j]!=0)
			{
				fprintf(block_writer, "%d %d %d\n", i, j, blocks[i][j]);
			}
			j++;
		}
		j=0;
		i++;
	}
	draw(1);
	SDL_Delay(1000);
	fprintf(block_writer, "\n-1\n");
	fclose(block_writer);
	return 0;
}

