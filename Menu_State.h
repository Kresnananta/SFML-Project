#ifndef MENU_STATE_H
#define MENU_STATE_H
#include <SFML/Graphics.hpp>

class MainMenu {
public:
    MainMenu();
    void draw(sf::RenderWindow& window);
    bool isStartClicked(sf::RenderWindow& window, sf::Event& event);
    bool isExitClicked(sf::RenderWindow& window, sf::Event& event);

private:
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text leadText;
    sf::RectangleShape startButton;
    sf::RectangleShape leadButton;
    sf::CircleShape exitButton;
    sf::Text exitText;

};

#endif