#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

class Asteroid{
public:
    Asteroid(float x, float y, float speed, sf::Texture* texture);
    
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen(float screenHeight) const;
    sf::FloatRect getBounds() const;
    void destroy(sf::Texture* explosionTexture);
    bool isDestroyed() const { return destroyed; }
    bool isAnimating() const { return animating; }

private:
    sf::RectangleShape shape;
    float speed;
    sf::Texture* texture = nullptr;
    float rotationSpeed = 50.0f;
    bool destroyed = false;
    bool animating = false;
    sf::Texture* explosionTexture = nullptr;
    sf::Sprite explosionSprite;
    int currentFrame = 0;
    float frameTime = 0.1f; // waktu per frame (detik)
    float animTimer = 0.f;
};

#endif