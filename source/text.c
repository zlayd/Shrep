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

_Bool text_int(int num, int x, int y, int r, int g, int b, int digits)
{
	SDL_Rect char_rect;
	char_rect.x=x;
	char_rect.y=y;
	char_rect.w=10;
	char_rect.h=20;
	SDL_Texture* char_tex;
	SDL_Surface* surf;
	int i = 1;
	int oof;
	char file_path[22] = "bmps/chars/char_*.bmp";
	while(i<=digits)
	{
		oof=(int)pow(10, (digits-i));
//		if(digits-i==0){oof=1;}
		file_path[16] = (char)((((int)(num/oof))%10)+'0');
//		printf("num: %d, i: %d, oof: %d, fp[16]: %c\n", num, i, oof, file_path[16]);
		if(!(surf = SDL_LoadBMP(file_path))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); SDL_DestroyTexture(char_tex); quit=1; return 1; }
		char_tex = SDL_CreateTextureFromSurface(rend, surf);
		SDL_SetTextureColorMod(char_tex, r, g, b);
		SDL_RenderCopy(rend, char_tex, NULL, &char_rect);
		char_rect.x+=char_rect.w+2;
		SDL_FreeSurface(surf);
		SDL_DestroyTexture(char_tex);
		i++;
	}
	return 0;
}

_Bool text_string(char* string, int x, int y, int r, int g, int b, int chars)
{
	SDL_Rect char_rect;
	char_rect.x=x;
	char_rect.y=y;
	char_rect.w=10;
	char_rect.h=20;
	SDL_Texture* char_tex;
	SDL_Surface* surf;
	int i = 0;
	char file_path[22] = "bmps/chars/char_*.bmp";
	while(i<chars)
	{
		if(string[i]!='\0') {
		file_path[16] = string[i];
		if(!(surf = SDL_LoadBMP(file_path))) { printf("oof: %s\n", SDL_GetError()); SDL_FreeSurface(surf); SDL_DestroyTexture(char_tex); quit=1; return 1; }
		char_tex = SDL_CreateTextureFromSurface(rend, surf);
		SDL_SetTextureColorMod(char_tex, r, g, b);
		SDL_RenderCopy(rend, char_tex, NULL, &char_rect);
		char_rect.x+=char_rect.w+2;
		SDL_FreeSurface(surf);
		SDL_DestroyTexture(char_tex);
		} i++;
	}
	return 0;
}
