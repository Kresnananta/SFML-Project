#ifndef MENU_STATE_H
#define MENU_STATE_H
#include <SFML/Graphics.hpp>
#include "Leaderboard.h"

class MainMenu {
public:
    MainMenu();
    void draw(sf::RenderWindow& window); // draw menu
    void draw(sf::RenderWindow& window, const std::vector<LeaderboardEntry>& entries, sf::Font& font); // draw overlay leaderboard
    void drawLeaderboard(sf::RenderWindow& window, const std::vector<LeaderboardEntry>& entries, sf::Font& font);
    bool isStartClicked(sf::RenderWindow& window, sf::Event& event);
    bool isExitClicked(sf::RenderWindow& window, sf::Event& event);
    bool isLeadClicked(sf::RenderWindow& window, sf::Event& event);
    bool isBackClicked(sf::RenderWindow& window, sf::Event& event);
    void processEvent(const sf::Event& event);
    bool showingLeaderboard = false;
    sf::Sprite leadPlatSprite;

private:
    sf::Texture bgMenuTexture;
    sf::Sprite bgMenuSprite;
    sf::Font font;
    sf::Text titleText;

    sf::RectangleShape leaderboardOverlay;

    sf::Texture startButtonTexture;
    sf::Sprite startButtonSprite;

    sf::Texture exitButtonTexture;
    sf::Sprite exitButtonSprite;

    sf::Texture leadButtonTexture;
    sf::Sprite leadButtonSprite;

    sf::Texture leadPlatTexture;

    sf::Texture backButtonTexture;
    sf::Sprite backButtonSprite;
    
    

};

#endif