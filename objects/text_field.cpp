#include "text_field.h"
#include <assert.h>
#include <sstream>

TextField::TextField(Vector2 initPosition, Vector2 initSize)
:Prop(initPosition, initSize)
{
	
}

void TextField::Update()
{
	
}

void TextField::Render(SDL_Renderer* renderer)
{
	if(isRender == true)
	{
		LoadFromRenderedText(renderer);
		isRender = false;
	}
	
	SDL_Rect destination = { static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y) };
	SDL_RenderCopy(renderer, texture, nullptr, &destination);
}

bool TextField::LoadFromRenderedText(SDL_Renderer* renderer)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);

	if(textSurface != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	}
	else
	{
		printf("Unable to render text surface!");
		return false;
	}
	SDL_FreeSurface(textSurface);
	
	return true;
}

bool TextField::LoadFont()
{
	gFont = TTF_OpenFont( "lazy.ttf", 28 );
	assert( gFont != nullptr);
	if( gFont == nullptr )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}
	return true;
}

void TextField::HandleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN )
	{
		if(clicable && IsMouseInside())
		{
			isActive = true;
			isRender = true;
			text = " ";
		}
	}
	
	else if(isActive && e.type == SDL_KEYDOWN)
	{
		//Handle backspace
		if( e.key.keysym.sym == SDLK_RETURN && text[0] != ' ' )
		{
			isRender = false;
			isActive = false;
			clicable = false;
		}
		if( e.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0 )
		{
			text.pop_back();
			if(text.size() == 0)
			{
				text.push_back(' ');
			}
			isRender = true;
		}
		//Handle copy
		else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
		{
			SDL_SetClipboardText( text.c_str() );
		}
		//Handle paste
		else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
		{
			text = SDL_GetClipboardText();
			isRender = true;
		}
	}
	
	//Special text input event
	else if(isActive && e.type == SDL_TEXTINPUT )
	{
		//Not copy or pasting
		if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
		{
			if(static_cast<int>(*e.text.text) >= 48 &&  static_cast<int>(*e.text.text) <= 57)
			{
				//Append character
				if(text.size() == 1 && text[0] == ' ')
				{
					text[0] = *e.text.text;
				}
				else text.push_back(*e.text.text);
				isRender = true;
			}
		}
	}
}


bool TextField::IsMouseInside()
{
		int x,y;
		SDL_GetMouseState(&x, &y);
	
		if( (x < (position.x + size.x)) && x > position.x && y < (position.y + size.y) && y > position.y ) 
		{
			return true;
		}

	return false;
}

int TextField::GetStringAsInt()
{
	int result;
	std::stringstream(text) >> result;
	return result;
}

bool TextField::IsSet()
{
	return clicable;
}