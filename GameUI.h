#ifndef GAMEUI_H
#define GAMEUI_H
#include <SFML/Graphics.hpp>
#include <string>

class GameUI{
public:
    GameUI();

    void setLives(int lives);
    void setScore(int score);
    void setGameOver(bool gameOver);
    void draw(sf::RenderWindow& window);
    bool isTryAgainClicked(sf::RenderWindow& window, sf::Event& event);
    bool isReturnMenuClicked(sf::RenderWindow& window, sf::Event& event);

    const sf::Font& getFont() const { return font; };

private:
    sf::Font font;
    sf::Text livesText;
    sf::Text scoreText;
    sf::Text gameOverText;

    sf::RectangleShape overlay;
    sf::RectangleShape tryAgainButton;
    sf::Text tryAgainText;
    sf::RectangleShape returnMenuButton;
    sf::Text returnMenuText;

    int lives = 3;
    int score = 0;
    bool gameOver = false;
};

#endif