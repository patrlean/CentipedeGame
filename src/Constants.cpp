/*
Author: Tianyou Zhao
Class: ECE6122
Last Date Modified: 24-09-23 10:38:45
Description:
Define all constant variables, like scene, award, monsters, and user capability
*/

// src/Constants.cpp
#include "Constants.hpp"

// set scene 
const int TOP_INFO_AREA = 143;
const int MUSHROOM_FREE_AREA = 1001;
const int MUSHROOM_NUMBER = 30;
const int LINE_HEIGHT = 26;
const int OFFSET = 20;

// set award
const int MUSHROOM_SCORE= 4;
const int CENTIPEDE_BODY_SCORE = 10;
const int CENTIPEDE_HEAD_SCORE = 100;
const int SPIDER_SCORE = 300;

// set monsters
const float CENTIPEDE_SPEED = 350; 
const float SPIDER_SPEED = 300;
const int CENTIPEDE_BODY_NUMBER = 11;
const sf::Vector2f CENTIPEDE_START_POINT = sf::Vector2f(1654.0f, 116.0f);

// set user capability
int SCORE = 0;
int LIVES = 3;
const float STARSHIP_SPEED = 450;
const float LASER_SPEED = 1800;
const float LASER_COOLDOWN_INTERVAL = 0.5;