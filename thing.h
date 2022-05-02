#ifndef H_THING
#define H_THING
#include <SFML/Graphics.hpp>

class Thing
{
public:
	Thing();
	~Thing();


	void update();
	void draw();

	void setPos(float x, float y);
	void setVel(float x, float y);
	float addVel(float x, float y);

private:
	sf::Sprite sprite;
	float posX;
	float posY;
	float velX;
	float velY;
};

#endif // !H_THING
