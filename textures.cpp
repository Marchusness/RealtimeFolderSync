#include "textures.h"
#include <filesystem>
#include <string>
#include <fstream>

Textures::Textures()
{
    for (const auto & file : std::filesystem::directory_iterator("textures/"))
    {
        //create new texture
        sf::Texture* texture = new sf::Texture();
        //load texture
        texture->loadFromFile(file.path().string());
        //add to dictionary
        std::pair<std::string, sf::Texture*> pair(file.path().stem().string(), texture);
        textures.insert(pair);
    }
    underfined = getTexture("underfined");
}

Textures::~Textures()
{
}

sf::Texture* Textures::getTexture(std::string name)
{
    auto it = textures.find(name);
    if (it == textures.end())
    {
        return underfined;
    }
    return it->second;
}