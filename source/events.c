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

_Bool events()
{
	_Bool record_data = 0;
	_Bool jump = 0;

	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		//gamepad
		if(gamepad)
		{
			move_gamepad=0;
			if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_A) && (edit || entities[0].block_distance_down==0) && !play) { entities[0].momentum_y=16; if(sfx) { Mix_PlayChannel(-1, jump_sfx, 0); } record_data = 1; jump = 1; }
			if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_X) && !edit && ammo && !entities[0].fired && !play) { entities[0].fired=1; ammo--; record_data=1; }
			if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_B) && !edit && os && !fire_o && !play) { fire_o=1; os--; record_data=1; }
			if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_LEFT) && !play) { entities[0].move_left=1; entities[0].dir=1; record_data=1; move_gamepad=1; }
			if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) && !play) { entities[0].move_right=1; entities[0].dir=0; record_data=1; move_gamepad=1; }
			if(SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_START)) { menu(); }
			if(!move_gamepad && !move_keyboard) { entities[0].move_left=0; entities[0].move_right=0; }
		}

		//mouse
		mb=0;
		if((SDL_GetMouseState(&mpos_x, &mpos_y) & SDL_BUTTON(SDL_BUTTON_LEFT)) && !edit && ammo && !entities[0].fired) { entities[0].fired=1; ammo--; }
		if((SDL_GetMouseState(&mpos_x, &mpos_y) & SDL_BUTTON(SDL_BUTTON_RIGHT)) && !edit && os && !fire_o) { fire_o=1; os--; }
		else if(SDL_GetMouseState(&mpos_x, &mpos_y)) { mb=1; }

		//keyboard
		switch(event.type)
		{
			case SDL_QUIT: quit = 1; break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE: /*case SDL_SCANCODE_Q:*/ if(menu()) { return 1; } break;

					//controls
					case SDL_SCANCODE_A: case SDL_SCANCODE_LEFT: if(!play) { entities[0].move_left=1; entities[0].move_right=0; entities[0].dir=1; record_data=1; move_keyboard=1; } break;
					case SDL_SCANCODE_D: case SDL_SCANCODE_RIGHT: if(!play) { entities[0].move_right=1; entities[0].move_left=0; entities[0].dir=0; record_data=1; move_keyboard=1; } break;
					case SDL_SCANCODE_C: if(!edit && os && !fire_o && !play) { fire_o=1; os--; record_data=1; } break;
					case SDL_SCANCODE_SPACE: if((edit||entities[0].block_distance_down==0) && !play) { entities[0].momentum_y=16; if(sfx) { Mix_PlayChannel(-1, jump_sfx, 0); } record_data = 1; jump = 1; } break;
					case SDL_SCANCODE_RETURN: case SDL_SCANCODE_LCTRL: case SDL_SCANCODE_RCTRL: if(!edit && ammo && !entities[0].fired && !play) { entities[0].fired=1; ammo--; record_data=1; } break;

					case SDL_SCANCODE_LSHIFT: ls=1; break;
					case SDL_SCANCODE_RSHIFT: rs=1; break;

					//edit mode only controls
//					case SDL_SCANCODE_L: if(edit){ sprintf(input_message, "enter level name"); if(text_input_string()) { break; } sprintf(next_level, "levels/%s", input_string); if(level_load()) { text_string("invalid level", 250, 160, 0, 0, 0, 13); SDL_RenderPresent(rend); SDL_Delay(1000); } } break;
//					case SDL_SCANCODE_N: if(edit){for(int i=0; i<1000; i++) { if(i<99) { entities[i+1].alive=0; } blocks[i]=0;} } break;
//					case SDL_SCANCODE_P: if(edit){level_save();} break;
					case SDL_SCANCODE_W: case SDL_SCANCODE_UP: if(edit){entities[0].rect.y-=10;} break;
					case SDL_SCANCODE_S: case SDL_SCANCODE_DOWN: if(edit){entities[0].rect.y+=10;} break;

					case SDL_SCANCODE_1: if(edit){ edit_id=0; if(ls||rs) { edit_id=4; } } break;
					case SDL_SCANCODE_2: if(edit){ edit_id=1; if(ls||rs) { edit_id=9; } } break;
					case SDL_SCANCODE_3: if(edit){ edit_id=2; if(ls||rs) { edit_id=10; } } break;
					case SDL_SCANCODE_4: if(edit){ edit_id=3; } break;
					case SDL_SCANCODE_5: if(edit){ edit_id=5; } break;
					case SDL_SCANCODE_6: if(edit){ edit_id=6; } break;
					case SDL_SCANCODE_7: if(edit){ edit_id=7; } break;
					case SDL_SCANCODE_8: if(edit){ edit_id=8; } break;
					case SDL_SCANCODE_9: if(edit){ edit_id=11; } break;

//					case SDL_SCANCODE_F: if(fullscreen==0){fullscreen=SDL_WINDOW_FULLSCREEN;}else{fullscreen=0;} SDL_SetWindowFullscreen(win, fullscreen); break;
//					case SDL_SCANCODE_E: if(!edit){edit=1;}else{edit=0; if(entities[0].momentum_x<0){entities[0].momentum_y=0;} } break;
//					case SDL_SCANCODE_R: frame=0; frame2=0; if(!rec) { strncpy(input_message, "enter demo name", 30); if(text_input_string()) { break; } strncpy(demo_name, input_string, 21); text_string("recording demo", 250, 160, 0, 0, 0, 14); text_string("press d again to end demo", 195, 190, 0, 0, 0, 25); SDL_RenderPresent(rend); SDL_Delay(1000); rec=1; }else { rec=0; text_string("demo ended", 270, 160, 0, 0, 0, 10); SDL_RenderPresent(rend); SDL_Delay(1000); } break;
//					case SDL_SCANCODE_M: if(Mix_PausedMusic()){Mix_ResumeMusic();}else{Mix_PauseMusic();} break;

					default: /* no u */ break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode)
				{
					case SDL_SCANCODE_A: case SDL_SCANCODE_LEFT: if(!play) { entities[0].move_left=0; record_data=1; move_keyboard=0; } break;
					case SDL_SCANCODE_D: case SDL_SCANCODE_RIGHT: if(!play) { entities[0].move_right=0; record_data=1; move_keyboard=0; } break;

					case SDL_SCANCODE_LSHIFT: ls=0; break;
					case SDL_SCANCODE_RSHIFT: rs=0; break;

					default: /* no u (again) */ break;
				}
				break;

			default: /* no u (again (again))*/ break;
		}
	}

	if(rec && record_data) { fprintf(demo_file, "%d\n%d %d %d %d %d\n", rec_frames, entities[0].move_left, entities[0].move_right, jump, entities[0].fired, fire_o); rec_frames=0; }
	else if(rec) { rec_frames++; }

	return 0;
}
