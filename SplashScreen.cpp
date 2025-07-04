#include "SplashScreen.h"
#include <iostream>

SplashScreen::SplashScreen() {
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Gagal load font!" << std::endl;
    }

    bgSplashTexture.loadFromFile("../img/MainImage_crop.png");
    bgSplashSprite.setTexture(bgSplashTexture);

    sf::Vector2u textureSize = bgSplashTexture.getSize();
    bgSplashSprite.setScale(
        800.0f / textureSize.x,
        600.0f / textureSize.y
    );
    // titleText.setFont(font);
    // titleText.setString("GALAXIUM");
    // titleText.setCharacterSize(64);
    // titleText.setFillColor(sf::Color::White);
    // titleText.setPosition(200, 180);

    // taglineText.setFont(font);
    // taglineText.setString("Defend the Galaxy!");
    // taglineText.setCharacterSize(32);
    // taglineText.setFillColor(sf::Color::White);
    // taglineText.setPosition(220, 270);

    // splashTexture.loadFromFile("../img/MainImage.png"); // path ke gambar splash
    // splashSprite.setTexture(splashTexture);

    clock.restart();
}

void SplashScreen::start(){
    clock.restart();
    finished = false;
}

void SplashScreen::update(){
    float totalTime = clock.getElapsedTime().asSeconds();
    float alpha = 255.0f;

    if (totalTime < fadeInTime) {
        alpha = 255.0f * (totalTime / fadeInTime);
    } else if (totalTime < fadeInTime + holdTime) {
        alpha = 255.0f;
    } else if (totalTime < fadeInTime + holdTime + fadeOutTime) {
        float t = (totalTime - fadeInTime - holdTime) / fadeOutTime;
        alpha = 255.0f * (1.0f - t);
    } else {
        alpha = 0.0f;
        finished = true;
    }


    // titleText.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    // taglineText.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    //splashSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

    bgSplashSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
}

void SplashScreen::draw(sf::RenderWindow& window) {
    // window.draw(titleText);
    // window.draw(taglineText);
    //window.draw(splashSprite);
    window.draw(bgSplashSprite);
}

bool SplashScreen::isFinished() const {
    return finished;
}