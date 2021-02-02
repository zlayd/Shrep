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

_Bool init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
	win = SDL_CreateWindow("Shrep Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	if(!win) { printf("oof: %s\n", SDL_GetError()); return 1; }
	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!rend) { printf("oof: %s\n", SDL_GetError()); return 1; }
	SDL_RenderSetLogicalSize(rend, WIN_W, WIN_H);
	SDL_Surface* surf;
	if(!(surf = SDL_LoadBMP("bmps/sky.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	sky_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/sky_noon.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	sky_noon_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/sky_night.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	sky_night_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/sky_hell.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	sky_hell_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/sun.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	sun_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/moon.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	moon_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//player
	if(!(surf = SDL_LoadBMP("bmps/abomination.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	player_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//walking anim
	if(!(surf = SDL_LoadBMP("bmps/abomination2.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	player_tex2 = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/wahts_wrong_with_your_legs.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	player_tex3 = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//gunshot
	if(!(surf = SDL_LoadBMP("bmps/fire.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	fire_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//enemy 1 (umm?)
	if(!(surf = SDL_LoadBMP("bmps/what_is_this.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	umm_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//enemy 2 (stoncc image)
	if(!(surf = SDL_LoadBMP("bmps/stoncc.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	stoncc_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//enemy 3 (MELONZ)
	if(!(surf = SDL_LoadBMP("bmps/watermelon_man.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	melon_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//actual blocks
	if(!(surf = SDL_LoadBMP("bmps/brick.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	brick_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/grass.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	grass_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/dirt.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	dirt_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//edit mode boxes
	if(!(surf = SDL_LoadBMP("bmps/select_box_blue.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	hud_tex_b = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/select_box_yellow.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	hud_tex_y = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//items
	if(!(surf = SDL_LoadBMP("bmps/coin.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	coin_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/ammo.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	ammo_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/dew.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	dew_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/tos.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	tos_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/tos_dark.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	tos_dark_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/os.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	os_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/os_dark.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	os_dark_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//decals
	if(!(surf = SDL_LoadBMP("bmps/cloud.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	cloud_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/tombstone.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	tomb_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	if(!(surf = SDL_LoadBMP("bmps/nuke.bmp"))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); return 1; }
	nuke_tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	//map
	entities[0].rect.h=75;
	entities[0].rect.w=50;
	entities[0].alive=2;
	entities[0].lives=3;
	entities[0].acceleration=0.2F;
	entities[0].type=0;
	entities[0].max_speed=7.0F;

	block_rect.h=60;
	block_rect.w=60;
	SDL_SetRenderDrawColor(rend, 0, 200, 255, 255);

	//SDL_mixer
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)==-1){ printf("oof: couldn't init sdl_mixer\n"); return 1;}

	//music
	mus1 = Mix_LoadMUS("wavs/track1.wav");
	if(!mus1){printf("oof: couldn't open wavs/track1.wav\n"); return 1;}
	mus2 = Mix_LoadMUS("wavs/track2.wav");
	if(!mus2){printf("oof: couldn't open wavs/track2.wav\n"); return 1;}
	mus3 = Mix_LoadMUS("wavs/track3.wav");
	if(!mus3){printf("oof: couldn't open wavs/track3.wav\n"); return 1;}
	mus4 = Mix_LoadMUS("wavs/track4.wav");
	if(!mus4){printf("oof: couldn't open wavs/track4.wav\n"); return 1;}

	//sfx
	shoot_sfx = Mix_LoadWAV("wavs/idk.wav");
	if(!shoot_sfx){printf("oof: couldn't open wavs/idk.wav (ugh)\n"); return 1;}
	tos_sfx = Mix_LoadWAV("wavs/tos.wav");
	if(!tos_sfx){printf("oof: couldn't open wavs/tos.wav (delicious)\n"); return 1;}
	dew_sfx = Mix_LoadWAV("wavs/dew.wav");
	if(!dew_sfx){printf("oof: couldn't open wavs/dew.wav (drink up, BUDDY)\n"); return 1;}
	coin_sfx = Mix_LoadWAV("wavs/coin.wav");
	if(!coin_sfx){printf("oof: couldn't open wavs/coin.wav (you're all out of playcoins!)\n"); return 1;}
	bullet_sfx = Mix_LoadWAV("wavs/bullet.wav");
	if(!bullet_sfx){printf("oof: couldn't open wavs/bullet.wav (i think the trigger is loose)\n"); return 1;}
	hurt_sfx = Mix_LoadWAV("wavs/hurt.wav");
	if(!hurt_sfx){printf("oof: couldn't open wavs/hurt.wav (it's okay, i'm not...human)\n"); return 1;}
	jump_sfx = Mix_LoadWAV("wavs/jump.wav");
	if(!jump_sfx){printf("oof: couldn't open wavs/jump.wav (use your rope)\n"); return 1;}
	ded_sfx = Mix_LoadWAV("wavs/ded.wav");
	if(!ded_sfx){printf("oof: couldn't open wavs/ded.wav (you're inexplicabley immortal)\n"); return 1;}
	fuck_sfx = Mix_LoadWAV("wavs/fail.wav");
	if(!fuck_sfx){printf("oof: couldn't open wavs/fail.wav (good job)\n"); return 1;}
	keyboard_sfx = Mix_LoadWAV("wavs/keyboard.wav");
	if(!keyboard_sfx){printf("oof: couldn't open wavs/keyboard.wav (wikipedia, the FREE online encyclopedia that ANYONE from Black Mesa can edit)\n"); return 1;}
	nuke_sfx = Mix_LoadWAV("wavs/nuke.wav");
	if(!nuke_sfx){printf("oof: couldn't open wavs/nuke.wav (this sound effect is absolutely terrible, you're not missing much)\n"); return 1;}

	seed = time(NULL);
	srand(seed);

//	printf("SDL_NumJoysticks(): %d\n", SDL_NumJoysticks());
	for(int i=0; i<SDL_NumJoysticks(); i++)
	{
		if(SDL_IsGameController(i)) { gamepad = SDL_GameControllerOpen(i); break; }
	}


	return 0;
}
