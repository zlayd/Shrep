#!/bin/bash

#compile binaries
gcc -g -ggdb -Wall -o shrep source/*.c -lSDL2 -lSDL2_mixer -lm
