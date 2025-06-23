#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SFML/Graphics.hpp>

class SplashScreen {
public:
    SplashScreen();
    void draw(sf::RenderWindow& window);
    bool isTimeUp() const;

private:
    sf::Font font;
    sf::Text titleText;
    sf::Clock clock;
    sf::Text taglineText;
    float duration = 3.0f; // detik, waktu tampil splash screen
};

#endif