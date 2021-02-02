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

_Bool level_end()
{
	if(!entities[0].alive) { draw(2); }

	hurt_frames=100;

	if(!entities[0].alive) { text_string("u ded boiiiiiiiiii", WIN_W/2-107, WIN_H/3, 255, 0, 0, 19); SDL_RenderPresent(rend); entities[0].lives--; if(sfx) { Mix_PlayChannel(-1, ded_sfx, 0); } SDL_Delay(2000); }

	if(entities[0].alive) { text_string("u r winnneeerrrrrr!!!11!11", WIN_W/2-155, WIN_H/3, 255, 0, 255, 26); SDL_RenderPresent(rend); SDL_Delay(2000); }

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);

	if(entities[0].alive && credits)
	{
		text_string("da end", WIN_W/2-35, WIN_H/3-44, 255, 0, 255, 6); SDL_RenderPresent(rend); SDL_Delay(2000);

		text_string("thanks for playing", WIN_W/2-107, WIN_H/3-22, 255, 0, 255, 18); SDL_RenderPresent(rend); SDL_Delay(2000);

		text_string("credits:", WIN_W/2-47, WIN_H/3+22, 255, 0, 255, 8); SDL_RenderPresent(rend); SDL_Delay(2000);
		text_string("art - zlayd", WIN_W/2-65, WIN_H/3+44, 255, 0, 255, 11); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("level design - zlayd", WIN_W/2-119, WIN_H/3+66, 255, 0, 255, 20); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("music - zlayd", WIN_W/2-77, WIN_H/3+88, 255, 0, 255, 13); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("programming - zlayd", WIN_W/2-113, WIN_H/3+110, 255, 0, 255, 19); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("sfx - zlayd", WIN_W/2-65, WIN_H/3+132, 255, 0, 255, 11); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("playtesting:", WIN_W/2-71, WIN_H/3+154, 255, 0, 255, 12); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("amy", WIN_W/2-17, WIN_H/3+176, 255, 0, 255, 3); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("chris", WIN_W/2-29, WIN_H/3+198, 255, 0, 255, 5); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("isa", WIN_W/2-17, WIN_H/3+220, 255, 0, 255, 3); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("mimi", WIN_W/2-23, WIN_H/3+242, 255, 0, 255, 4); SDL_RenderPresent(rend); SDL_Delay(500);
		text_string("zlayd", WIN_W/2-29, WIN_H/3+264, 255, 0, 255, 5); SDL_RenderPresent(rend); SDL_Delay(2000);
	}

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);
	SDL_Rect temp_rect = {WIN_W/2-30, WIN_H/2+5, 10, 20};
	SDL_RenderCopy(rend, player_tex, NULL, &temp_rect);
	text_int(entities[0].lives, WIN_W/2-16, WIN_H/2+5, 255, 255, 255, 3);

	/* Ded */
	if(entities[0].lives==0)
	{
		entities[0].lives=3;
		coins=0;
		ammo=10;
		SDL_RenderPresent(rend);
		SDL_Delay(2000);
		text_string("game over", WIN_W/2-54, WIN_H/2+25, 255, 255, 255, 9);
		SDL_RenderPresent(rend);
		if(sfx) { Mix_PlayChannel(-1, fuck_sfx, 0); }
		sprintf(next_level, "levels/lvl_1");
		sprintf(current_level, "levels/lvl_1");
		SDL_Delay(10000);
	}

	if(level_load  ()) { return 1; }
	text_string(level_proper_name, WIN_W/2-((level_proper_name_length*6)-1), WIN_H/2-25, 255, 255, 255, level_proper_name_length);
	SDL_RenderPresent(rend);
	SDL_Delay(2000);

	return 0;
}
