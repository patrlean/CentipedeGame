/*
Author: Tianyou Zhao
Class: ECE6122
Last Date Modified: 2024-09-23 10:39:22
Description:
This file defines class of centipede, which controls the movement, collision detection, update centipede texture and stay in shape
*/

// src/Centipede.cpp

#include "ECE_Centipede.hpp"

// Initialise the centipede with its head segment
// Constructor
ECE_Centipede::ECE_Centipede(const sf::Texture & textureCentipedeHead, const sf::Texture & textureCentipedeBody, const sf::Vector2f& position, const sf::Vector2i& direction, bool isHead)
    : isHead(isHead), 
    centipedeDirection(direction), 
    textureHead(&textureCentipedeHead), 
    textureBody(&textureCentipedeBody),
    moveOffset(22), // Distance to move in one step
    centipedeSpeed(::CENTIPEDE_SPEED), // Initialize the speed of the centipede
    lineOffset(LINE_HEIGHT), 
    isDownRow(false), // Flag to check if the centipede should move to the next row
    rowNumber(0), // 
    segmentNo(0), // Segment number of the centipede part
    currentMovement(sf::Vector2f(0, 0)), // current movement of the centipede
    previousMovement(sf::Vector2f(0, 0)), // previous movement of the centipede
    prev(nullptr) // Pointer to the previous segment
{
    // Set texture based on whether it's the head or body
    this->setTexture(isHead ? *textureHead : *textureBody);
    this->setOrigin(textureHead -> getSize().x / 2, textureHead -> getSize().y / 2);
    this->setRotation(180);
    this->setPosition(position);
}

// Initial a long centipede with 11 bodies
// input: ECE_Centipede centipede - the head of the centipede
// return: std::list<ECE_Centipede> - the list of all segments of centipede
std::list<ECE_Centipede> ECE_Centipede::initialCentipede(ECE_Centipede centipede)
{
    std::list<ECE_Centipede> centipedeSegments;
    sf::Vector2f currentPosition = this -> getPosition();
    sf::Vector2i centipedeDirection = sf::Vector2i(- 1, 1);
    this -> segmentNo = 1;
    // Add the head to the list first
    centipedeSegments.push_back(centipede);
    this -> setScale(22.f / 24.f, 24.0f / 24.0f);
    // Generate body segments
    for (int i = 0; i < CENTIPEDE_BODY_NUMBER; i++) {
        // Calculate the position for each body segment
        currentPosition.x -= moveOffset * centipedeDirection.x;  // Move left or right based on direction
        currentPosition.y = this -> getPosition().y;
        // Create the body segment
        ECE_Centipede bodySegment(*textureHead, *textureBody, currentPosition, centipedeDirection, false);
        bodySegment.rowNumber = 0;
        bodySegment.prev = &centipedeSegments.back();
        bodySegment.segmentNo = i + 2;
        centipedeSegments.push_back(bodySegment);  
    }
    return centipedeSegments;
}

// Update the centipede's position and check for collisions
// input: list of mushrooms and delta time for movement calculations
void ECE_Centipede::updateCentipedePosition(const std::list<Mushroom>& mushrooms, float dt)
{
    sf::Vector2f currentPosition = this -> getPosition();
    
    // set texture rotation by direction
    if (centipedeDirection.x == -1)
    {
        this->setRotation(180);  // face left
    }
    else
    {
        this->setRotation(0);  // face right
    }

    // check if this is head, if head, check collision,if not new position is the position of the last segment
    bool collisionDetected = false;
    for (const auto& mushroom : mushrooms) {
        if (this->getGlobalBounds().intersects(mushroom.mushroomSprite.getGlobalBounds())) {
            collisionDetected = true;
            break;
        }
    }
    // if collision enter next row
    if (currentPosition.y > MUSHROOM_FREE_AREA) {
        this -> centipedeDirection.y = -1; // move up
    }else if(currentPosition.y < TOP_INFO_AREA - 24) {
        this -> centipedeDirection.y = 1; // move down
    }

    // if collision enter next row
    if (collisionDetected || currentPosition.x < 22 || currentPosition.x > 1920 - 22) {
        if(!this -> isDownRow)
        {
            // change direction 
            centipedeDirection.x = - centipedeDirection.x;  // 
            
            // move to next row
            currentPosition.y += lineOffset * centipedeDirection.y;  
            currentPosition.x += dt * centipedeSpeed * centipedeDirection.x;
            this -> isDownRow = true;
            this -> rowNumber += 1; // detect how many rows have entered
        }else{
            currentPosition.x += dt * centipedeSpeed * centipedeDirection.x;
        }
    } 
    else 
    {
        // otherwise, move 
        currentPosition.x += dt * centipedeSpeed * centipedeDirection.x;
        this -> isDownRow = false;
    }
    // update centipede position
    this->setPosition(currentPosition);
} 

