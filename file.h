#include<SDL2/SDL.h>
#include<string>
#include<fstream>
#include<iostream>


void G_ErrorLogger(std::string cause){//given a name output the last error of sdl
	std::cout<<cause<<": "<<SDL_GetError()<<std::endl;
}

void G_ClearBox(SDL_Renderer* Renderer){
	Uint8 G_BackgroundColor[3]={192,192,192};//Background color in rgb
	SDL_Rect G_Box;//create a rect for the text box and the colors for its outline and background
	Uint8 G_BoxBackgroundColor[3]={255,255,255};
	Uint8 G_BoxOutlineColor[3]={0,0,0};
	G_Box.x=100;
	G_Box.w=440;
	G_Box.y=100;
	G_Box.h=50;
	
	//set 4 Uint8 to hold the original drawing color the renderer had to restore it at the end of the function
	Uint8 OriginalRed;
	Uint8 OriginalGreen;
	Uint8 OriginalBlue;
	Uint8 OriginalAlpha;
	SDL_GetRenderDrawColor(Renderer,&OriginalRed,&OriginalGreen,&OriginalBlue,&OriginalAlpha);

	//set Background to Background color
	SDL_SetRenderDrawColor(Renderer,G_BackgroundColor[0],G_BackgroundColor[1],G_BackgroundColor[2],SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Renderer);
	
	//create a rect fill it with box background color then create an outline for it
	SDL_SetRenderDrawColor(Renderer,G_BoxBackgroundColor[0],G_BoxBackgroundColor[1],G_BoxBackgroundColor[2],SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(Renderer,&G_Box);
	
	SDL_SetRenderDrawColor(Renderer,G_BoxOutlineColor[0],G_BoxOutlineColor[1],G_BoxOutlineColor[2],SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(Renderer,&G_Box);
	
	//Set the render draw color to the original, update the renderer and exit the function
	SDL_SetRenderDrawColor(Renderer,OriginalRed,OriginalGreen,OriginalBlue,OriginalAlpha);
	SDL_RenderPresent(Renderer);
	return;
}

