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

private:
    sf::RectangleShape shape;
    float speed;
    sf::Texture* texture = nullptr;
    float rotationSpeed = 50.0f;
};

#endif