void ECE_Centipede::updateCentipedePositionByMovement(const std::list<Mushroom>& mushrooms, float dt)
{
    sf::Vector2f currentPosition = this -> getPosition();
    sf::Vector2f NewPosition = currentPosition;
    
    // set texture rotation by direction
    if (centipedeDirection.x == -1)
    {
        this->setRotation(180);  // face left
    }
    else
    {
        this->setRotation(0);  // face right
    }

    // check if this is head, if head, check collision,if not new position is the position of the last segment
    bool collisionDetected = false;
    for (const auto& mushroom : mushrooms) {
        if (this->getGlobalBounds().intersects(mushroom.mushroomSprite.getGlobalBounds())) {
            collisionDetected = true;
            break;
        }
    }
    // if collision enter next row
    if (currentPosition.y > MUSHROOM_FREE_AREA) {
        this -> centipedeDirection.y = -1; // move up
    }else if(currentPosition.y < TOP_INFO_AREA - 24) {
        this -> centipedeDirection.y = 1; // move down
    }

    if (this -> isHead)
    {
        // if collision enter next row
        if (collisionDetected || currentPosition.x < 22 || currentPosition.x > 1920 - 22) {
            if(!this -> isDownRow)
            {
                // change direction 
                centipedeDirection.x = - centipedeDirection.x;  // 
                
                // move to next row
                NewPosition.y += lineOffset * centipedeDirection.y;  
                NewPosition.x += dt * centipedeSpeed * centipedeDirection.x;
                this -> isDownRow = true;
                this -> rowNumber += 1; // detect how many rows have entered

                // update previous movement
                this -> previousMovement = this -> currentMovement;
                this -> currentMovement = sf::Vector2f(dt * centipedeSpeed * centipedeDirection.x, lineOffset * centipedeDirection.y); // update current movement
            }else{
                NewPosition.x += dt * centipedeSpeed * centipedeDirection.x;
                this -> previousMovement = this -> currentMovement;
                this -> currentMovement = sf::Vector2f(dt * centipedeSpeed * centipedeDirection.x, 0);
            }
        }
        else
        {
            // update previous movement
            this -> previousMovement = this -> currentMovement;
            this -> currentMovement = sf::Vector2f(dt * centipedeSpeed * centipedeDirection.x, 0);
            NewPosition.x += dt * centipedeSpeed * centipedeDirection.x;
            this -> isDownRow = false;
        }
    }
    else // not head
    {
        if(this -> prev != nullptr)
        {
            // get the movement of the previous segment
            this -> currentMovement = this -> prev -> previousMovement;
            NewPosition.x = currentPosition.x + currentMovement.x;
            NewPosition.y = currentPosition.y + currentMovement.y;
            this -> isDownRow = false;
        }
    }
    // update centipede position
    this->setPosition(NewPosition);
} 


// Update the centipede's texture based on whether it's the head or body
void ECE_Centipede::updateCentipedeTexture()
// check the ishead var and set correct texture
{
    if (this -> isHead)
    {
        this -> setTexture(*textureHead);
    }else{
        this-> setTexture(*textureBody);
    }
}

// check the relative position of this segment and the previous segment
void ECE_Centipede::stayInShape()
{
    // previous segment is not null
    if (this -> prev != nullptr && !this -> isHead){
        sf::Vector2f thisPosition = this -> getPosition();
        sf::Vector2f previousPosition = this -> prev ->getPosition();
        // if they are in the same row, then check whether they are in good shape.
        // only body will stay in shape
        if (this -> rowNumber == this -> prev -> rowNumber)
        {
            thisPosition.x = previousPosition.x - centipedeDirection.x * 22;
            thisPosition.y = previousPosition.y;
            this -> setPosition(thisPosition);
        }
    }
}
