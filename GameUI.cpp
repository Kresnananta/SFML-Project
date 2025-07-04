#include "GameUI.h"
#include <iostream>

GameUI::GameUI(){
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }
    if (!tryAgainTexture.loadFromFile("../img/Replay_BTN.png")) {
        std::cout << "Error loading Try Again button texture" << std::endl;
    }
    if (!returnMenuTexture.loadFromFile("../img/Menu_BTN.png")) {
        std::cout << "Error loading Return Menu button texture" << std::endl;
    }

    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 10);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 40);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(255, 200);

    elapsedTimeText.setFont(font);
    elapsedTimeText.setCharacterSize(24);
    elapsedTimeText.setFillColor(sf::Color::White);
    elapsedTimeText.setPosition(650, 10); // pojok kanan atas

    overlay.setSize(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent black

    // Overlay semi-transparan
    overlay.setSize(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    // Tombol Try Again
    tryAgainSprite.setTexture(tryAgainTexture);
    tryAgainSprite.setPosition(510, 350);
    tryAgainSprite.setScale(0.5f, 0.5f);


    tryAgainText.setFont(font);
    tryAgainText.setString("Try Again");
    tryAgainText.setCharacterSize(24);
    tryAgainText.setFillColor(sf::Color::White);
    tryAgainText.setPosition(495, 470);
    

    // Tombol Return to Menu
    returnMenuSprite.setTexture(returnMenuTexture);
    returnMenuSprite.setPosition(185, 350);
    returnMenuSprite.setScale(0.5f, 0.5f);


    returnMenuText.setFont(font);
    returnMenuText.setString("Menu");
    returnMenuText.setCharacterSize(24);
    returnMenuText.setFillColor(sf::Color::White);
    returnMenuText.setPosition(200, 470);

}



void GameUI::setLives(int lives) {
    this->lives = lives;
    livesText.setString("Lives: " + std::to_string(lives));
}

void GameUI::setScore(int score) {
    this->score = score;
    scoreText.setString("Score: " + std::to_string(score));
}

void GameUI::setElapsedTime(float seconds) {
    int mins = static_cast<int>(seconds) / 60;
    int secs = static_cast<int>(seconds) % 60;
    elapsedTimeText.setString("Time: " + std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs));
}

void GameUI::setGameOver(bool gameOver){
    this->gameOver = gameOver;
}

void GameUI::draw(sf::RenderWindow& window) {
    window.draw(livesText);
    window.draw(scoreText);
    window.draw(elapsedTimeText);
    if (gameOver) {
        window.draw(overlay);
        window.draw(gameOverText);
        window.draw(tryAgainSprite);
        window.draw(returnMenuSprite);
        window.draw(tryAgainText);
        window.draw(returnMenuText);
    }
}

bool GameUI::isTryAgainClicked(sf::RenderWindow& window, sf::Event& event) {
    if (!gameOver) return false;
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (tryAgainSprite.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

bool GameUI::isReturnMenuClicked(sf::RenderWindow& window, sf::Event& event) {
    if (!gameOver) return false;
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (returnMenuSprite.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}