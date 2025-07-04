#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SFML/Graphics.hpp>

class SplashScreen {
public:
    SplashScreen();
    void start();
    void update();
    void draw(sf::RenderWindow& window);
    bool isFinished() const;

private:
    sf::Texture bgSplashTexture;
    sf::Sprite bgSplashSprite;
    sf::Font font;
    // sf::Text titleText;
    sf::Clock clock;
    // sf::Text taglineText;
    sf::Sprite splashSprite;
    sf::Texture splashTexture;
    float duration = 3.0f; // detik, waktu tampil splash screen
    float fadeInTime = 1.0f;
    float holdTime = 2.0f;
    float fadeOutTime = 1.0f;
    bool finished = false;
};

#endif