/*
Author: Tianyou Zhao 
Class: ECE6122 
Last Date Modified: 24-09-20 19:41:05
Description:
This is the header file of Mushroom.cpp
*/

// include/Mushroom.hpp

#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <chrono>
#include <random>
#include "ECE_LaserBlast.hpp"

struct Mushroom {
    sf::Sprite mushroomSprite;
    int hitFlag; // 0 - unhit; 1 - hit; 2 - hit twice
};

void initializeMushrooms(std::list<Mushroom>& mushrooms, sf::Texture& textureMushroom);
/* 
************************************
Initialize all mushrooms in the window
Input: 
mushroom <list> to maintain all mushroom information, position and whether it is hit;
textureMushroom <Texture> contains the png file of the mushroom;
*/

void fireLaser(std::list<ECE_LaserBlast>& laserBlasts, const sf::Vector2f& laserPosition);
/* 
This function fires a laser and adds member to laserBlasts list
Input: 
laserBlasts list: a list of all lasers
laserPosition : the position of the initial laser.
*/

bool checkLaserMushroomCollision(const sf::RectangleShape& laser, const sf::Sprite& mushroom);
/* 
This function check whether a laser hits a mushroom
Input: 
laser<RectangleShape>
mushroom<Sprite>
*/

bool checkStarshipMushroomCollision(const sf::Sprite& starship, const std::list<Mushroom>& mushrooms);
/* 
This function check whether the starship collides with the mushroom
Input: 
starship<Sprite>
mushroom<list<Mushroom>>
*/

#endif // MUSHROOM_HPP
