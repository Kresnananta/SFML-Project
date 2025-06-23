#include "Game.h"
#include "constant.h"
#include <SFML/Graphics.hpp>

Game::Game() : running(true), window(sf::VideoMode(800, 600), "Galaxium") {}

void Game::init() {
    window.setFramerateLimit(60);
    pesawat.setSize(sf::Vector2f(100.0f, 100.0f));
    pesawat.setPosition(400.0f, 300.0f);
    pesawatTexture.loadFromFile("../img/pesawat1.png");
    pesawat.setTexture(&pesawatTexture);

    gameUI.setLives(lives);
    gameUI.setScore(score);
    gameUI.setGameOver(false);

    bgTexture.loadFromFile("../img/background_star.jpg");
    bgTexture.setRepeated(true);
    bgRect.setSize(sf::Vector2f(2400.0f, 1800.0f));
    bgRect.setTexture(&bgTexture);
    
    asteroidTexture.loadFromFile("../img/asteroid.png");

    if(!menuMusic.openFromFile("../audio/menuBGM.ogg")){
        throw std::runtime_error("Failed to load menu music");
    }
    menuMusic.setLoop(true);
    if(!buttonSound.loadFromFile("../audio/btn_click2.wav")){
        throw std::runtime_error("Failed to load button sound");
    }
    buttonClick.setBuffer(buttonSound);
    buttonClick.setVolume(50.0f);

    if(!laserSoundBuffer.loadFromFile("../audio/laser_shot.wav")){
        throw std::runtime_error("Failed to load laser sound");
    }
    laserSound.setBuffer(laserSoundBuffer);
    laserSound.setVolume(50.0f);
}

void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
            running = false;
        }
        if (state == GameState::Menu && mainMenu.isStartClicked(window, event)) {
            buttonClick.play();
            state = GameState::Playing;
        }
        if (gameOver && gameUI.isTryAgainClicked(window, event)) {
            buttonClick.play();
            restartGame();
        }
        if (gameOver && gameUI.isReturnMenuClicked(window, event)) {
            buttonClick.play();
            state = GameState::Menu;
            gameOver = false;
            lives = 3;
            score = 0;
            gameUI.setLives(lives);
            gameUI.setScore(score);
            gameUI.setGameOver(false);
            asteroids.clear();
            lasers.clear();
            pesawat.setPosition(400.0f, 300.0f);
            camera.reset();
        }
        if (state == GameState::Menu && mainMenu.isExitClicked(window, event)) {
            running = false;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        laserSound.play();
        if(shootClock.getElapsedTime().asSeconds() > shootCooldown){
            sf::RectangleShape laser(sf::Vector2f(8.f, 30.f));
            laser.setFillColor(sf::Color::Blue);
            // posisi laser
            sf::Vector2f pos = pesawat.getPosition();
            sf::Vector2f size = pesawat.getSize();
            laser.setPosition(pos.x + size.x/2 - 2.f - 4.f, pos.y - 30.f); // set di ujung pesawat
            lasers.push_back(laser);
            shootClock.restart();
        }
    }
}

