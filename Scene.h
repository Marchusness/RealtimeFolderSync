#ifndef H_SCENE
#define H_SCENE

class Scene
{
public:
	virtual void handleKeyPress(sf::Event);
	virtual void update() = 0;
};

#endif