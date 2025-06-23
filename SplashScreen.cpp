#include "SplashScreen.h"

SplashScreen::SplashScreen() {
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");
    titleText.setFont(font);
    titleText.setString("GALAXIUM");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(200, 180);

    taglineText.setFont(font);
    taglineText.setString("Defend the Galaxy!");
    taglineText.setCharacterSize(32);
    taglineText.setFillColor(sf::Color::White);
    taglineText.setPosition(220, 270);

    clock.restart();
}

void SplashScreen::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(titleText);
    window.draw(taglineText);
    window.display();
}

bool SplashScreen::isTimeUp() const {
    return clock.getElapsedTime().asSeconds() > duration;
}