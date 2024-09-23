// src/Centipede.cpp
#include "ECE_Centipede.hpp"

// Initialise the centipede with its head segment
// Constructor
ECE_Centipede::ECE_Centipede(const sf::Texture & textureCentipedeHead, const sf::Texture & textureCentipedeBody, const sf::Vector2f& position, const sf::Vector2i& direction, bool isHead)
    : isHead(isHead), 
    centipedeDirection(direction), 
    textureHead(&textureCentipedeHead), 
    textureBody(&textureCentipedeBody),
    moveOffset(22),
    centipedeSpeed(::centipedeSpeed),
    lineOffset(lineHeight),
    isDownRow(false),
    rowNumber(0),
    segmentNo(0),
    prev(nullptr)
{
    this->setTexture(isHead ? *textureHead : *textureBody);
    this->setOrigin(textureHead -> getSize().x / 2, textureHead -> getSize().y / 2);
    this->setRotation(180);
    this->setPosition(position);
}

// Initial a long centipede with 11 bodies
// input: ECE_Centipede centipede - the head of the centipede
// return: std::list<ECE_Centipede> - the list of all segments of centipede
std::list<ECE_Centipede> ECE_Centipede::initialCentipede()
{
    std::list<ECE_Centipede> centipedeSegments;
    sf::Vector2f currentPosition = this -> getPosition();
    sf::Vector2i centipedeDirection = sf::Vector2i(- 1, 1);
    this -> segmentNo = 1;
    // Add the head to the list first
    centipedeSegments.push_back(*this);
    this -> setScale(22 / 24, 24 / 24);
    // Generate body segments
    for (int i = 0; i < centipedeBodyNumber; i++) {
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

void ECE_Centipede::updateCentipedePosition(const std::list<Mushroom>& mushrooms, float dt)
{
    sf::Vector2f currentPosition = this -> getPosition();
    
    // 根据方向设置 texture 旋转
    if (centipedeDirection.x == -1)
    {
        this->setRotation(180);  // 面向左
    }
    else
    {
        this->setRotation(0);  // 面向右
    }

    // check if this is head, if head, check collision,if not new position is the position of the last segment
    bool collisionDetected = false;
    for (const auto& mushroom : mushrooms) {
        if (this->getGlobalBounds().intersects(mushroom.mushroomSprite.getGlobalBounds())) {
            collisionDetected = true;
            break;
        }
    }

    // 如果检测到碰撞，掉头并向下挪一行
    if (collisionDetected || currentPosition.x < 22 || currentPosition.x > 1920 - 22) {
        if(!this -> isDownRow)
        {
            // 改变方向
            centipedeDirection.x = - centipedeDirection.x;  // 水平方向反转
            
            // 向下移动一行
            currentPosition.y += lineOffset * centipedeDirection.y;  // 假设moveOffset是足够向下移动一行的距离
            currentPosition.x += dt * centipedeSpeed * centipedeDirection.x;
            this -> isDownRow = true;
            this -> rowNumber += 1; // detect how many rows have entered
        }else{
            currentPosition.x += dt * centipedeSpeed * centipedeDirection.x;
        }
    } 
    else 
    {
        // 否则，正常移动 
        currentPosition.x += dt * centipedeSpeed * centipedeDirection.x;
        this -> isDownRow = false;
    }
    // 更新蜈蚣的位置
    this->setPosition(currentPosition);
} 



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

void ECE_Centipede::stayInShape()
// check the relative position of this segment and the previous segment
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
        // if (!this -> isDownRow && !this -> prev -> isDownRow && this->rowNumber != this -> prev -> rowNumber && this -> centipedeDirection.x != this -> prev -> centipedeDirection.x )
        // {
        //     thisPosition.y = previousPosition.y;
        //     thisPosition.x = previousPosition.x + centipedeDirection.x * 22;
        //     this -> setPosition(thisPosition);
        //     this -> isDownRow = true;
        // }
    }
}
