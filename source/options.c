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

_Bool options(_Bool mode) {
	/* load options */
	FILE* options;
	if(!mode)
	{
		options=fopen(".options", "r");
		if(!options) { Mix_Volume(-1, vol_sfx); printf("No options file\nCreating...\n"); goto shit; }
		int temp1=-1, temp2=-1, temp3=-1, temp4=-1, temp5=-1, temp6=-1, temp7=-1, temp8=-1;
		fscanf(options, "%d %d %d %d %d %d %d %d", &temp1, &temp2, &temp3, &temp4, &temp5, &temp6, &temp7, &temp8);
		if((temp1!=0 && temp1!=1) || (temp2!=0 && temp2!=1) || (temp3!=0 && temp3!=1) || temp4<0 || temp4>MIX_MAX_VOLUME || temp5<0 || temp5>MIX_MAX_VOLUME || !(temp6==2560 || temp6==1920 || temp6==1600 || temp6==1280 || temp6==640) || !(temp7==1440 || temp7==1080 || temp7==900 || temp7==720 || temp7==480) || (temp8!=0 && temp8!=1)) { fclose(options); printf("Illegal options file\nReplacing...\n"); goto shit; }

		block_rect.y-=WIN_H;
		WIN_W=temp6;
		WIN_H=temp7;
		block_rect.y+=WIN_H;
		SDL_RenderSetLogicalSize(rend, WIN_W, WIN_H);
		SDL_SetWindowSize(win, WIN_W, WIN_H);
		sky_rect.w=WIN_W;
		sky_rect.h=WIN_H;

		if(temp1) { fullscreen=SDL_WINDOW_FULLSCREEN_DESKTOP; } else { fullscreen=0; }
		SDL_SetWindowFullscreen(win, fullscreen);
		if(!temp2) { Mix_PauseMusic(); } else if(Mix_PausedMusic()) { Mix_ResumeMusic(); }
		sfx=temp3;
		vol_sfx=temp4;
		vol_music=temp5;
		seen_disclaimer=temp8;
	}else
	{
		shit:
		options=fopen(".options", "w");
		int temp=0;
		if(fullscreen==SDL_WINDOW_FULLSCREEN_DESKTOP) { temp=1; }
		fprintf(options, "%d ", temp);
		if(Mix_PausedMusic()) { temp=0; } else{ temp=1; }
		fprintf(options, "%d %d %d %d %d %d %d\n", temp, sfx, vol_sfx, vol_music, WIN_W, WIN_H, seen_disclaimer);
	}
	Mix_Volume(-1, vol_sfx);
	Mix_VolumeMusic(vol_music);

	fclose(options);
	return 0;
}
