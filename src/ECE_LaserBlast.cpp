/*
Author: Tianyou Zhao 
Class: ECE6122 
Last Date Modified: 24-09-22 11:48:32
Description:
This file defines the class of laser controlling its movement and appearance on the screen.
*/

// src/ECE_LaserBlast

#include "ECE_LaserBlast.hpp"

/* 
This class constructs all lasers;
All parameters about lasers are defined: speed, color, size;
updatePosition function will update the position of laser by setPosition function in Sprite;
isOffScreen function will check whether the laser goes off the screen.
*/
ECE_LaserBlast::ECE_LaserBlast(const sf::Vector2f& startPostion )
    : laserSpeed(::LASER_SPEED),
    color(sf::Color::Red),
    size(sf::Vector2f(5.0, 10.0))
{
    shape.setSize(size);
    shape.setFillColor(color);
    shape.setPosition(startPostion);
}

//  update the position of all lasers in the scene
void ECE_LaserBlast::updatePosition(float dt)
{   
    shape.setPosition(shape.getPosition().x, shape.getPosition().y - laserSpeed * dt);
}

// check whether the laser is out the screen
// return true when it is off screen, otherwise it is false
bool ECE_LaserBlast::isOffScreen( const sf::RenderWindow& window)
{
    return shape.getPosition().y < 0;
}
