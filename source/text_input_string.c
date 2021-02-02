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

_Bool text_input_string(_Bool spaces)
{
	_Bool meme = 0;
	_Bool exit = 0;
	for(int i = 0 ; i<22; i++) { input_string[i]=(char)0; }
	input_string[0]='e';
	input_string[1]='p';
	input_string[2]='i';
	input_string[3]='c';
	Uint8 pos = 4;
	input=1;
	while(!meme)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT: quit=1; break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.scancode)
					{
						case SDL_SCANCODE_ESCAPE: exit=1; break;
						case SDL_SCANCODE_LSHIFT: ls=1; break;
						case SDL_SCANCODE_RSHIFT: rs=1; break;
						case SDL_SCANCODE_RETURN: if(input_string[0]!=(char)0){meme=1;} break;
						case SDL_SCANCODE_BACKSPACE: if(pos>0) { input_string[pos-1]=(char)0; pos--; } break;
						//idk how to make this better
						case SDL_SCANCODE_MINUS: if(pos<20) { if(ls || rs){input_string[pos]='_';}else{input_string[pos]='-';} pos++; } break;
						case SDL_SCANCODE_SPACE: if(pos<20 && spaces) { input_string[pos]=' '; pos++; } break;
						case SDL_SCANCODE_A: if(pos<20) { input_string[pos]='a'; pos++; } break;
						case SDL_SCANCODE_B: if(pos<20) { input_string[pos]='b'; pos++; } break;
						case SDL_SCANCODE_C: if(pos<20) { input_string[pos]='c'; pos++; } break;
						case SDL_SCANCODE_D: if(pos<20) { input_string[pos]='d'; pos++; } break;
						case SDL_SCANCODE_E: if(pos<20) { input_string[pos]='e'; pos++; } break;
						case SDL_SCANCODE_F: if(pos<20) { input_string[pos]='f'; pos++; } break;
						case SDL_SCANCODE_G: if(pos<20) { input_string[pos]='g'; pos++; } break;
						case SDL_SCANCODE_H: if(pos<20) { input_string[pos]='h'; pos++; } break;
						case SDL_SCANCODE_I: if(pos<20) { input_string[pos]='i'; pos++; } break;
						case SDL_SCANCODE_J: if(pos<20) { input_string[pos]='j'; pos++; } break;
						case SDL_SCANCODE_K: if(pos<20) { input_string[pos]='k'; pos++; } break;
						case SDL_SCANCODE_L: if(pos<20) { input_string[pos]='l'; pos++; } break;
						case SDL_SCANCODE_M: if(pos<20) { input_string[pos]='m'; pos++; } break;
						case SDL_SCANCODE_N: if(pos<20) { input_string[pos]='n'; pos++; } break;
						case SDL_SCANCODE_O: if(pos<20) { input_string[pos]='o'; pos++; } break;
						case SDL_SCANCODE_P: if(pos<20) { input_string[pos]='p'; pos++; } break;
						case SDL_SCANCODE_Q: if(pos<20) { input_string[pos]='q'; pos++; } break;
						case SDL_SCANCODE_R: if(pos<20) { input_string[pos]='r'; pos++; } break;
						case SDL_SCANCODE_S: if(pos<20) { input_string[pos]='s'; pos++; } break;
						case SDL_SCANCODE_T: if(pos<20) { input_string[pos]='t'; pos++; } break;
						case SDL_SCANCODE_U: if(pos<20) { input_string[pos]='u'; pos++; } break;
						case SDL_SCANCODE_V: if(pos<20) { input_string[pos]='v'; pos++; } break;
						case SDL_SCANCODE_W: if(pos<20) { input_string[pos]='w'; pos++; } break;
						case SDL_SCANCODE_X: if(pos<20) { input_string[pos]='x'; pos++; } break;
						case SDL_SCANCODE_Y: if(pos<20) { input_string[pos]='y'; pos++; } break;
						case SDL_SCANCODE_Z: if(pos<20) { input_string[pos]='z'; pos++; } break;
						case SDL_SCANCODE_1: if(pos<20) { input_string[pos]='1'; pos++; } break;
						case SDL_SCANCODE_2: if(pos<20) { input_string[pos]='2'; pos++; } break;
						case SDL_SCANCODE_3: if(pos<20) { input_string[pos]='3'; pos++; } break;
						case SDL_SCANCODE_4: if(pos<20) { input_string[pos]='4'; pos++; } break;
						case SDL_SCANCODE_5: if(pos<20) { input_string[pos]='5'; pos++; } break;
						case SDL_SCANCODE_6: if(pos<20) { input_string[pos]='6'; pos++; } break;
						case SDL_SCANCODE_7: if(pos<20) { input_string[pos]='7'; pos++; } break;
						case SDL_SCANCODE_8: if(pos<20) { input_string[pos]='8'; pos++; } break;
						case SDL_SCANCODE_9: if(pos<20) { input_string[pos]='9'; pos++; } break;
						case SDL_SCANCODE_0: if(pos<20) { input_string[pos]='0'; pos++; } break;

						case SDL_SCANCODE_COMMA: if(pos<20) { if((ls||rs) && spaces) { input_string[pos]='<'; } else { input_string[pos]=','; } pos++; } break;
						case SDL_SCANCODE_PERIOD: if(pos<20) { if((ls||rs) && spaces) { input_string[pos]='>'; } else { input_string[pos]='.'; } pos++; } break;

						default: /* ??? */ break;
					} break;
				case SDL_KEYUP:
					switch(event.key.keysym.scancode)
					{
						case SDL_SCANCODE_LSHIFT: ls=0; break;
						case SDL_SCANCODE_RSHIFT: rs=0; break;

						default: /* SHADDUP */ break;
					}break;
				default: /* ?????????????? */ break;
			}
		}
		if(exit || quit) { input=0; return 1; }
		draw(1);
	}
	input_string[pos]='\0';
	input=0;
	draw(1);
	return 0;
}
