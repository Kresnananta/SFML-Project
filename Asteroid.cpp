#include "Asteroid.h"
#include <SFML/Graphics.hpp>

Asteroid::Asteroid(float x, float y, float speed, sf::Texture* texture) : speed(speed), texture(texture) {
    float scale = 1.5f;
    if (texture) {
        shape.setTexture(texture);
        sf::Vector2u texSize = texture->getSize();
        shape.setSize(sf::Vector2f(texSize.x * scale, texSize.y * scale));
    } else {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        shape.setFillColor(sf::Color::Green); // Default color, kalo texture ga ke load
    }
    shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f); // <-- poros di tengah
    shape.setPosition(x, y);
}

void Asteroid::update(float dt) {
    if (animating) {
        animTimer += dt;
        if (animTimer >= frameTime) {
            animTimer -= frameTime;
            currentFrame++;
            if (currentFrame < 8) {
                explosionSprite.setTextureRect(sf::IntRect(currentFrame * 96, 0, 96, 96));
            } else {
                animating = false; // animasi selesai
            }
        }
        // Asteroid tidak bergerak saat animasi
        return;
    }
    if(!destroyed){
        shape.move(0.f, speed * dt);
        shape.rotate(rotationSpeed * dt);
    }
    
}

void Asteroid::draw(sf::RenderWindow& window) const {
    if(animating){
        window.draw(explosionSprite);
    }
    else if(!destroyed){
        window.draw(shape);
    }
}

void Asteroid::destroy(sf::Texture* explosionTex) {
    destroyed = true;
    animating = true;
    explosionTexture = explosionTex;
    explosionSprite.setTexture(*explosionTexture);
    explosionSprite.setOrigin(48, 48); // tengah 96x96
    explosionSprite.setPosition(shape.getPosition());
    currentFrame = 0;
    animTimer = 0.f;
    // Set frame pertama
    explosionSprite.setTextureRect(sf::IntRect(0, 0, 96, 96));
}

bool Asteroid::isOffScreen(float screenHeight) const {
    return shape.getPosition().y > screenHeight;
}

sf::FloatRect Asteroid::getBounds() const {
    //return shape.getGlobalBounds();
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();
    float angle = shape.getRotation() * 3.14159265f / 180.f;

    // Hitbox setengah ukuran, tetap di tengah asteroid
    sf::Vector2f halfSize = size * 0.5f * 0.5f; // 0.5f untuk setengah ukuran
    sf::Vector2f center = pos;

    // Kembalikan bounding box axis-aligned (tanpa rotasi, cukup untuk kebanyakan kasus)
    return sf::FloatRect(
        center.x - halfSize.x,
        center.y - halfSize.y,
        size.x * 0.5f,
        size.y * 0.5f
    );
}