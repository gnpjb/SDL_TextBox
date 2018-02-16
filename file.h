#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<string>
#include<fstream>
#include<iostream>


void G_ErrorLogger(std::string cause){//given a name output the last error of sdl
	std::cout<<cause<<": "<<SDL_GetError()<<std::endl;
}

//non-oop aproach
void G_ClearBox(SDL_Renderer* Renderer){//prints a clear box to the renderer
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












//oop aproach
class G_TextBox{
	public:	
		G_TextBox();
		void CloseFont(){if(Font!=NULL){TTF_CloseFont(Font);}}
		void AppendText(std::string tmp_Text){Text.append(tmp_Text);}//add text to the end of Text
		void EraseOneChar();//errase last char
		void G_ClearBox(SDL_Renderer* Renderer);//clear the textbox
		void SetBoxBackgroundColor(SDL_Color tmp_BoxBackgroundColor){G_BoxBackgroundColor=tmp_BoxBackgroundColor;}//change background color
		void SetBoxOutlineColor(SDL_Color tmp_BoxOutlineColor){G_BoxOutlineColor=tmp_BoxOutlineColor;}//change outline color
		void CopyRectForSize(SDL_Rect tmp_Rect);//set Rect using a SDL_Rect
		void DefineSize(int S_x,int S_y,int S_w,int S_h){Rect.x=S_x;Rect.y=S_y;Rect.w=S_w;Rect.h=S_h;}//define the meassures of Rect
		void Update(SDL_Renderer* Renderer);//update the textbox in screen
		bool SetFontToHeight(std::string FontPath);//set font according to the height of Rect
		bool SetFont(std::string FontPath,int FontSize);//set font manually
		void SetTextColor(SDL_Color tmp_TextColor){TextColor=tmp_TextColor;}//set the text color
	private:
		std::string Text="";
		SDL_Rect Rect;
		SDL_Color G_BoxBackgroundColor;
		SDL_Color G_BoxOutlineColor;
		TTF_Font* Font;
		SDL_Color TextColor;
};



//Methods--------------------------------------------------------------

G_TextBox::G_TextBox(){
	Rect.x=100;
	Rect.w=440;
	Rect.y=100;
	Rect.h=50;
	G_BoxBackgroundColor={255,255,255};
	G_BoxOutlineColor={0,0,0};
	TextColor={0,0,0};
}

void G_TextBox::G_ClearBox(SDL_Renderer* Renderer){//prints a clear box to the renderer


	
	//set 4 Uint8 to hold the original drawing color the renderer had to restore it at the end of the function
	Uint8 OriginalRed;
	Uint8 OriginalGreen;
	Uint8 OriginalBlue;
	Uint8 OriginalAlpha;
	SDL_GetRenderDrawColor(Renderer,&OriginalRed,&OriginalGreen,&OriginalBlue,&OriginalAlpha);
	
	//create a rect fill it with box background color then create an outline for it
	SDL_SetRenderDrawColor(Renderer,G_BoxBackgroundColor.r,G_BoxBackgroundColor.g,G_BoxBackgroundColor.b,SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(Renderer,&Rect);
	
	SDL_SetRenderDrawColor(Renderer,G_BoxOutlineColor.r,G_BoxOutlineColor.g,G_BoxOutlineColor.b,SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(Renderer,&Rect);
	
	//Set the render draw color to the original, update the renderer and exit the function
	SDL_SetRenderDrawColor(Renderer,OriginalRed,OriginalGreen,OriginalBlue,OriginalAlpha);
	SDL_RenderPresent(Renderer);
	return;
}

bool G_TextBox::SetFontToHeight(std::string FontPath){
	const char* tmp_FontPath=FontPath.c_str();
	int FontSize=1;
	bool Done=false;
	int Fails=0;
	while(!Done){
		/*starts by font size 1, if it is smaller than the rect
		 * height then it adds 1. if it is greater or equalls it
		 * takes 1 from font size and breaks the cicle
		 * Lastly if it fails 10 times it prints that it failed and
		 * return false
		 */
		Font=TTF_OpenFont(tmp_FontPath,FontSize);
		if(Fails==10){
			std::cout<<"Failed 10 times in a row"<<std::endl;
			return false;
		}
		if(Font==NULL){
			Fails++;
			std::cout<<"FontOpeningInSetFont:"<<TTF_GetError()<<std::endl;
			continue;
		}
		if(TTF_FontHeight(Font)<Rect.h){
			FontSize++;
			continue;
		}
		if(TTF_FontHeight(Font)>=Rect.h){
			FontSize--;
			Done=true;
			continue;
		}
	}
	Font=TTF_OpenFont(tmp_FontPath,FontSize);
	return true;
}

bool G_TextBox::SetFont(std::string FontPath,int FontSize){//given a font file and a size it opens it,if it fails it prints error and returns false
	const char* tmp_FontPath=FontPath.c_str();
	Font=TTF_OpenFont(tmp_FontPath,FontSize);
	if(Font==NULL){
		std::cout<<"SetFontFailed:"<<TTF_GetError()<<std::endl;
		return false;
	}
	return true;
}


void G_TextBox::EraseOneChar(){//if the string is not empty it erases the last character
	if(!Text.empty()){
		Text.pop_back();
	}
}

void G_TextBox::Update(SDL_Renderer* Renderer){
	SDL_Rect tmp_Rect=Rect;
	if(Font==NULL){//if font is null output error and exit function
		std::cout<<"Update fail Font=NULL"<<std::endl;
		return;
	}
	if(Text.empty()){//if text is empty make a clear box
		this->G_ClearBox(Renderer);
		return;
	}
	
	
	
	//check that the lenght of the string fits in the box and truncate(taking the first part out) if not
	bool Done=false;
	std::string RenderedText=Text;
	int WidhtOfText;
	while(!Done){
		{
			const char* tmp_TextHolder=RenderedText.c_str();
			TTF_SizeText(Font,tmp_TextHolder,&WidhtOfText,NULL);
		}
		if(WidhtOfText>tmp_Rect.w){
			RenderedText=RenderedText.substr(1,-1);
			continue;
		}
		else{
			Done=true;
			continue;
		}
	}
	
	const char* tmp_RenderedText=RenderedText.c_str();
	SDL_Surface* TextSurface=TTF_RenderText_Solid(Font,tmp_RenderedText,TextColor);//load a surface with the text
	if(TextSurface==NULL){
		
		std::cout<<"Update fail Surface=NULL:"<<TTF_GetError()<<std::endl;
		return;
	}
	SDL_Texture* TextTexture=SDL_CreateTextureFromSurface(Renderer,TextSurface);//create a texture from the surface
	if(TextTexture==NULL){
		std::cout<<"Update fail Texture=NULL:"<<SDL_GetError()<<std::endl;
		SDL_FreeSurface(TextSurface);
		return;
	}
	this->G_ClearBox(Renderer);//clear the box
	SDL_QueryTexture(TextTexture,NULL,NULL,&tmp_Rect.w,&tmp_Rect.h);//prepare the texture
	SDL_RenderCopy(Renderer,TextTexture,NULL,&tmp_Rect);//copy to the renderer
	SDL_RenderPresent(Renderer);//update renderer
	//free memory
	SDL_DestroyTexture(TextTexture);
	SDL_FreeSurface(TextSurface);
	return;
}
