#include "GameUI.h"
#include <iostream>

GameUI::GameUI(){
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cout << "Error loading font" << std::endl;
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
    gameOverText.setPosition(255, 250);

    overlay.setSize(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent black

    // Overlay semi-transparan
    overlay.setSize(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    // Tombol Try Again
    tryAgainButton.setSize(sf::Vector2f(200, 60));
    tryAgainButton.setFillColor(sf::Color(200, 200, 200, 220));
    tryAgainButton.setPosition(415, 350);

    tryAgainText.setFont(font);
    tryAgainText.setString("Try Again");
    tryAgainText.setCharacterSize(32);
    tryAgainText.setFillColor(sf::Color::Black);
    // tryAgainText.setPosition(340, 360);
    sf::FloatRect buttonBounds = tryAgainButton.getGlobalBounds();
    sf::FloatRect textBounds = tryAgainText.getLocalBounds();
    tryAgainText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                        textBounds.top + textBounds.height / 2.0f);
    tryAgainText.setPosition(
        buttonBounds.left + buttonBounds.width / 2.0f,
        buttonBounds.top + buttonBounds.height / 2.0f
    );

    returnMenuButton.setSize(sf::Vector2f(200, 60));
    returnMenuButton.setFillColor(sf::Color(200, 200, 200, 220));
    returnMenuButton.setPosition(185, 350); // 80px from left, same y as Try Again

    returnMenuText.setFont(font);
    returnMenuText.setString("Menu");
    returnMenuText.setCharacterSize(32);
    returnMenuText.setFillColor(sf::Color::Black);

    sf::FloatRect btnBounds = returnMenuButton.getGlobalBounds();
    sf::FloatRect txtBounds = returnMenuText.getLocalBounds();
    returnMenuText.setOrigin(txtBounds.left + txtBounds.width / 2.0f, txtBounds.top + txtBounds.height / 2.0f);
    returnMenuText.setPosition(
        btnBounds.left + btnBounds.width / 2.0f,
        btnBounds.top + btnBounds.height / 2.0f
    );
}



void GameUI::setLives(int lives) {
    this->lives = lives;
    livesText.setString("Lives: " + std::to_string(lives));
}

void GameUI::setScore(int score) {
    this->score = score;
    scoreText.setString("Score: " + std::to_string(score));
}

void GameUI::setGameOver(bool gameOver){
    this->gameOver = gameOver;
}

void GameUI::draw(sf::RenderWindow& window) {
    window.draw(livesText);
    window.draw(scoreText);
    if (gameOver) {
        window.draw(overlay);
        window.draw(gameOverText);
        window.draw(tryAgainButton);
        window.draw(tryAgainText);
        window.draw(returnMenuButton);
        window.draw(returnMenuText);
    }
}

bool GameUI::isTryAgainClicked(sf::RenderWindow& window, sf::Event& event) {
    if (!gameOver) return false;
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (tryAgainButton.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

bool GameUI::isReturnMenuClicked(sf::RenderWindow& window, sf::Event& event) {
    if (!gameOver) return false;
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (returnMenuButton.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}