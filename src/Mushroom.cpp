// src/mushroom.cpp
#include "Mushroom.hpp"

void initializeMushrooms(std::list<Mushroom>& mushrooms, sf::Texture& textureMushroom)
/* 
************************************
Initialize all mushrooms in the window
Input: 
mushroom <list> to maintain all mushroom information, position and whether it is hit;
textureMushroom <Texture> contains the png file of the mushroom;
*/
{
    sf::Vector2u textureMushroomSize = textureMushroom.getSize();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed); // 0 -39 relates to the fact that there can only place 71 mushroom in the x axis  
    std::uniform_int_distribution<int> distributionX{0, 70};
    std::uniform_int_distribution<int> distributionY(0, (mushroomFreeArea - topInfoArea) / textureMushroomSize.y - 1);
    // iterate all mushroom 
    for ( int i = 0; i < mushroomNumber; i++)
    {
        Mushroom mushroom;
        // set related features of the mushroom
        mushroom.mushroomSprite.setTexture(textureMushroom);
        mushroom.mushroomSprite.setPosition(distributionX(generator) * textureMushroomSize.x, distributionY(generator) * textureMushroomSize.y + topInfoArea);
        mushroom.hitFlag = 0;
        mushrooms.push_back(mushroom);
    }
}

void fireLaser(std::list<ECE_LaserBlast>& laserBlasts, const sf::Vector2f& laserPosition)
/* 
This function fires a laser and adds member to laserBlasts list
Input: 
laserBlasts list: a list of all lasers
laserPosition : the position of the initial laser.
*/
{
    ECE_LaserBlast laser(laserPosition);
    laserBlasts.push_back(laser);
}

bool checkLaserMushroomCollision(const sf::RectangleShape& laser, const sf::Sprite& mushroom) 
/* 
This function check whether a laser hits a mushroom
Input: 
laser<RectangleShape>
mushroom<Sprite>
*/
{
    return laser.getGlobalBounds().intersects(mushroom.getGlobalBounds());
}

bool checkStarshipMushroomCollision(const sf::Sprite& starship, const std::list<Mushroom>& mushrooms) 
/* 
This function check whether the starship collides with the mushroom
Input: 
starship<Sprite>
mushroom<list<Mushroom>>
*/
{
    bool isCollision = false;
    for ( auto& mushroom : mushrooms) // check whether starship is collide with any of the mushroom 
    {
        isCollision =  isCollision || starship.getGlobalBounds().intersects(mushroom.mushroomSprite.getGlobalBounds());
    }
    return isCollision;
}