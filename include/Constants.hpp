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
extern const int TOP_INFO_AREA;
extern const int MUSHROOM_FREE_AREA;
extern const int MUSHROOM_NUMBER;
extern const int LINE_HEIGHT;
extern const int OFFSET;

// Awards
extern const int MUSHROOM_SCORE;
extern const int CENTIPEDE_BODY_SCORE;
extern const int CENTIPEDE_HEAD_SCORE;
extern const int SPIDER_SCORE;

// Monsters
extern const float CENTIPEDE_SPEED;
extern const float SPIDER_SPEED;
extern const int CENTIPEDE_BODY_NUMBER;
extern const sf::Vector2f CENTIPEDE_START_POINT;

// User capability
extern int SCORE;
extern int LIVES;
extern const float STARSHIP_SPEED;
extern const float LASER_SPEED;
extern const float LASER_COOLDOWN_INTERVAL;

#endif // CONSTANTS_HPP
