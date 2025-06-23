#include "Asteroid.h"
#include <SFML/Graphics.hpp>

Asteroid::Asteroid(float x, float y, float speed, sf::Texture* texture) : speed(speed), texture(texture) {
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setPosition(x, y);
    if (texture) {
        shape.setTexture(texture);
    } else {
        shape.setFillColor(sf::Color::Green); // Default color, kalo texture ga ke load
    }
}

void Asteroid::update(float dt) {
    shape.move(0.f, speed * dt);
    shape.rotate(rotationSpeed * dt);
}

void Asteroid::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

bool Asteroid::isOffScreen(float screenHeight) const {
    return shape.getPosition().y > screenHeight;
}

sf::FloatRect Asteroid::getBounds() const {
    return shape.getGlobalBounds();
}