#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include "Asteroid.h"
#include "GameUI.h"
#include "SplashScreen.h"
#include "Menu_State.h"
#include "Camera.h"

enum class GameState {
    Splash,
    Menu,
    Playing,
    GameOver
};


class Game {
public:
    Game();
    void init();
    void processInput();
    void update();
    void render();
    bool isRunning() const;
    void restartGame();

private:
    bool running;
    sf::RenderWindow window;
    sf::RectangleShape pesawat;
    sf::Texture pesawatTexture;

    sf::Texture bgTexture;
    sf::RectangleShape bgRect;
    sf::Vector2f bgOffset{0.0f, 0.0f}; // Offset untuk parallax effect
    //float parallaxFactor = 0.5f; // 20% dari kecepatan pesawat

    SplashScreen splashScreen;
    MainMenu mainMenu;
    sf::Music menuMusic;
    sf::SoundBuffer buttonSound;
    sf::Sound buttonClick;
    GameUI gameUI;
    GameState state = GameState::Splash; 

    Camera camera{800.0f, 600.0f};
    bool cameraFollow = false;

    int lives = 3; // nyawa pesawat
    int score = 0;
    bool gameOver = false;

    sf::Clock deltaClock;
    //float speed = 300.0f; //pixel per second

    std::vector<sf::RectangleShape> lasers;
    //float laserSpeed = 500.0f;
    sf::Clock shootClock;
    //float shootCooldown = 0.2f;
    sf::SoundBuffer laserSoundBuffer;
    sf::Sound laserSound;

    sf::Texture asteroidTexture;
    std::vector<Asteroid> asteroids;
    sf::Clock asteroidClock;
    //float asteroidSpawnCooldown = 1.0f; // seconds
    //float asteroidSpeed = 150.0f;
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> asteroiddistX{0.0f, 700.0f}; // Assuming window width is 800
};

#endif // GAME_H