void Game::update() {
    if (gameOver) return;
    if (state == GameState::Splash) {
        if (splashScreen.isTimeUp()) {
            state = GameState::Menu;
        }
        return; // jgn update game saat di splash screen
    }
    if (state == GameState::Menu) {
        if(menuMusic.getStatus() != sf::Music::Playing) {menuMusic.play();}
        return;
    } else {
        if(menuMusic.getStatus() == sf::Music::Playing) {menuMusic.stop();}
    }
    if(state == GameState::GameOver) {
        return;
    }

    // Main Logic (state = GameState::Playing)
    float dt = deltaClock.restart().asSeconds();

    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * dt;
    pesawat.move(movement);

    // Paralax effect
    bgOffset += movement * parallaxFactor;
    sf::Vector2f textOffset(
        std::fmod(bgOffset.x, bgTexture.getSize().x),
        std::fmod(bgOffset.y, bgTexture.getSize().y)
    );
    if(textOffset.x < 0) textOffset.x += bgTexture.getSize().x;
    if(textOffset.y < 0) textOffset.y += bgTexture.getSize().y;
     sf::Vector2f camTopLeft = camera.getView().getCenter() - camera.getView().getSize() / 2.0f;
    bgRect.setPosition(camTopLeft);
    bgRect.setTextureRect(sf::IntRect(
        static_cast<int>(textOffset.x),
        static_cast<int>(textOffset.y),
        static_cast<int>(bgRect.getSize().x),
        static_cast<int>(bgRect.getSize().y)
    ));
    // follow setelah pesawat bergerak lebih dari threshold
    camera.update(pesawat.getPosition(), true, 60.0f);

    // update posisis laser
    for (auto& laser : lasers) {
        laser.move(0.f, -laserSpeed * dt);
    }

    // dapetin posisi atas layar
    window.setView(camera.getView());
    sf::View view = window.getView();
    float topY = view.getCenter().y - view.getSize().y / 2.0f;


    // ngehapus laser yang keluar dari layar
    lasers.erase(std::remove_if(lasers.begin(), lasers.end(), [topY](const sf::RectangleShape& l){
        return l.getPosition().y + l.getSize().y < topY;
    }), lasers.end());

    // spawn asteroid
    if (asteroidClock.getElapsedTime().asSeconds() > asteroidSpawnCooldown) {
        float x = asteroiddistX(rng);
        asteroids.emplace_back(x, topY -64.0f, asteroidSpeed, &asteroidTexture);
        asteroidClock.restart();
    }
    // update asteroid
    for (auto& asteroid : asteroids) {
        asteroid.update(dt);
    }
    // hapus asteroid yang keluar dari layar
    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](const Asteroid& a){
        return a.isOffScreen(600.0f); }), asteroids.end()
    );

    // cek colision antara laser dan asteroid
    for (auto l = lasers.begin(); l != lasers.end(); ) {
        bool hit = false;
        for (auto a = asteroids.begin(); a != asteroids.end();) {
            if (l->getGlobalBounds().intersects(a->getBounds())) {
                hit = true;
                a = asteroids.erase(a); // hapus asteroid yang kena laser
                score += 10;
                gameUI.setScore(score);
                break;
            } else {
                ++a;
            }
        }
        if (hit) {
            l = lasers.erase(l); // hapus laser yang kena asteroid
        } else {
            ++l;
        }
    }

    // cek colision antara pesawat dan asteroid
    for (auto a = asteroids.begin(); a != asteroids.end(); ){
        if (pesawat.getGlobalBounds().intersects(a->getBounds())){
            a = asteroids.erase(a);
            lives--;
            gameUI.setLives(lives);
            if (lives <= 0){
                gameOver = true;
                // running = false;
                gameUI.setGameOver(true);
            }
        }
        else {
            ++a;
        }
    }
}

void Game::restartGame() {
    lives = 3;
    score = 0;
    gameOver = false;
    gameUI.setLives(lives);
    gameUI.setScore(score);
    gameUI.setGameOver(false);
    asteroids.clear();
    lasers.clear();
    pesawat.setPosition(400.0f, 300.0f);
    camera.reset();
}

void Game::render() {
    if (state == GameState::Splash) {
        splashScreen.draw(window);
        return;
    }
    if (state == GameState::Menu) {
        mainMenu.draw(window);
        return;
    }
    if(state == GameState::Playing || state == GameState::GameOver) {
        window.clear();
        window.setView(camera.getView());
        window.draw(bgRect);
        window.draw(pesawat);
        for(const auto& laser : lasers){
            window.draw(laser);
        }
        for (const auto& asteroid : asteroids) {
            asteroid.draw(window);
        }
        window.setView(window.getDefaultView());
        gameUI.draw(window);

        window.display();
    }
    // if(state == GameState::GameOver) {
    //     window.clear();
    //     window.draw(pesawat);
    //     for(const auto& laser : lasers){
    //         window.draw(laser);
    //     }
    //     for (const auto& asteroid : asteroids) {
    //         asteroid.draw(window);
    //     }
    //     gameUI.draw(window);
    //     window.display();
    // }
        
}

bool Game::isRunning() const {
    return running && window.isOpen();
}