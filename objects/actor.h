#include "prop.h"

class Actor : public Prop{

public:
    Actor(Vector2 initPosition, Vector2 initSize, std::string spritePath);
    void HandleEvents(SDL_Event event);
    bool IsMouseInside(Vector2 clickPosition,Vector2 midPosition, double side);


};

