// include/ECE_Centipede.hpp

#ifndef ECE_CENTIPEDE_HPP
#define ECE_CENTIPEDE_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include "Mushroom.hpp" 
#include "Constants.hpp"


class ECE_Centipede : public sf::Sprite {
private:
    float centipedeSpeed;
    float moveOffset;
    float lineOffset;

public:
    bool isHead;
    bool isDownRow;
    sf::Vector2i centipedeDirection;
    sf::Vector2f previousPosition;
    const sf::Texture* textureHead;
    const sf::Texture* textureBody;
    int rowNumber;
    int segmentNo;
    ECE_Centipede* prev;

    // construct function
    ECE_Centipede(const sf::Texture& textureCentipedeHead, const sf::Texture& textureCentipedeBody, const sf::Vector2f& position, const sf::Vector2i& direction, bool isHead);

    // initialize centipede
    std::list<ECE_Centipede> initialCentipede();

    // update centipede position
    void updateCentipedePosition(const std::list<Mushroom>& mushrooms, float dt);

    // update texture
    void updateCentipedeTexture();

    // stay in shape
    void stayInShape();
};

#endif // ECE_CENTIPEDE_HPP
