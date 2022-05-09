#ifndef H_SCENE_SETUP
#define H_SCENE_SETUP
#include <SFML/Graphics.hpp>
#include "Scene.h"

class UI_Item;

class Scene_Setup : public Scene
{
public:
	Scene_Setup();
	~Scene_Setup();

	void update();
	void draw();
private:
	UI_Item* UI;
};

#endif // H_SCENE_SETUP
