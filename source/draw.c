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

_Bool draw(int actually_draw)
{
	if(actually_draw && WIN_H==480 && fullscreen && (level_type!=3 || !item_anim || edit)) { SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); SDL_RenderClear(rend); }

	if(actually_draw)
	{
		switch(level_type)
		{
			case 0: SDL_RenderCopy(rend, sky_noon_tex, NULL, &sky_rect); SDL_Rect temp = {WIN_W/2-50, WIN_H/3, 100, 100}; SDL_RenderCopy(rend, sun_tex, NULL, &temp); break;
			case 1: SDL_RenderCopy(rend, sky_tex, NULL, &sky_rect); SDL_Rect tempz = {WIN_W/2-50, WIN_H/4*3, 100, 100}; SDL_RenderCopy(rend, sun_tex, NULL, &tempz); break;
			case 2: SDL_RenderCopy(rend, sky_night_tex, NULL, &sky_rect); SDL_Rect tempzz = {WIN_W/2-50, WIN_H/3, 100, 100}; SDL_RenderCopy(rend, moon_tex, NULL, &tempzz); break;
			case 3: if(!item_anim || edit) { SDL_RenderCopy(rend, sky_hell_tex, NULL, &sky_rect); } break;
		}
	}
	for(int i=0; i<100; i++)
	{
		if(entities[i].alive)
		{
			entities[i].rect.x+=block_rect.x;
			entities[i].rect.y+=block_rect.y;
		}
	}

	//decals
	if(actually_draw)
	{
		for(int z=0; z<DECALS; z++)
		{
			if(decals[z].active)
			{
				int shit = block_rect.x/decals[z].parallax;
				int shittier = block_rect.y/decals[z].parallax;
				int oldw = decals[z].rect.w;
				int oldh = decals[z].rect.h;
				decals[z].rect.w/=decals[z].parallax;
				decals[z].rect.h/=decals[z].parallax;
//				printf("b, z: %d, x: %d\n", z, decals[z].rect.x);
				decals[z].rect.x+=shit;
				decals[z].rect.y+=shittier;
				switch(decals[z].passport)
				{
					case 0: SDL_RenderCopy(rend, cloud_tex, NULL, &decals[z].rect); break;
					case 1: SDL_RenderCopy(rend, tomb_tex, NULL, &decals[z].rect); break;
				}
				decals[z].rect.x-=shit;
				decals[z].rect.y-=shittier;
				decals[z].rect.w=oldw;
				decals[z].rect.h=oldh;
//				printf("a, z: %d, x: %d\n", z, decals[z].rect.x);
			}
		}
	}

	int x = 0;
	_Bool mdew=0;

	SDL_RendererFlip temp_flip;
	while(x<ENTITIES && !input && actually_draw)
	{
		if(entities[x].alive && ((entities[x].rect.x+entities[x].rect.w>=0 && entities[x].rect.x<=(int)WIN_W && entities[x].rect.y+entities[x].rect.h>=0 && entities[x].rect.y<=(int)WIN_H) || entities[x].type==0))
		{
//			if(x!=0) { entities[x].rect.x+=block_rect.x; }
			entities[x].block_distance_right=-1;
			entities[x].block_distance_left=-1;
			entities[x].block_distance_up=-1;
			entities[x].block_distance_down=-1;
			//"animation" (shrek's legs are broken)
			temp_flip=SDL_FLIP_NONE; if(entities[x].dir) { temp_flip=SDL_FLIP_HORIZONTAL; }
			if(entities[x].type==0)
			{
				if((entities[x].move_left || entities[x].move_right) && entities[x].anim == 0) { entities[x].anim=1; entities[x].anim_frame=0; }
				if(!entities[x].move_left && !entities[x].move_right) { entities[x].anim=0; entities[x].anim_frame=0; }
				if(entities[x].anim_frame>=3 && entities[x].anim!=0) { entities[x].anim_frame=0; if(entities[x].anim==1) { entities[x].anim=2;}else{ entities[x].anim=1; }  }
				if(entities[x].anim==0 && !(hurt_frames%2)) { SDL_RenderCopyEx(rend, player_tex, NULL, &entities[x].rect, 0, NULL, temp_flip); }
				if(entities[x].anim==1 && !(hurt_frames%2)) { SDL_RenderCopyEx(rend, player_tex2, NULL, &entities[x].rect, 0, NULL, temp_flip); }
				if(entities[x].anim==2 && !(hurt_frames%2)) { SDL_RenderCopyEx(rend, player_tex3, NULL, &entities[x].rect, 0, NULL, temp_flip); }
				if(entities[x].anim!=0) { entities[x].anim_frame++; }
			}
			else if(entities[x].type==1) { SDL_RenderCopyEx(rend, umm_tex, NULL, &entities[x].rect, 0, NULL, temp_flip); }
			else if(entities[x].type==2) { SDL_RenderCopyEx(rend, stoncc_tex, NULL, &entities[x].rect, 0, NULL, temp_flip); }
			else if(entities[x].type==3) { SDL_RenderCopyEx(rend, fire_tex, NULL, &entities[x].rect, 0, NULL, temp_flip); }
			else if(entities[x].type==4) { SDL_RenderCopyEx(rend, melon_tex, NULL, &entities[x].rect, 0, NULL, temp_flip); }
			else if(entities[x].type==5) { SDL_Rect temp = {20,20,20,20}; SDL_RenderCopyEx(rend, os_tex, &temp, &entities[x].rect, 0, NULL, temp_flip); }
			else if(entities[x].type==6) { SDL_RenderCopyEx(rend, nuke_tex, NULL, &entities[x].rect, 0, NULL, temp_flip); entities[x].anim_frame++; if(entities[x].anim_frame==100) { entities[x].alive=0;} }
		}
		x++;
	}

	int i=0;
	int j=0;
	while(i < level_length)
	{
		block_rect.x+=i*60;
		while(j < level_height)
		{
			block_rect.y-=j*60;
			if(blocks[i][j] && block_rect.x+60>=0 && block_rect.x<=(int)WIN_W)
			{

				x=0;
				//get coordinates from position in array
//				if(entities[x].alive)
//				{
					if(blocks[i][j]==1 || blocks[i][j]==3 || blocks[i][j]==8)
					{
						for(x=0; x<ENTITIES; x++)
						{
							if(entities[x].alive && ((entities[x].rect.x+entities[x].rect.w>=0 && entities[x].rect.x<=(int)WIN_W && entities[x].rect.y+entities[x].rect.h>=0 && entities[x].rect.y<=(int)WIN_H) || entities[x].type==0))
							{
								//get distance from player
								//right side
								if(entities[x].rect.x>=block_rect.x+60 && (entities[x].rect.x-(block_rect.x+60)<entities[x].block_distance_left || entities[x].block_distance_left==-1) && entities[x].rect.y<block_rect.y+60 && entities[x].rect.y+entities[x].rect.h>block_rect.y) { entities[x].block_distance_left=entities[x].rect.x-(block_rect.x+60); }
								//left side
								if(entities[x].rect.x<block_rect.x && ((block_rect.x-1)-(entities[x].rect.x+(entities[x].rect.w-1))<entities[x].block_distance_right || entities[x].block_distance_right==-1) && entities[x].rect.y<block_rect.y+60 && entities[x].rect.y+entities[x].rect.h>block_rect.y) { entities[x].block_distance_right=(block_rect.x-1)-(entities[x].rect.x+(entities[x].rect.w-1)); }
								//bottom side
								if(entities[x].rect.y>=block_rect.y+60 && (entities[x].rect.y-(block_rect.y+60)<entities[x].block_distance_up || entities[x].block_distance_up==-1) && entities[x].rect.x<block_rect.x+60 && entities[x].rect.x+entities[x].rect.w>block_rect.x) { entities[x].block_distance_up=entities[x].rect.y-(block_rect.y+60); }
								//top side
								if(entities[x].rect.y<block_rect.y && ((block_rect.y-1)-(entities[x].rect.y+entities[x].rect.h)<=entities[x].block_distance_down || entities[x].block_distance_down==-1) && entities[x].rect.x<block_rect.x+60 && entities[x].rect.x+entities[x].rect.w>block_rect.x) { entities[x].block_distance_down=(block_rect.y-1)-(entities[x].rect.y+(entities[x].rect.h-1)); }
							}
						}
						//draw block
						if(actually_draw) { if(blocks[i][j]==1){SDL_RenderCopy(rend, brick_tex, NULL, &block_rect);}else if(blocks[i][j]==3){SDL_RenderCopy(rend, grass_tex, NULL, &block_rect);}else{SDL_RenderCopy(rend, dirt_tex, NULL, &block_rect);} }
					}else if(blocks[i][j]==2 || blocks[i][j]==5 || blocks[i][j]==6 || blocks[i][j]==7 || blocks[i][j]==11)
					{
						//draw coin/ammo/dew/tos/os
						if(actually_draw && blocks[i][j]==2) { SDL_RenderCopyEx(rend, coin_tex, NULL, &block_rect, item_angle, NULL, SDL_FLIP_NONE); }
						else if(actually_draw && blocks[i][j]==5){ SDL_RenderCopyEx(rend, ammo_tex, NULL, &block_rect, item_angle, NULL, SDL_FLIP_NONE); }
						else if(actually_draw && blocks[i][j]==6){ SDL_RenderCopyEx(rend, dew_tex, NULL, &block_rect, item_angle, NULL, SDL_FLIP_NONE); }
						else if(actually_draw && blocks[i][j]==7){ SDL_RenderCopyEx(rend, tos_tex, NULL, &block_rect, item_angle, NULL, SDL_FLIP_NONE); }
						else if(actually_draw && blocks[i][j]==11){ SDL_RenderCopyEx(rend, os_tex, NULL, &block_rect, item_angle, NULL, SDL_FLIP_NONE); }
						//coin/ammo/dew/tos/os collision
						if(!edit && entities[0].rect.x+49>block_rect.x+15 && entities[0].rect.x<block_rect.x+25 && entities[0].rect.y+85>block_rect.y+9 && entities[0].rect.y<block_rect.y+40) { if(blocks[i][j]==2) { blocks[i][j]=102; coins++; if(coins!=0 && coins%100==0) { entities[0].lives++; } if(sfx) { Mix_PlayChannel(-1, coin_sfx, 0); } } else if(ammo<99 && blocks[i][j]==5) { blocks[i][j]=105; ammo++; if(sfx) { Mix_PlayChannel(-1, bullet_sfx, 0); } } else if(blocks[i][j]==6) { blocks[i][j]=106; dew++; if(sfx) { Mix_PlayChannel(-1, dew_sfx, 0); } mdew=1; } else if(blocks[i][j]==7 && entities[0].alive<3) { blocks[i][j]=107; entities[0].alive++; if(sfx) { Mix_PlayChannel(-1, tos_sfx, 0); } } else if(blocks[i][j]==11 && os<3) { blocks[i][j]=111; os++; if(sfx) { Mix_PlayChannel(-1, tos_sfx, 0); } } }
					}else if(blocks[i][j]==4 && edit) { SDL_RenderCopy(rend, umm_tex, NULL, &block_rect);
					}else if(blocks[i][j]==9 && edit) { SDL_RenderCopy(rend, stoncc_tex, NULL, &block_rect);
					}else if(blocks[i][j]==10 && edit) { SDL_RenderCopy(rend, melon_tex, NULL, &block_rect);
					}else if(blocks[i][j]==102 && edit) { blocks[i][j]=2;
					}else if(blocks[i][j]==105 && edit) { blocks[i][j]=5;
					}else if(blocks[i][j]==106 && edit) { blocks[i][j]=6;
					}else if(blocks[i][j]==107 && edit) { blocks[i][j]=7;
					}else if(blocks[i][j]==111 && edit) { blocks[i][j]=11; }
//				}
			}
			if(edit && mpos_x>=block_rect.x && mpos_x<block_rect.x+60 && mpos_y>=block_rect.y && mpos_y<block_rect.y+60 && mb==1){blocks[i][j]=edit_id;}
			block_rect.y+=j*60;
			j++;
		}
		block_rect.x-=i*60;
		j=0;
		i++;
	}

	/* draw hud */
	int oldx=block_rect.x; int oldy=block_rect.y;
	block_rect.y=-10;
	//coins
	if(actually_draw) { block_rect.x=-5; SDL_RenderCopy(rend, coin_tex, NULL, &block_rect); text_int(coins, 32, 10, 0, 0, 255, 6); }
	//ammo
	block_rect.y=20;
	if(actually_draw) { block_rect.x=-5; SDL_RenderCopy(rend, ammo_tex, NULL, &block_rect); text_int(ammo, 32, 40, 0, 0, 255, 3); }
	//lives
	SDL_Rect temp_rect = {68, 40, 10, 20};
	if(actually_draw) { SDL_RenderCopy(rend, player_tex, NULL, &temp_rect); text_int(entities[0].lives, 80, 40, 0, 0, 255, 2); }
	//dew
