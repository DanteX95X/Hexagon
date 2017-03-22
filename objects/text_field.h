#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H
#include "prop.h"
#include "actor.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class TextField : public Prop
{
public:
	TextField();
	TextField(Vector2 position, Vector2 size);
	
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	
	bool LoadFromRenderedText(SDL_Renderer* renderer);
	bool LoadFont();
	
	std::string GetText();
	void SetText(std::string newText);
	void SetColor(SDL_Color textColor);
	
	void HandleEvents(SDL_Event& event);
	bool IsMouseInside();
	
	int GetStringAsInt();
	
	bool IsSet();
	
private:
	bool isActive = false;
	bool isRender = false;
	bool clicable = true;
	std::string text = "Enter text";
	int stringAsInt;
	TTF_Font *gFont = nullptr;
	SDL_Color textColor = {0,0,0,0xff};
	
};

#endif