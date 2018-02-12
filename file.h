#include<SDL2/SDL.h>
#include<string>
#include<fstream>
#include<iostream>

void G_ErrorLogger(string cause){//given a name output the last error of sdl
	cout<<cause<<": "<<SDL_GetError()<<endl;
}