//	block_rect.y=50;
//	if(actually_draw) { block_rect.x=19; SDL_RenderCopy(rend, dew_tex, NULL, &block_rect); text_int(dew, 56, 40, 0, 0, 255, 3); }
	//tos aka health
	block_rect.x=0; block_rect.y=100;
	for(int wtf=2 ; wtf>-1 ; wtf--)
	{
		if(actually_draw) { if(entities[0].alive>wtf) { SDL_RenderCopy(rend, tos_tex, NULL, &block_rect); }else { SDL_RenderCopy(rend, tos_dark_tex, NULL, &block_rect); } }
		block_rect.x+=30;
		if(actually_draw) { if(os>wtf) { SDL_RenderCopy(rend, os_tex, NULL, &block_rect); }else { SDL_RenderCopy(rend, os_dark_tex, NULL, &block_rect); } }
		block_rect.x-=30;
		block_rect.y-=25;
	}
	block_rect.x=oldx; block_rect.y=oldy;

	if(input) { text_string(input_message, WIN_W/2-174, WIN_H/4, 0, 0, 255, 29); text_string(input_string, WIN_W/2-174, WIN_H/4+20, 0, 0, 255, 20); }
	//draw edit menu
	if(actually_draw && edit){
		SDL_Rect hud_rect = {WIN_W/2-157, 10, 40, 40};
		SDL_Rect hud_block_rect = {WIN_W/2-152, 15, 30, 30};
		// TODO: Cleanup 'code'
		if(edit_id==0){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} text_int(1, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==1){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, brick_tex, NULL, &hud_block_rect); text_int(2, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==2){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, coin_tex, NULL, &hud_block_rect); text_int(3, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==3){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, grass_tex, NULL, &hud_block_rect); text_int(4, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==5){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, ammo_tex, NULL, &hud_block_rect); text_int(5, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==6){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, dew_tex, NULL, &hud_block_rect); text_int(6, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==7){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, tos_tex, NULL, &hud_block_rect); text_int(7, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==8){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, dirt_tex, NULL, &hud_block_rect); text_int(8, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==11){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, os_tex, NULL, &hud_block_rect); text_int(9, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		hud_rect.x=WIN_W/2-157;
		hud_rect.y+=70;
		hud_block_rect.x=WIN_W/2-152;
		hud_block_rect.y+=70;
		if(edit_id==4){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, umm_tex, NULL, &hud_block_rect); text_int(1, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==9){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, stoncc_tex, NULL, &hud_block_rect); text_int(2, hud_rect.x+15, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
		if(edit_id==10){SDL_RenderCopy(rend, hud_tex_y, NULL, &hud_rect);}else{SDL_RenderCopy(rend, hud_tex_b, NULL, &hud_rect);} SDL_RenderCopy(rend, melon_tex, NULL, &hud_block_rect); text_int(3, hud_rect.x+9, hud_rect.y+43, 0, 0, 255, 1); hud_rect.x+=46; hud_block_rect.x+=46;
	}
	if(actually_draw==1) { SDL_RenderPresent(rend); }

	for(int i=0; i<100; i++)
	{
		if(entities[i].alive)
		{
			entities[i].rect.x-=block_rect.x;
			entities[i].rect.y-=block_rect.y;
		}
	}
	if(actually_draw) { item_anim++; }
	if(item_anim==50) { item_anim=0; item_angle=0-item_angle; }
	if(mdew) { level_end(); }
	return 0;
}
//no u
