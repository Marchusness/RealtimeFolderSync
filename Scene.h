#ifndef H_SCENE
#define H_SCENE

#include <SFML/Graphics.hpp>

class Scene
{
public:
	virtual ~Scene();
	virtual void handleKeyPress(sf::Event);
	virtual void update() = 0;
	virtual void draw() = 0;
protected:
};

#endif