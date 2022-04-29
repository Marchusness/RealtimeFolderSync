#ifndef H_TEXTURES
#define H_TEXTURES

#include <SFML/Graphics.hpp>
#include <map>

class Textures
{
private:
    std::map<std::string, sf::Texture*> textures;
    sf::Texture* underfined;

public:
    Textures();
    ~Textures();

    sf::Texture* getTexture(std::string);
};

#endif