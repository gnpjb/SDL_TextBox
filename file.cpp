#include"file.h"

using namespace std;

int main(int argc,char* argv[]){
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){//init sdl, print error otherwise 
		G_ErrorLogger("init");
		return 3;
	}
	
	const int G_ScreenWidth=640;
	const int G_ScreenHeight=480;
	
	SDL_Window* Window=SDL_CreateWindow(//create window
		"TextBox",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		G_ScreenWidth,
		G_ScreenHeight,
		SDL_WINDOW_SHOWN
	);
	if(Window==NULL){//if window fails then output error, quit sdl and exit
		G_ErrorLogger("window create");
		SDL_Quit();
		return 2;
	}
	
	SDL_Renderer* Renderer=SDL_CreateRenderer(//create a renderer
		Window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	
	if(Renderer==NULL){//if it fails to create a render, output de error and exit the program
		G_ErrorLogger("Renderer create");
		SDL_DestroyWindow(Window);
		SDL_Quit();
		return 1;
	}
	
	string TextInBox="";
	
	SDL_Event Event;
	bool Done=false;
	while(!Done){//event handler
		if(!SDL_PollEvent(&Event)){
			SDL_Delay(10);
			continue;
		}
		if(Event.type==SDL_QUIT){
			Done=true;
			continue;
		}
		if(Event.type==SDL_KEYDOWN&&Event.key.keysym.sym==SDLK_BACKSPACE){
			if(TextInBox.lenght()>0){
				TextInBox.pop_back();
			}
			continue;
		}
		if(Event.type==SDL_TEXTINPUT){
			TextInBox.append(Event.text.text);
			continue;
		}
	}
	return 0;
	
	
	
	
	
	
}
