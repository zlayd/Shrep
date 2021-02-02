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

void play_music(int music)
{
	switch(music)
	{
		case 0: Mix_FadeInMusic(mus1, -1, 3000); break;
		case 1: Mix_FadeInMusic(mus2, -1, 3000); break;
		case 2: Mix_FadeInMusic(mus3, -1, 3000); break;
		case 3: Mix_FadeInMusic(mus4, -1, 3000); break;
	}
}
