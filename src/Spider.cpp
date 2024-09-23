// src/Spider.cpp
#include "Spider.hpp" // Include your global constants definition

// Constructor
ECE_Spider::ECE_Spider(const sf::Texture& textureSpider, const sf::Vector2f& spiderStartPosition)
    : spiderSpeed(::spiderSpeed),  // Initialize with global constant
      holdTime(0),                 // Initialize holdTime
      thresholdTime(1),            // Initialize threshold time
      isOffScreenNow(false),       // Initialize isOffScreenNow flag
      disThreshold(0, 1),          // Initialize random threshold
      spiderDirection(-1, -1)      // Initialize spider direction
{
    this->setTexture(textureSpider);  // Set the texture for the spider
    this->setPosition(spiderStartPosition);  // Set initial position of the spider
}

// Update the spider's movement direction
void ECE_Spider::updateDirection() {
    spiderDirection = sf::Vector2i(dis(gen), dis(gen));  // Randomly change direction
}

// Update the spider's position based on time elapsed (dt)
void ECE_Spider::updatePosition(const float& dt) {
    sf::Vector2f newPosition;
    holdTime += dt;  // Accumulate time

    // If accumulated time exceeds threshold, change direction
    if (holdTime > thresholdTime + disThreshold(gen)) {  
        this->updateDirection();  // Update the movement direction
        holdTime = 0;  // Reset the hold time
    }

    // Check if the spider is off-screen
    if (this->isOffScreen()) {
        if (this->isOffScreenNow) {
            // Move the spider in the current direction
            newPosition.x = this->getPosition().x + dt * spiderDirection.x * spiderSpeed;
            newPosition.y = this->getPosition().y + dt * spiderDirection.y * spiderSpeed;
        } else {
            // Reverse the spider's direction when off-screen
            this->spiderDirection.x = -this->spiderDirection.x;
            this->spiderDirection.y = -this->spiderDirection.y;
            newPosition.x = this->getPosition().x + dt * spiderDirection.x * spiderSpeed;
            newPosition.y = this->getPosition().y + dt * spiderDirection.y * spiderSpeed;
            this->isOffScreenNow = true;  // Mark that the spider is off-screen
        }
    } else {
        // If the spider is within the screen boundaries, update the position normally
        newPosition.x = this->getPosition().x + dt * spiderDirection.x * spiderSpeed;
        newPosition.y = this->getPosition().y + dt * spiderDirection.y * spiderSpeed;
        this->isOffScreenNow = false;  // Spider is back on the screen
    }

    // Set the new position for the spider
    this->setPosition(newPosition);
}

// Check if the spider collides with a mushroom
bool ECE_Spider::isSpiderCollideWithMushroom(const ECE_Spider& spider, const sf::Sprite& mushroom) {
    return spider.getGlobalBounds().intersects(mushroom.getGlobalBounds());
}

// Check if the spider collides with a laser
bool ECE_Spider::isSpiderCollideWithLaser(const ECE_Spider& spider, const sf::RectangleShape& laser) {
    return spider.getGlobalBounds().intersects(laser.getGlobalBounds());
}

// Check if the spider is off the screen boundaries
bool ECE_Spider::isOffScreen() {
    return (this->getPosition().x < 48) || (this->getPosition().x > 1920 - 48) ||
           (this->getPosition().y < topInfoArea) || (this->getPosition().y > mushroomFreeArea - 29);
}
