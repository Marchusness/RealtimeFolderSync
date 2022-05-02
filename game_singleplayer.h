#ifndef H_GAME_SINGLEPLAYER
#define H_GAME_SINGLEPLAYER
#include <SFML/graphics.hpp>
#include "scene.h"

class Map;

class Game_Singleplayer : public Scene
{
public:
	Game_Singleplayer();
	~Game_Singleplayer();

	void update();
	void draw();
private:
	Map* map;
};

#endif // H_GAME_SINGLEPLAYER
