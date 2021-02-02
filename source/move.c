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

void move()
{
	int x=0;
	int random;
	while(x<ENTITIES)
	{
		// debug info
//		if(entities[x].alive>0) { printf("id: %d, rx: %d, ry: %d, maxs: %d, ml: %d, mr: %d, bdl: %d, bdr: %d, bdd: %d, bdu: %d, mx: %f, my: %f\n", x, entities[x].rect.x, entities[x].rect.y, (int)entities[x].max_speed, (int)entities[x].move_left, (int)entities[x].move_right, (int)entities[x].block_distance_left, (int)entities[x].block_distance_right, (int)entities[x].block_distance_down, (int)entities[x].block_distance_up, entities[x].momentum_x, entities[x].momentum_y); }

		if(!edit || entities[x].type==0) {
		if(entities[x].alive && ((entities[x].rect.x+block_rect.x+entities[x].rect.w>=0 && entities[x].rect.x+block_rect.x<=(int)WIN_W && entities[x].rect.y+entities[x].rect.h+block_rect.y>=0 && entities[x].rect.y+block_rect.y<=(int)WIN_H) || entities[x].type==0))
		{
			//crap ai
//			_Bool record_data = 0, jump = 0;
			if(entities[x].block_distance_left==0 && x!=0 && entities[x].move_left==1 ) { entities[x].move_left=0; entities[x].move_right=1; }
			if(entities[x].block_distance_right==0 && x!=0 && entities[x].move_right==1 ) { entities[x].move_left=1; entities[x].move_right=0; }
			if(entities[x].type==1 || entities[x].type==2)
			{
				random = rand() % 100;
				//moar debug
//				printf("%d\n", random);
				if(random == 0) { entities[x].move_right=0; entities[x].move_left=0; /*record_data=1;*/ }
				if(random == 1) { entities[x].move_right=0; entities[x].move_right=1; /*record_data=1;*/ }
				if(random == 2) { entities[x].move_right=1; entities[x].move_left=0; /*record_data=1;*/ }
				if(random == 3 && entities[x].type==2 && entities[x].block_distance_down==0) { entities[x].momentum_y=16; /*record_data=1; jump=1;*/ }

//				if(rec && record_data) { if(!rec_movement) { fprintf(demo_file, "-1 %d\n", rec_frames); rec_frames=1; rec_movement=1; } fprintf(demo_file, "%d %d %d %d %d\n", x, entities[x].move_left, entities[x].move_right, jump, entities[x].fired); }
			}
			else if(entities[x].type==3)
			{
				if(!entities[x].block_distance_right || !entities[x].block_distance_left) { entities[x].alive=0; }
			}
			else if(entities[x].type==4)
			{
				if(entities[0].rect.x<entities[x].rect.x+block_rect.x) { entities[x].move_left=1; entities[x].move_right=0; }
				else { entities[x].move_left=0; entities[x].move_right=1; }
			}
			else if(entities[x].type==5)
			{
				if(entities[x].block_distance_down==0) { entities[x].type=6; entities[x].rect.x-=40; entities[x].rect.y-=80; entities[x].anim_frame=0; entities[x].momentum_x=0; entities[x].momentum_y=0; entities[x].move_left=0; entities[x].move_right=0; entities[x].rect.w=100; entities[x].rect.h=100; if(sfx) { Mix_PlayChannel(-1, nuke_sfx, 0); } }
			}

			/* change entities[x].momentum_x (based on keyboard input or crappy ai) */
			if(entities[x].move_left && entities[x].momentum_x>=-entities[x].max_speed) { entities[x].momentum_x-=entities[x].acceleration; }
			if(entities[x].move_right && entities[x].momentum_x<=entities[x].max_speed) { entities[x].momentum_x+=entities[x].acceleration; }

			if(entities[x].momentum_x>entities[x].max_speed) { entities[x].momentum_x=entities[x].max_speed; }
			if(entities[x].momentum_x<-entities[x].max_speed) { entities[x].momentum_x=(-entities[x].max_speed); }

			entities[x].rect.x+=block_rect.x;
			entities[x].rect.y+=block_rect.y;
			/* move player left */
			if((entities[x].block_distance_left==-1 || entities[x].block_distance_left+entities[x].momentum_x>0) && entities[x].momentum_x<=-1.0F) { entities[x].rect.x+=(int)entities[x].momentum_x;
				//if too close too block
				}else if(entities[x].momentum_x<=-1.0F) { entities[x].momentum_x=0; entities[x].rect.x-=entities[x].block_distance_left; }

			//update block distance info
			draw(0);

			//it really does frustrate me how i need to copy and paste lines just to change minor things, but i don't really have a choice

			/* move player right */
			if((entities[x].block_distance_right==-1 || entities[x].block_distance_right-entities[x].momentum_x>0) && entities[x].momentum_x>=1.0F) { entities[x].rect.x+=(int)entities[x].momentum_x;
			//if too close too block
				}else if(entities[x].momentum_x>=1.0F) { entities[x].momentum_x=0; entities[x].rect.x+=entities[x].block_distance_right; }

//			if(0){

			/* change entities[x].momentum_x (towards 0) */
			//on ground
			if(!entities[x].move_left && !entities[x].move_right && entities[x].momentum_x<0 && entities[x].block_distance_down == 0) { entities[x].momentum_x+=0.2F; }
			//in air
			else if(!entities[x].move_left && !entities[x].move_right && entities[x].momentum_x<0 && entities[x].block_distance_down != 0) { entities[x].momentum_x+=0.05; }
			//on ground
			if(!entities[x].move_left && !entities[x].move_right && entities[x].momentum_x>0 && entities[x].block_distance_down == 0) { entities[x].momentum_x-=0.2F; }
			//in air
			else if(!entities[x].move_left && !entities[x].move_right && entities[x].momentum_x>0 && entities[x].block_distance_down != 0) { entities[x].momentum_x-=0.05; }

			/* update block distance info */
			draw(0);


			/* move player up */
			if((entities[x].block_distance_up==-1 || entities[x].block_distance_up-entities[x].momentum_y>0) && entities[x].momentum_y>=1.0F) { entities[x].rect.y-=(int)entities[x].momentum_y;
				//if too close too block
				}else if(entities[x].momentum_y>=1.0F) { entities[x].momentum_y=0; entities[x].rect.y-=entities[x].block_distance_up; }

//fuck you fuck you fuck you fuck you
			if(!edit)
			{
				draw(0);

				/* move player down */
				if((entities[x].block_distance_down==-1 || entities[x].block_distance_down+entities[x].momentum_y>0) && entities[x].momentum_y<=-1.0F) { entities[x].rect.y-=(int)entities[x].momentum_y;
					//if too close too block
					}else if(entities[x].momentum_y<=-1.0F) { entities[x].momentum_y=0; entities[x].rect.y+=entities[x].block_distance_down; }

				//reset player location if below the ground
//				if(entities[x].rect.y > 405) { entities[x].rect.y=405; }

				//kill player if below the ground
				if(entities[x].rect.y>(int)WIN_H+100) { entities[x].alive=0; }
			} // I WIN

			entities[x].rect.x-=block_rect.x;
			entities[x].rect.y-=block_rect.y;

			//decrease entities[x].momentum_y (GRAVITY)
			if((entities[x].block_distance_down>0 || entities[x].block_distance_down==-1) && entities[x].type!=3) { entities[x].momentum_y-=0.5F; }
			//reset player momentum upon touching the ground
			if((entities[x].block_distance_down==0 /*|| entities[x].rect.y==405*/) && entities[x].momentum_y<0) { entities[x].momentum_y=0; }

			if(x==0)
			{
				block_rect.x=-(entities[x].rect.x+entities[x].rect.w/2-WIN_W/2);
				if(block_rect.x>0){block_rect.x=0;}
				block_rect.y=-(entities[x].rect.y+entities[x].rect.h/2-WIN_H/2);
				if(block_rect.y<WIN_H-60){block_rect.y=WIN_H-60;}
			}

			//reset player location if offscreen
			if(entities[x].rect.x < 0 && entities[x].type==0) { entities[x].momentum_x=0; entities[x].rect.x=0; }
//			}

		} // end of "!edit || entities[x].type==0"

		}
		else if(entities[x].alive && entities[x].type==3) { entities[x].alive=0; }
		x++;
	}
}
