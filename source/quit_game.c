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

void quit_game()
{
	options(1);

	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_DestroyTexture(player_tex);
	SDL_DestroyTexture(player_tex2);
	SDL_DestroyTexture(player_tex3);
	SDL_DestroyTexture(umm_tex);
	SDL_DestroyTexture(stoncc_tex);
	SDL_DestroyTexture(melon_tex);
	SDL_DestroyTexture(brick_tex);
	SDL_DestroyTexture(grass_tex);
	SDL_DestroyTexture(dirt_tex);
	SDL_DestroyTexture(coin_tex);
	SDL_DestroyTexture(sky_tex);
	SDL_DestroyTexture(sky_noon_tex);
	SDL_DestroyTexture(sky_night_tex);
	SDL_DestroyTexture(sky_hell_tex);
	SDL_DestroyTexture(sun_tex);
	SDL_DestroyTexture(moon_tex);
	SDL_DestroyTexture(hud_tex_b);
	SDL_DestroyTexture(hud_tex_y);
	SDL_DestroyTexture(ammo_tex);
	SDL_DestroyTexture(dew_tex);
	SDL_DestroyTexture(tos_tex);
	SDL_DestroyTexture(tos_dark_tex);
	SDL_DestroyTexture(os_tex);
	SDL_DestroyTexture(os_dark_tex);
	SDL_DestroyTexture(fire_tex);
	SDL_DestroyTexture(cloud_tex);
	SDL_DestroyTexture(tomb_tex);
	SDL_DestroyTexture(nuke_tex);
	SDL_GameControllerClose(gamepad);
	SDL_Quit();

	Mix_FreeMusic(mus1);
	Mix_FreeMusic(mus2);
	Mix_FreeMusic(mus3);
	Mix_FreeMusic(mus4);
	Mix_FreeChunk(shoot_sfx);
	Mix_FreeChunk(tos_sfx);
	Mix_FreeChunk(dew_sfx);
	Mix_FreeChunk(coin_sfx);
	Mix_FreeChunk(bullet_sfx);
	Mix_FreeChunk(hurt_sfx);
	Mix_FreeChunk(jump_sfx);
	Mix_FreeChunk(ded_sfx);
	Mix_FreeChunk(fuck_sfx);
	Mix_FreeChunk(keyboard_sfx);
	Mix_FreeChunk(nuke_sfx);
	Mix_CloseAudio();

	if(rec || play) { demo(3); }

	return;
}

