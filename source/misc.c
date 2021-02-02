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

void misc()
{
	int to_kill=-1;
	_Bool make_decal=0;
	//damage player if touching enemy
	for(int f=0; f<100; f++)
	{
		if(!edit && (entities[f].type==0 || entities[f].type==3 || entities[f].type==6) && entities[f].alive)
		{
			entities[f].rect.x+=block_rect.x;
			entities[f].rect.y+=block_rect.y;
//			printf("%d %d\n", f, entities[f].type);
			for(int x=1; x<ENTITIES; x++)
			{
				if(entities[x].alive && (entities[x].type==1 || entities[x].type==2 || entities[x].type==4))
				{
					if(entities[x].rect.y+block_rect.y<entities[f].rect.y+entities[f].rect.h && entities[x].rect.y+block_rect.y+entities[x].rect.h>entities[f].rect.y && entities[x].rect.x+block_rect.x+entities[x].rect.w>entities[f].rect.x && entities[x].rect.x+block_rect.x<entities[f].rect.x+entities[f].rect.w && (hurt_frames==0 || entities[f].type==3)) { if(entities[f].type==0) { entities[f].alive--; hurt_frames=100; if(sfx && entities[f].alive) { Mix_PlayChannel(-1, hurt_sfx, 0); } else { make_decal=1; to_kill=f; } } else { entities[x].alive=0; if(entities[f].type!=6) { entities[f].alive=0; } make_decal=1; to_kill=x; } break; }
				}
 			}
			entities[f].rect.x-=block_rect.x;
			entities[f].rect.y-=block_rect.y;
		}
	}
	if(make_decal) { int z=-1; for(int garbage=0; garbage<DECALS; garbage++) { if(!decals[garbage].active) { z=garbage; break; } } if(z!=-1 && entities[to_kill].block_distance_down!=-1) { decals[z].active=1; decals[z].passport=1; decals[z].rect.x=entities[to_kill].rect.x; decals[z].rect.y=(entities[to_kill].rect.y+entities[to_kill].rect.h+entities[to_kill].block_distance_down)-50; decals[z].rect.w=50; decals[z].rect.h=50; decals[z].parallax=1; } }
	if(hurt_frames>0) {hurt_frames--;}

	//gun
	if((entities[0].fired || fire_o) && entities[0].alive)
	{
		if(sfx) { Mix_PlayChannel(-1, shoot_sfx, 0); }
		for(int x=1; x<ENTITIES; x++)
		{
			if(!entities[x].alive)
			{
				entities[x].alive=1;
				entities[x].rect.y=entities[0].rect.y+34;
				entities[x].max_speed=9.0F;
				entities[x].acceleration=9.0F;
				entities[x].dir=entities[0].dir;
				entities[x].block_distance_left=-1;
				entities[x].block_distance_right=-1;
				if(!entities[0].dir) { entities[x].momentum_x=9.0F; entities[x].rect.x=entities[0].rect.x+49; entities[x].move_left=0; entities[x].move_right=1; }
				else { entities[x].momentum_x=-9.0F; entities[x].rect.x=entities[0].rect.x-14; entities[x].move_left=1; entities[x].move_right=0; }
				if(fire_o) { fire_o=0; entities[x].rect.w=20; entities[x].rect.h=20; entities[x].type=5; entities[x].momentum_y=2.0F; } else { entities[0].fired=0; entities[x].rect.w=14; entities[x].rect.h=14; entities[x].type=3; entities[x].momentum_y=0.0F; }
				if(!fire_o && !entities[0].fired) { break; }
			}
		}
	}
}
