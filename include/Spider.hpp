/*
Author: Tianyou Zhao 
Class: ECE6122 
Last Date Modified: 24-09-20 19:41:46
Description:
This is the header file of Spider.cpp
*/

// include/Spider.hpp

#ifndef SPIDER_HPP
#define SPIDER_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include "Constants.hpp"

class ECE_Spider : public sf::Sprite{
    private:
        float spiderSpeed;
        std::default_random_engine gen;
        std::uniform_int_distribution<int> dis{-1, 1};
        float holdTime;
        float thresholdTime;
        bool isOffScreenNow;
    public:
        sf::Vector2i spiderDirection;
        std::uniform_real_distribution<float> disThreshold;

        ECE_Spider(const sf::Texture& textureSpider, const sf::Vector2f& spiderStartPosition);
        // construct function

    void updateDirection();
    // update spider direction with uniform dis in -1 or 1

    void updatePosition(const float& dt);
    // update spider position
    
    bool isSpiderCollideWithMushroom(const ECE_Spider& spider, const Sprite& mushroom);
    //  check whether the spider collides with a mushroom

    bool isSpiderCollideWithLaser(const ECE_Spider& spider, const sf::RectangleShape& laser);
    // check whether the spider collides with a laser

    bool isOffScreen();

};

#endif