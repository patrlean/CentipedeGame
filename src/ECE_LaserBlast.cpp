// src/ECE_LaserBlast

#include "ECE_LaserBlast.hpp"

ECE_LaserBlast::ECE_LaserBlast(const sf::Vector2f& startPostion )
    : laserSpeed(::laserSpeed),
    color(sf::Color::Red),
    size(sf::Vector2f(6.0, 14.0))
{
    shape.setSize(size);
    shape.setFillColor(color);
    shape.setPosition(startPostion);
}
/* 
This class constructs all lasers;
All parameters about lasers are defined: speed, color, size;
updatePosition function will update the position of laser by setPosition function in Sprite;
isOffScreen function will check whether the laser goes off the screen.
*/


void ECE_LaserBlast::updatePosition(float dt)
{   
    shape.setPosition(shape.getPosition().x, shape.getPosition().y - laserSpeed * dt);
}

bool ECE_LaserBlast::isOffScreen( const sf::RenderWindow& window)
// check whether the laser is out the screen
// return true when it is off screen, otherwise it is false
{
    return shape.getPosition().y < 0;
}
