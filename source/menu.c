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

_Bool menu()
{
	if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); }
	_Bool fuckzzz=0;
	int selected = 0;
	_Bool color[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	entities[0].move_left=0;
	entities[0].move_right=0;

	int menu_h=WIN_H/3-20;
	int menu_s=20;
	_Bool right, left;

	mb=0;

	int timer=0;

	move_keyboard=0;

	while(!fuckzzz)
	{
		if(timer) { timer--; }

		left=0;
		right=0;

		draw(2);
		text_string("resume", WIN_W/2-36, menu_h, color[0]*255, 0, (!color[0])*255, 6);
		if(edit) { text_string("editing level", WIN_W/2-78, menu_h+menu_s, color[1]*255, 0, (!color[1])*255, 13); } else { text_string("edit level", WIN_W/2-60, menu_h+menu_s, color[1]*255, 0, (!color[1])*255, 10); }
		if(fullscreen) { text_string("fullscreen <on>", WIN_W/2-90, menu_h+menu_s*2, color[2]*255, 0, (!color[2])*255, 15); } else { text_string("fullscreen <off>", WIN_W/2-96, menu_h+menu_s*2, color[2]*255, 0, (!color[2])*255, 16); }

		char res[11];
		sprintf(res, "res: %dp", WIN_H);
		int res_chars = 9;
		if(WIN_H==1080 || WIN_H==1440) { res_chars=10; }
		text_string(res, WIN_W/2-(res_chars*6), menu_h+menu_s*3, color[3]*255, 0, (!color[3])*255, res_chars);

		if(!Mix_PausedMusic()) { text_string("music <on>", WIN_W/2-60, menu_h+menu_s*4, color[4]*255, 0, (!color[4])*255, 10); } else { text_string("music <off>", WIN_W/2-66, menu_h+menu_s*4, color[4]*255, 0, (!color[4])*255, 11); }
		if(sfx) { text_string("sfx <on>", WIN_W/2-48, menu_h+menu_s*5, color[5]*255, 0, (!color[5])*255, 8); } else { text_string("sfx <off>", WIN_W/2-54, menu_h+menu_s*5, color[5]*255, 0, (!color[5])*255, 9); }
		text_string("music volume: ", WIN_W/2-102, menu_h+menu_s*6, color[6]*255, 0, (!color[6])*255, 14); text_int(vol_music, WIN_W/2+84, menu_h+menu_s*6, color[6]*255, 0, (!color[6])*255, 3);
		text_string("sfx volume: ", WIN_W/2-90, menu_h+menu_s*7, color[7]*255, 0, (!color[7])*255, 12); text_int(vol_sfx, WIN_W/2+72, menu_h+menu_s*7, color[7]*255, 0, (!color[7])*255, 3);
		if(rec) { text_string("recording demo", WIN_W/2-84, menu_h+menu_s*8, color[8]*255, 0, (!color[8])*255, 14); } else { text_string("record demo", WIN_W/2-66, menu_h+menu_s*8, color[8]*255, 0, (!color[8])*255, 11); }
		if(play) { text_string("playing demo", WIN_W/2-72, menu_h+menu_s*9, color[9]*255, 0, (!color[9])*255, 12); } else { text_string("play demo", WIN_W/2-54, menu_h+menu_s*9, color[9]*255, 0, (!color[9])*255, 9); }
		text_string("quit", WIN_W/2-24, menu_h+menu_s*10, color[10]*255, 0, (!color[10])*255, 4);

		if(edit)
		{
			text_string("load level", WIN_W/2-60, menu_h+menu_s*11, color[11]*255, 0, (!color[11])*255, 10);
			text_string("save level", WIN_W/2-60, menu_h+menu_s*12, color[12]*255, 0, (!color[12])*255, 10);
			text_string("new level", WIN_W/2-54, menu_h+menu_s*13, color[13]*255, 0, (!color[13])*255, 9);
			if(level_type==0) { text_string("level type: noon", WIN_W/2-96, menu_h+menu_s*14, color[14]*255, 0, (!color[14])*255, 16); }
			else if(level_type==1) { text_string("level type: sunset", WIN_W/2-108, menu_h+menu_s*14, color[14]*255, 0, (!color[14])*255, 18); }
			else if(level_type==2) { text_string("level type: night", WIN_W/2-102, menu_h+menu_s*14, color[14]*255, 0, (!color[14])*255, 17); }
			else { text_string("level type: hell", WIN_W/2-96, menu_h+menu_s*14, color[14]*255, 0, (!color[14])*255, 16); }
			text_string("randomize clouds", WIN_W/2-96, menu_h+menu_s*15, color[15]*255, 0, (!color[15])*255, 16);
		}
		SDL_RenderPresent(rend);

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(gamepad)
			{
				if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_START)) { fuckzzz=1; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } }
				if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_LEFT) && !timer) { timer=10; left=1; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } }
				if((SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_A)) && !timer) { timer=10; right=1; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } }
				if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_UP)) { color[selected]=0; if(selected>0){selected--;} else if(edit) { selected=15; } else{selected=10;} color[selected]=255; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } }
				if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) { color[selected]=0; if(selected<10 || (edit && selected<15)) { selected++; } else {selected=0;} color[selected]=255; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } }
			}
			switch(event.type)
			{
				case SDL_QUIT: fuckzzz=1; quit = 1; break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.scancode)
					{
						case SDL_SCANCODE_ESCAPE: fuckzzz=1; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } break;

						case SDL_SCANCODE_A: case SDL_SCANCODE_LEFT: left=1; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } break;
						case SDL_SCANCODE_RETURN: case SDL_SCANCODE_SPACE: case SDL_SCANCODE_D: case SDL_SCANCODE_RIGHT: right=1; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } break;

						case SDL_SCANCODE_W: case SDL_SCANCODE_UP: color[selected]=0; if(selected>0){selected--;} else if(edit) { selected=15; } else{selected=10;} color[selected]=255; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } break;
						case SDL_SCANCODE_S: case SDL_SCANCODE_DOWN: color[selected]=0; if(selected<10 || (edit && selected<15)) { selected++; } else {selected=0;} color[selected]=255; if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); } break;

						default: /* no u */ break;
					}
					break;
				default: /* no uuuuuuuuuuuuuuuuuuuuuuuuuuuu*/ break;
			}
		}

		if(left || right)
		{
			switch(selected)
			{
				case 0: fuckzzz=1; break;
				case 1: if(edit) { edit=0; } else if(!rec && !play) { edit=1; for(int x=0; x<level_length; x++) { for(int y=0; y<level_height; y++) { if(blocks[x][y]>100) { blocks[x][y]-=100; } } } } break;
				case 2: if(!fullscreen){fullscreen=SDL_WINDOW_FULLSCREEN_DESKTOP;}else{fullscreen=0;} SDL_SetWindowFullscreen(win, fullscreen); break;
				case 3: if(!rec && !play) { if(left) { switch(WIN_H) { case 1440: WIN_W=1920; WIN_H=1080; break; case 1080: WIN_W=1600; WIN_H=900; break; case 900: WIN_W=1280; WIN_H=720; break; case 720: WIN_W=640; WIN_H=480; break; default: break; } } else { switch(WIN_H) { case 480: WIN_W=1280; WIN_H=720; break; case 720: WIN_W=1600; WIN_H=900; break; case 900: WIN_W=1920; WIN_H=1080; break; case 1080: WIN_W=2560; WIN_H=1440; break; default: break; } } SDL_RenderSetLogicalSize(rend, WIN_W, WIN_H); SDL_SetWindowSize(win, WIN_W, WIN_H); block_rect.x=-(entities[0].rect.x+entities[0].rect.w/2-WIN_W/2); if(block_rect.x>0){block_rect.x=0;} block_rect.y=-(entities[0].rect.y+entities[0].rect.h/2-WIN_H/2); if(block_rect.y<WIN_H-60){block_rect.y=WIN_H-60;} sky_rect.w=WIN_W; sky_rect.h=WIN_H; } break;
				case 4: if(Mix_PausedMusic()) { play_music(level_type); } else { Mix_PauseMusic(); } break;
				case 5: if(sfx) { sfx=0; } else { sfx=1; } break;
				case 6: if(left) {if(vol_music>0){vol_music--;}}else {if(vol_music<MIX_MAX_VOLUME){vol_music++;}} Mix_VolumeMusic(vol_music); break;
				case 7: if(left) {if(vol_sfx>0){vol_sfx--;}}else {if(vol_sfx<MIX_MAX_VOLUME){vol_sfx++;}} Mix_Volume(-1, vol_sfx); break;
				case 8: if(rec) { demo(3); } else if(!play) { edit=0; if(demo(0)) { return 1; } } break;
				case 9: if(play) { demo(3); } else if(!rec) { edit=0; if(demo(1)) { draw(2); text_string("illegal demo", WIN_W/2-72, WIN_H/4-10, 0, 0, 0, 12); SDL_RenderPresent(rend); SDL_Delay(2000); } } break;
				case 10: fuckzzz=1; quit=1; break;

				case 11: sprintf(input_message, "enter level name"); if(text_input_string(0)) { break; } sprintf(next_level, "levels/%s", input_string); if(level_load  ()) { text_string("illegal level", 250, 160, 0, 0, 0, 13); SDL_RenderPresent(rend); SDL_Delay(1000); } break;
				case 12: level_save(); break;
				case 13: for(int i=0; i<BLOCKS_X; i++) { for(int j=0; j<BLOCKS_Y; j++) { blocks[i][j]=0; } } for(int x=1; x<ENTITIES; x++) { entities[x].alive=0; } for(int z=0; z<DECALS; z++) { decals[z].active=0; } break;
				case 14: if(left) {if(level_type>0){level_type--;if(!Mix_PausedMusic()){play_music(level_type);}}}else {if(level_type<3){level_type++;if(!Mix_PausedMusic()){play_music(level_type);}}} item_anim=0; break;
				case 15: for(int z=0; z<DECALS/2; z++) { if(z<15) { decals[z].active=1; decals[z].passport=0; decals[z].block=0; decals[z].rect.w=100; decals[z].rect.h=100; decals[z].rect.x=rand()%(BLOCKS_X*30); decals[z].rect.y=rand()%400; decals[z].parallax=((double)(rand()%40)/(double)10)+1.1F; } else { decals[z].active=0; } } break;

				default: printf("this is an error!\n"); break;
			}
			if(sfx) { Mix_PlayChannel(-1, keyboard_sfx, 0); }
		}
	}
	return 0;
}
