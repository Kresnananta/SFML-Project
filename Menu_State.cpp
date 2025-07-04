#include "Menu_State.h"

#include <cmath>
#include <iostream>

MainMenu::MainMenu() {
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");

    bgMenuTexture.loadFromFile("../img/Background.png");
    bgMenuSprite.setTexture(bgMenuTexture);

    float scaleY = 600.0f / bgMenuTexture.getSize().y;
    bgMenuSprite.setScale(scaleY, scaleY);
    float bgWidth = bgMenuTexture.getSize().x * scaleY;
    float offsetX = (800.0 - bgWidth) / 2.0f;
    bgMenuSprite.setPosition(offsetX, 0);

    if(!startButtonTexture.loadFromFile("../img/Start_BTN.png")){
        std::cout << "Gagal load start_button\n";
    }
    if(!exitButtonTexture.loadFromFile("../img/Exit_BTN.png")){
        std::cout << "Gagal load exit_button\n";
    }
    if(!leadButtonTexture.loadFromFile("../img/Rating_BTN.png")){
        std::cout << "Gagal load leaderboard_button\n";
    }
    if(!leadPlatTexture.loadFromFile("../img/Platform.png")){
        std::cout << "Gagal load Platform\n";
    }
    if(!backButtonTexture.loadFromFile("../img/Back_BTN.png")){
    std::cout << "Gagal load back_button\n";
}

    titleText.setFont(font);
    titleText.setString("GALAXIUM");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(268, 119);
    
    startButtonSprite.setTexture(startButtonTexture);
    startButtonSprite.setPosition(300, 240);
    startButtonSprite.setScale(0.5f, 0.5f);

    exitButtonSprite.setTexture(exitButtonTexture);
    exitButtonSprite.setPosition(300, 330);
    exitButtonSprite.setScale(0.5f, 0.5f);

    leadButtonSprite.setTexture(leadButtonTexture);
    leadButtonSprite.setPosition(710, 520);
    leadButtonSprite.setScale(0.3f, 0.3f);

    backButtonSprite.setTexture(backButtonTexture);
    backButtonSprite.setPosition(40, 520);
    backButtonSprite.setScale(0.3f, 0.3f);

    leaderboardOverlay.setSize(sf::Vector2f(720, 510));
    leaderboardOverlay.setPosition(40, 45);
    leaderboardOverlay.setFillColor(sf::Color(0, 0, 0, 150));
}

void MainMenu::processEvent(const sf::Event& event) {
    if (showingLeaderboard && event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (!leadPlatSprite.getGlobalBounds().contains(mousePos)) {
            showingLeaderboard = false;
        }
    }
    // tambahin kalo ada yg lain
}

void MainMenu::drawLeaderboard(sf::RenderWindow& window, const std::vector<LeaderboardEntry>& entries, sf::Font& font) {
    window.draw(bgMenuSprite);
    window.draw(leaderboardOverlay);

    // Header
    float baseX = 100.0f;
    float startY = 120.0f;
    float colRank = baseX;
    float colName = baseX + 120;
    float colScore = baseX + 300;
    float colTime = baseX + 430;

    sf::Text headerRank("RANK", font, 24);
    headerRank.setFillColor(sf::Color::Yellow);
    headerRank.setPosition(colRank, startY - 40);
    window.draw(headerRank);

    sf::Text headerName("NAME", font, 24);
    headerName.setFillColor(sf::Color::Yellow);
    headerName.setPosition(colName, startY - 40);
    window.draw(headerName);

    sf::Text headerScore("SCORE", font, 24);
    headerScore.setFillColor(sf::Color::Yellow);
    headerScore.setPosition(colScore, startY - 40);
    window.draw(headerScore);

    sf::Text headerTime("TIME", font, 24);
    headerTime.setFillColor(sf::Color::Yellow);
    headerTime.setPosition(colTime, startY - 40);
    window.draw(headerTime);

    // Entries
    int rank = 1;
    for (const auto& entry : entries) {
        if (rank > 10) break;

        sf::Text textRank(std::to_string(rank), font, 22);
        textRank.setFillColor(sf::Color::White);
        textRank.setPosition(colRank, startY + (rank-1)*32);
        window.draw(textRank);

        sf::Text textName(entry.name, font, 22);
        textName.setFillColor(sf::Color::White);
        textName.setPosition(colName, startY + (rank-1)*32);
        window.draw(textName);

        sf::Text textScore(std::to_string(entry.score), font, 22);
        textScore.setFillColor(sf::Color::White);
        textScore.setPosition(colScore, startY + (rank-1)*32);
        window.draw(textScore);

        sf::Text textTime(std::to_string(entry.elapsed) + "s", font, 22);
        textTime.setFillColor(sf::Color::White);
        textTime.setPosition(colTime, startY + (rank-1)*32);
        window.draw(textTime);

        ++rank;
    }

    // button
    window.draw(backButtonSprite);
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(bgMenuSprite);
    window.draw(titleText);
    window.draw(startButtonSprite);
    window.draw(exitButtonSprite);
    window.draw(leadButtonSprite);
}

bool MainMenu::isStartClicked(sf::RenderWindow& window, sf::Event& event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if(startButtonSprite.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

bool MainMenu::isExitClicked(sf::RenderWindow& window, sf::Event& event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if(exitButtonSprite.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

bool MainMenu::isLeadClicked(sf::RenderWindow& window, sf::Event& event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if(leadButtonSprite.getGlobalBounds().contains(mousePos)) {
            //std::cout << "LEADERBOARD BUTTON CLICKED\n";
            return true;
        }
    }
    return false;
}

bool MainMenu::isBackClicked(sf::RenderWindow& window, sf::Event& event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if(backButtonSprite.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}