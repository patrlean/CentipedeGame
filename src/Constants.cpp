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
const int topInfoArea = 143;
const int mushroomFreeArea = 1001;
const int mushroomNumber = 30;
const int lineHeight = 26;
const int offset = 20;

// set award
const int mushroomScore = 4;
const int centipedeBodyScore = 10;
const int centipedeHeadScore = 100;
const int spiderScore = 300;

// set monsters
const float centipedeSpeed = 350; 
const float spiderSpeed = 300;
const int centipedeBodyNumber = 11;
const sf::Vector2f centipedeStartPoint = sf::Vector2f(1654.0f, 116.0f);

// set user capability
int score = 0;
int lives = 3;
const float starshipSpeed = 450;
const float laserSpeed = 1800;
const float LASER_COOLDOWN_INTERVAL = 0.5;