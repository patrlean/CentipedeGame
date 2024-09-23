# SFML learning log

## Getting to know with Sprite

> A visual, 2D game object, such as a character or perhaps a zombie, is called a Sprite.
>

> The origin of the Sprite object is the upper left corner of the image.

What can **Sprite** do is to **associate a texture** with it and then **set position on the screen.

### Preparing the Sprite using a Texture

> A texture is a graphic stored in memory, on the graphics processing unit (GPU).

> An object that's made from the Sprite class needs an object made from the Texture class in order to display itself as an image.

```cpp
// Prepare the background photo
Texture textureBackground;

if (!textureBackground.loadFromFile("../graphics/Startup Screen BackGround.png")) 
{
    std::cout << "Can not read background photo" << std::endl;
    return -1; // exit while no picture exists
}

Sprite background(textureBackground);

background.setPosition(0, 0);

// get window size
Vector2u windowSize = window.getSize();
Vector2u textureSize = textureBackground.getSize();

// scale factor
float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

// scale the background
background.setScale(scaleX, scaleY);
```
### Some important features of Sprite

`setPosition()` 

`getPosition()`

## Know how long have passed between two frames

To set the movement of the objects, we need to know its speed and know how long it passes between two frames.

```cpp
Clock clock; // start a clock to count time

while(window.isOpen())
{
    ...
    /* update the scene */
    Time dt = clock.restart(); // count the time interval from the start of clock or last restart 
    distance = speed * dt.asSeconds(); // d = s * t
}
```

# Cpp complie multifile

