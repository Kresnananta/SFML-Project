#include "Menu_State.h"
#include <cmath>

MainMenu::MainMenu() {
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");
    titleText.setFont(font);
    titleText.setString("GALAXIUM");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(268, 119);

    startButton.setSize(sf::Vector2f(200, 60));
    startButton.setFillColor(sf::Color(200, 200, 200, 220));
    startButton.setPosition(300, 240);

    startText.setFont(font);
    startText.setString("Start");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::Black);

    sf::FloatRect startButtonBounds = startButton.getGlobalBounds();
    sf::FloatRect startTextBounds = startText.getLocalBounds();
    startText.setOrigin(startTextBounds.left + startTextBounds.width / 2.0f,
                        startTextBounds.top + startTextBounds.height / 2.0f);
    startText.setPosition(
        startButtonBounds.left + startButtonBounds.width / 2.0f,
        startButtonBounds.top + startButtonBounds.height / 2.0f
    );

    leadButton.setSize(sf::Vector2f(200, 60));
    leadButton.setFillColor(sf::Color(200, 200, 200, 220));
    leadButton.setPosition(300, 330);

    leadText.setFont(font);
    leadText.setString("Leaderboard");
    leadText.setCharacterSize(30);
    leadText.setFillColor(sf::Color::Black);

    sf::FloatRect leadButtonBounds = leadButton.getGlobalBounds();
    sf::FloatRect leadTextBounds = leadText.getLocalBounds();
    leadText.setOrigin(leadTextBounds.left + leadTextBounds.width / 2.0f,
                        leadTextBounds.top + leadTextBounds.height / 2.0f);
    leadText.setPosition(
        leadButtonBounds.left + leadButtonBounds.width / 2.0f,
        leadButtonBounds.top + leadButtonBounds.height / 2.0f
    );

    exitButton.setRadius(30.0f);
    exitButton.setFillColor(sf::Color(200, 50, 50, 220));
    exitButton.setPosition(20, 522);
    exitText.setFont(font);
    exitText.setString("X");
    exitText.setCharacterSize(32);
    exitText.setFillColor(sf::Color::White);

    sf::FloatRect txtBounds = exitText.getLocalBounds();
    exitText.setOrigin(txtBounds.left + txtBounds.width / 2.0f, txtBounds.top + txtBounds.height / 2.0f);
    exitText.setPosition(
        exitButton.getPosition().x + exitButton.getRadius(),
        exitButton.getPosition().y + exitButton.getRadius()
    );
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(titleText);
    window.draw(startButton);
    window.draw(startText);
    window.draw(leadButton);
    window.draw(leadText);
    window.draw(exitButton);
    window.draw(exitText);
    window.display();
}

bool MainMenu::isStartClicked(sf::RenderWindow& window, sf::Event& event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if(startButton.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

bool MainMenu::isExitClicked(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f center = exitButton.getPosition() + sf::Vector2f(exitButton.getRadius(), exitButton.getRadius());
        float dx = mousePos.x - center.x;
        float dy = mousePos.y - center.y;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist <= exitButton.getRadius()) {
            return true;
        }
    }
    return false;
}