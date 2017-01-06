#include "prop.h"

class Actor : public Prop{

public:
    Actor(Vector2 initPosition, Vector2 initSize, std::string spritePath);
    void handleEvents(SDL_Event event);
    bool am_i_in(Vector2 clickPosition,Vector2 midPosition, double side);


};

