// src/ECE_LaserBlast

#ifndef ECE_LASERBLAST
#define ECE_LASERBLAST

#include "Constants.hpp"
#include <SFML/Graphics.hpp>

class ECE_LaserBlast : public sf::Sprite {
/* 
This class constructs all lasers;
All parameters about lasers are defined: speed, color, size;
updatePosition function will update the position of laser by setPosition function in Sprite;
isOffScreen function will check whether the laser goes off the screen.
*/
private:
    float laserSpeed;
    sf::Color color;
    sf::Vector2f size;
public:
    sf::RectangleShape shape;

    ECE_LaserBlast(const sf::Vector2f& startPostion );

    void updatePosition(float dt);

    bool isOffScreen( const sf::RenderWindow& window);
    // check whether the laser is out the screen
    // return true when it is off screen, otherwise it is false
};

#endif