// src/main.cpp
#include<SFML/Graphics.hpp>
#include<iostream>
#include<random>
#include<list>
#include<deque>
#include<sstream>

#include "Constants.hpp"
#include "Spider.hpp"
#include "Mushroom.hpp"
#include "ECE_Centipede.hpp"
#include "ECE_LaserBlast.hpp"

using namespace sf;

int main()
{
    // Generate main window
    VideoMode vm(1920, 1080);

    RenderWindow window(vm, "Centipede Game", Style::Fullscreen);
    
    // Prepare the background photo
    Texture textureBackground;
    if (!textureBackground.loadFromFile("../graphics/Startup Screen BackGround.png")) { return -1; }
    Sprite background(textureBackground);
    // get window size
    Vector2u windowSize = window.getSize();
    Vector2u textureSize = textureBackground.getSize();
    // scale factor
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    // scale the background
    background.setScale(scaleX, scaleY);

    // prepare the mushrooms
    Texture textureMushroom0;
    Texture textureMushroom1;
    if (!textureMushroom0.loadFromFile("../graphics/Mushroom0.png")||!textureMushroom1.loadFromFile("../graphics/Mushroom1.png")) { return -1; }
    std::list<Mushroom> mushrooms;
    initializeMushrooms(mushrooms, textureMushroom0);

    // prepare the centipede
    Texture textureCentipedeHead;
    Texture textureCentipedeBody;
    if (!textureCentipedeHead.loadFromFile("../graphics/CentipedeHead.png") || !textureCentipedeBody.loadFromFile("../graphics/CentipedeBody.png")){ return -1;}
    ECE_Centipede centipedeHead(textureCentipedeHead, textureCentipedeBody, centipedeStartPoint, Vector2i(- 1, 1), true);
    std::list<ECE_Centipede> centipedeSegments = centipedeHead.initialCentipede();

    

    // Prepare the starship
    Texture textureStarship;
    if (!textureStarship.loadFromFile("../graphics/StarShip.png")){ return -1; }
    Sprite starship(textureStarship);
    Vector2u starshipSize = textureStarship.getSize();
    Vector2f starshipStartPoint = Vector2f(windowSize.x / 2 - starshipSize.x / 2, mushroomFreeArea);
    starship.setPosition(starshipStartPoint);

    // Prepare the remaining lives
    std::vector<Sprite> remainingLives;
    for (int i = 0; i < lives; i++)
    {
        Sprite live(textureStarship);
        live.setPosition(956 + 200 + i * textureStarship.getSize().x, 71);
        remainingLives.push_back(live);
    }

    //prepare the lasers
    std::list<ECE_LaserBlast> laserBlasts;

    //prepare the score
    Text scoreText;
    Font font; // choose a font
    font.loadFromFile("../fonts/KOMIKAP_.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(50); // set size
    scoreText.setPosition(window.getSize().x / 2 - 25, topInfoArea / 2 - 25);
    scoreText.setFillColor(Color::White); // set color

    // prepare "press enter"
    Text PressEnter;
    PressEnter.setFillColor(Color::White);
    PressEnter.setString("Press Enter to restart the game");
    PressEnter.setFont(font);
    PressEnter.setCharacterSize(50);
    // get text boundary
    FloatRect textBounds = PressEnter.getLocalBounds();
    // set origin as the center of the text
    PressEnter.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    // set text position
    PressEnter.setPosition(windowSize.x / 2, windowSize.y / 2 + 100);

    // prepare the spider
    Texture textureSpider;
    if (! textureSpider.loadFromFile("../graphics/spider.png")) { return -1;}
    Vector2f spiderStartPosition = Vector2f(window.getSize().x - textureSpider.getSize().x - offset, mushroomFreeArea - textureSpider.getSize().y - offset);
    ECE_Spider spider(textureSpider, spiderStartPosition);


    // set flag variables
    bool acceptInput = false;

    // control whether to show the background picture
    bool showBackground = true;

    // whether to render the random initial scene                                                          
    bool renderInitScene = false;

    // fire now?
    bool fireNow = false;

    // Does players win?
    bool winner = false;
    bool fail = false;

    // Whether to reset the game
    bool reset = false;

    //start timing
    Clock clock;
    float laserCoolDownTimer = 0;

    // count loops number
    int loopNumber = 0;

    // auto list item

    /*
     * ************************
     * Start the game
     * ************************
     */ 
    while (window.isOpen())
    {
        /* Three parts: processInput, update, render */
        
        loopNumber += 1;
        /*
        ************************
         Process Input
        ************************ 
         */ 
        auto event = sf::Event{};
        while( window.pollEvent(event)){
            //close the window
            if (event.type == Event::KeyReleased){
                acceptInput = true;
            }
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                fireNow = true;
            }
        }
        
        // close the window
        if (acceptInput){
            // close the window
            if ( Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            // render initial scene
            if (Keyboard::isKeyPressed(Keyboard::Return) && showBackground)
            {
                
                renderInitScene = true;
                showBackground = false;
            }
        }
        
        /*
        ***************************
        Update the scene
        ***************************
        */ 
        Time dt = clock.restart();
        if (renderInitScene)
        {
            // First update all objects position

            

            // control the moving direction of the starship
            // check input -- update position -- check collision 
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                Vector2f starshipPosition = starship.getPosition();
                Vector2f starshipPositionCopy = starshipPosition;
                if ( starshipPosition.x > 0)
                {
                    starship.setPosition(starshipPosition.x - starshipSpeed * dt.asSeconds(), starshipPosition.y);
                    if (checkStarshipMushroomCollision(starship, mushrooms))
                    {
                        starship.setPosition(starshipPositionCopy);
                    }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                Vector2f starshipPosition = starship.getPosition();
                Vector2f starshipPositionCopy = starshipPosition;
                if ( starshipPosition.x < windowSize.x - textureStarship.getSize().x)
                {
                    starship.setPosition(starshipPosition.x + starshipSpeed * dt.asSeconds(), starshipPosition.y);
                    if (checkStarshipMushroomCollision(starship, mushrooms))
                    {
                        starship.setPosition(starshipPositionCopy);
                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                Vector2f starshipPosition = starship.getPosition();
                Vector2f starshipPositionCopy = starshipPosition;
                if (starshipPosition.y > topInfoArea)
                {
                    starship.setPosition(starshipPosition.x, starshipPosition.y - starshipSpeed * dt.asSeconds());
                    if (checkStarshipMushroomCollision(starship, mushrooms))
                    {
                        starship.setPosition(starshipPositionCopy);
                    }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                Vector2f starshipPosition = starship.getPosition();
                Vector2f starshipPositionCopy = starshipPosition;
                if (starshipPosition.y < windowSize.y - textureStarship.getSize().y)
                {
                    starship.setPosition(starshipPosition.x, starshipPosition.y + starshipSpeed * dt.asSeconds());
                    if (checkStarshipMushroomCollision(starship, mushrooms))
                    {
                        starship.setPosition(starshipPositionCopy);
                    }
                }
            }

            // control laser
            if (fireNow)
            {
                laserCoolDownTimer += dt.asSeconds();
                if ( laserCoolDownTimer > laserCoolDownInterval) 
                {
                    Vector2f starshipPosition = starship.getPosition();
                    Vector2f laserPosition = starshipPosition;
                    laserPosition.x = laserPosition.x + textureStarship.getSize().x / 2 - 2;
                    laserPosition.y = laserPosition.y - 10;
                    fireLaser(laserBlasts, laserPosition);
                    laserCoolDownTimer = 0;
                    fireNow = false;
                }
            }
            
            // update all lasers
            for (auto& laser : laserBlasts)
            {
                laser.updatePosition(dt.asSeconds());
            }
            
            // update spider movement
            spider.updatePosition(dt.asSeconds());

            // check starship collision with spider
            if (starship.getGlobalBounds().intersects(spider.getGlobalBounds()))
            // The spider collides with the starship
            // starship relocates to start point 
            // remaining lives minus one
            {
                starship.setPosition(starshipStartPoint);
                lives -= 1;
            }

            // Mushroom Collision Check: with laser and spider
            // check collision of mushroom and laser
            // check collision of mushroom and spider
            auto mushroomIt = mushrooms.begin();
            while (mushroomIt != mushrooms.end()) 
            {
                bool mushroomDestroyed = false;
                // first check spider with mushroom
                if (spider.isSpiderCollideWithMushroom(spider, mushroomIt -> mushroomSprite))
                {
                    mushroomIt = mushrooms.erase(mushroomIt);
                    continue;
                }
                
                // second check laser with mushroom
                auto laserIt = laserBlasts.begin();
                while (laserIt != laserBlasts.end()) 
                {
                    // check laser boundary
                    if (laserIt -> isOffScreen(window))
                    {
                        laserIt = laserBlasts.erase(laserIt);
                    }else
                    {
                        // check collision
                        if (checkLaserMushroomCollision(laserIt->shape, mushroomIt->mushroomSprite)) 
                        {
                            // process mushroom
                            mushroomIt->hitFlag += 1;
                            mushroomIt->mushroomSprite.setTexture(textureMushroom1);

                            // if destroyed
                            if (mushroomIt->hitFlag == 2) 
                            {
                                mushroomDestroyed = true;
                                score += 4;
                            }

                            // delete mushroom
                            laserIt = laserBlasts.erase(laserIt);  
                        } else 
                        {
                            ++laserIt; // move to next laser
                        }
                    }
                }
                if (mushroomDestroyed) 
                {
                    mushroomIt = mushrooms.erase(mushroomIt);  // delete mushroom
                } else 
                {
                    ++mushroomIt;  
                }
            }

            
            // Laser Collision Check: centipede with lasers && spider with lasers
            auto segmentIt = centipedeSegments.begin();
            while (segmentIt != centipedeSegments.end())
            {
                segmentIt -> updateCentipedeTexture();
                bool collision = false;
                auto laserIt = laserBlasts.begin();
                while( laserIt != laserBlasts.end())
                {                                                                  
                    // spider part
                    if (spider.isSpiderCollideWithLaser(spider, laserIt -> shape))
                    // if laser collides with a spider, spider reset to start point 
                    // laser disappears
                    // add scores 
                    // continue
                    {
                        laserIt = laserBlasts.erase(laserIt);
                        spider.setPosition(spiderStartPosition);
                        score += spiderScore;
                        continue;
                    }

                    // centipede part
                    if (segmentIt -> getGlobalBounds().intersects(laserIt->shape.getGlobalBounds()))
                    // if collide, then laser erase, segment changes into mushroom
                    {
                        
                        collision = true;
                        // add score
                        if (segmentIt -> isHead)
                        {
                            score += centipedeHeadScore;
                        }else{
                            score += centipedeBodyScore;
                        }

                        // erase laser
                        laserIt = laserBlasts.erase(laserIt);

                        // set a new mushroom
                        Mushroom mushroomInplace;
                        Vector2f currentPosition = segmentIt -> getPosition();
                        mushroomInplace.mushroomSprite.setTexture(textureMushroom0);
                        mushroomInplace.mushroomSprite.setPosition(currentPosition);
                        mushroomInplace.hitFlag = 0;
                        mushrooms.push_back(mushroomInplace);

                        // remove the segment
                        auto prevSegmentIt = segmentIt -> prev;
                        segmentIt = centipedeSegments.erase(segmentIt);
                        if (segmentIt != centipedeSegments.end()) {
                            segmentIt -> isHead = true;  // 设置下一个段为头部
                            segmentIt -> isDownRow = false;
                            segmentIt -> prev = prevSegmentIt;
                            segmentIt -> updateCentipedeTexture(); // update centipede texture
                        }
                        break;
                    }
                    else{
                        laserIt++;
                    }
                }
                if (!collision){
                    segmentIt++;
                }
            }  

            // update all centipedes
            for (auto& segment : centipedeSegments)
            {
                segment.updateCentipedePosition(mushrooms, dt.asSeconds());
                segment.stayInShape();
            }

            // if (loopNumber % 100 == 0){
            //     auto segmentIt = centipedeSegments.begin();
            //     std::cout<<"We have "<<centipedeSegments.size()<<" segments now!"<<std::endl;
            //     while (segmentIt != centipedeSegments.end())
            //     {
            //         if (segmentIt -> isHead){
            //             std::cout<<">>";
            //         }
            //         std::cout<<"("<<segmentIt -> getPosition().x<<" "<<segmentIt -> getPosition().y<<")";
            //         std::cout<<" R"<<segmentIt -> rowNumber;
            //         std::cout<<" No"<<segmentIt -> segmentNo<<"|";
            //         segmentIt++;
            //     }
            //     std::cout<<std::endl;
            //     std::cout<<std::endl;
            // }    
            
            // update score
            scoreText.setString(std::to_string(score));  
        }

        // control game starting and stopping
        // game ends if no more centipede segments
        if ( centipedeSegments.size() == 0)
        // show winner page and reset to start page
        {
            winner = true;
            reset = true;
        }else if( lives == 0)
        // game ends if no lives
        {
            fail = true;
            reset = true;
        }

        if (reset)
        // back to start page and reset all flags
        // laser, mushroom, starship, centipede, spider, score, and remaining lives
        {
            
            renderInitScene = false;
            reset = false;
            showBackground = false;

            // clear lasers
            laserBlasts.clear(); 

            // clear mushrooms
            mushrooms.clear();
            initializeMushrooms(mushrooms, textureMushroom0);

            // reset starship
            starship.setPosition(starshipStartPoint);

            // reset centipede
            centipedeSegments.clear();
            centipedeHead.setTexture(textureCentipedeHead);
            centipedeHead.setPosition(centipedeStartPoint);
            centipedeHead.centipedeDirection = Vector2i(- 1, 1);
            centipedeHead.isHead = true;
            centipedeSegments = centipedeHead.initialCentipede();
            for (auto segmentIt = centipedeSegments.begin(); segmentIt != centipedeSegments.end();)
            {
                segmentIt -> updateCentipedeTexture();
                segmentIt ++;
            }

            // reset spider
            spider.setPosition(spiderStartPosition);

            // reset player
            lives = 3;
            score = 0;
        }

        /* 
        ***************************
        Render Graphics 
        ***************************
        */ 
        window.clear();
        //show background
        if (showBackground) {
            window.draw(background);
        }
        // render initial scene
        else if (renderInitScene) {
            // mushrooms
            for ( const auto& mushroom : mushrooms)
            {
                window.draw(mushroom.mushroomSprite);
            }
            
            // remaining lives
            for ( int i = 0; i < lives; i++)
            {
                window.draw(remainingLives[i]);
            }

            // lasers
            for ( const auto& laser : laserBlasts)
            {
                window.draw(laser.shape);
            }

            // spider
            window.draw(spider);
            
            // score
            window.draw(scoreText);

            // starship
            window.draw(starship);

            // centipede
            for ( const auto& segment : centipedeSegments )
            {
                window.draw(segment);
            }
        } 
        // show winner page and detect "enter" to restart the game
        else if (winner){
            // set "Congratulations" text
            Text textWinner;
            textWinner.setFillColor(Color::White);
            textWinner.setString(" Congratulations! ");
            textWinner.setFont(font);
            textWinner.setCharacterSize(100);
            // get text boundary
            textBounds = textWinner.getLocalBounds();
            // set origin as the center of the text
            textWinner.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            // set text position
            textWinner.setPosition(windowSize.x / 2, windowSize.y / 2);

            // set "press enter to restart the game" text
            Text PressEnter;
            PressEnter.setFillColor(Color::White);
            PressEnter.setString("Press Enter to restart the game");
            PressEnter.setFont(font);
            PressEnter.setCharacterSize(50);
            // get text boundary
            textBounds = PressEnter.getLocalBounds();
            // set origin as the center of the text
            PressEnter.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            // set text position
            PressEnter.setPosition(windowSize.x / 2, windowSize.y / 2 + 100);

            window.draw(textWinner);
            window.draw(PressEnter);

            //detect "enter" to restart the game and reset winner flag
            if( Keyboard::isKeyPressed(Keyboard::Enter))
            {
                winner = false;
                showBackground = true;
            }
        }
        else if( fail ) {
            // showing fail page and detect "enter" to restart the game 
            // set "Congratulations" text
            Text textFail;
            textFail.setFillColor(Color::White);
            textFail.setString(" You Fail ");
            textFail.setFont(font);
            textFail.setCharacterSize(100);
            // get text boundary
            textBounds = textFail.getLocalBounds();
            // set origin as the center of the text
            textFail.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            // set text position
            textFail.setPosition(windowSize.x / 2, windowSize.y / 2);

            window.draw(textFail);
            window.draw(PressEnter);

            //detect "enter" to restart the game and reset fail flag
            if( Keyboard::isKeyPressed(Keyboard::Enter))
            {
                fail = false;
                showBackground = true;
            }
        }
        window.display();
        
    }
    return 0;
}
