// include/Constants.hpp

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/System/Vector2.hpp>

// Scene settings
extern const int topInfoArea;
extern const int mushroomFreeArea;
extern const int mushroomNumber;
extern const int lineHeight;
extern const int offset;

// Awards
extern const int mushroomScore;
extern const int centipedeBodyScore;
extern const int centipedeHeadScore;
extern const int spiderScore;

// Monsters
extern const float centipedeSpeed;
extern const float spiderSpeed;
extern const int centipedeBodyNumber;
extern const sf::Vector2f centipedeStartPoint;

// User capability
extern int score;
extern int lives;
extern const float starshipSpeed;
extern const float laserSpeed;
extern const float laserCoolDownInterval;

#endif // CONSTANTS_HPP
