/*
Author: Tianyou Zhao 
Class: ECE6122 
Last Date Modified: 24-09-23 11:23:51
Description:
This is the header file of constants.cpp
*/

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
extern const float LASER_COOLDOWN_INTERVAL;

#endif // CONSTANTS_HPP
