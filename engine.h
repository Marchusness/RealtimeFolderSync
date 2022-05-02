#ifndef H_ENGINE
#define H_ENGINE
#include <map>
#include <SFML/Graphics.hpp>

class Textures;
class Scene;

class Engine
{
private:
    static Engine* engine;
    Textures* textures;
    sf::RenderWindow* window;
    Scene* currentScene;
    sf::Clock deltaTimeClock;
    sf::Time previousFrameTime;

    //magic will happen with this
    //template <typename T>
    //Scene* createScene();
    //using funcp = Scene*(*)();
    //std::map<std::string, funcp> sceneCreateres;

public:
    Engine();
    ~Engine();
    static Engine* getEngine();

    void loop();
    //void LoadScene(std::string scene);
    static Textures* getTextures();
    static sf::Texture* getTexture(std::string name);
    static sf::Int32 getDetaTime();
    static sf::RenderWindow* getWindow();
};

#endif