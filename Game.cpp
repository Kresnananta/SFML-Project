#include "Game.h"
#include "constant.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() : running(true), window(sf::VideoMode(800, 600), "Galaxium") {}

void Game::init() {
    window.setFramerateLimit(60);
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");

    // pesawat
    pesawat.setSize(sf::Vector2f(100.0f, 100.0f));
    pesawat.setPosition(400.0f, 300.0f);
    pesawatTexture.loadFromFile("../img/pesawat_baru.png");
    pesawat.setTexture(&pesawatTexture);
    // laser
    if (!laserTexture.loadFromFile("../img/laser.png")) {
        std::cout << "Gagal load laser.png\n";
    }
    // engine efek
    if (!engineIdleTexture.loadFromFile("../img/engine_idle.png")) {
        std::cout << "Gagal load engine_idle.png\n";
    }
    if (!engineBoostTexture.loadFromFile("../img/engine_boost.png")) {
        std::cout << "Gagal load engine_boost.png\n";
    }
    engineIdleSprite.setTexture(engineIdleTexture);
    engineBoostSprite.setTexture(engineBoostTexture);

    // UI
    gameUI.setLives(lives);
    gameUI.setScore(score);
    gameUI.setGameOver(false);
    leaderboard.load("leaderboard.txt");

    //background (seamless)
    bgTexture.loadFromFile("../img/greenNebula.png");
    bgTexture.setRepeated(true);
    bgRect.setSize(sf::Vector2f(2400.0f, 1800.0f));
    bgRect.setTexture(&bgTexture);
    
    // base asteroid
    asteroidTexture.loadFromFile("../img/Asteroid_Base.png");
    // explosive asteroid (96 x 8 = 768)
    if (!explosionTexture.loadFromFile("../img/Asteroid_Explode.png")) {
    std::cout << "Gagal load asteroid_explosion.png\n";
}

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

    if(!explodeSoundBuffer.loadFromFile("../audio/asteroid_explode.wav")){
        throw std::runtime_error("Failed to load explosion sound");
    }
    explodeSound.setBuffer(explodeSoundBuffer);
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
            elapsedClock.restart();
            elapsedTime = 0.0f;
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
        if (state == GameState::Menu && mainMenu.isLeadClicked(window, event)) {
            state = GameState::Leaderboard;
        }
        if (state == GameState::Leaderboard && mainMenu.isBackClicked(window, event)) {
            state = GameState::Menu;
        }
        //nampilin leaderboard di main menu
        mainMenu.processEvent(event);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        laserSound.play();
        if(shootClock.getElapsedTime().asSeconds() > shootCooldown){
            sf::Sprite laser;
            laser.setTexture(laserTexture);
            // Set posisi laser di ujung pesawat
            sf::Vector2f pos = pesawat.getPosition();
            sf::Vector2f size = pesawat.getSize();
            // Pusatkan laser di tengah pesawat (atur sesuai kebutuhan)
            laser.setPosition(pos.x + size.x/2 - laserTexture.getSize().x/2, pos.y - laserTexture.getSize().y);
            lasers.push_back(laser);
            shootClock.restart();
            // sf::RectangleShape laser(sf::Vector2f(8.f, 30.f));
            // laser.setFillColor(sf::Color::Blue);
            // // posisi laser
            // sf::Vector2f pos = pesawat.getPosition();
            // sf::Vector2f size = pesawat.getSize();
            // laser.setPosition(pos.x + size.x/2 - 2.f - 4.f, pos.y - 30.f); // set di ujung pesawat
            // lasers.push_back(laser);
            // shootClock.restart();
        }
    }
}

void Game::update() {
    if (gameOver) return;
    if (state == GameState::Splash) {
        splashScreen.update();
        if (splashScreen.isFinished()) {
            state = GameState::Menu;
        }
        return; // jgn update game saat di splash screen
    }
    if (state == GameState::Menu || state == GameState::Leaderboard) {
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

    elapsedTime = elapsedClock.getElapsedTime().asSeconds();
    gameUI.setElapsedTime(elapsedTime);

    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * dt;
    pesawat.move(movement);

    // Deteksi boosting
    bool boosting = sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    isBoosting = boosting;

    // Update animasi engine idle
    if (!isBoosting) {
        engineIdleTimer += dt;
        if (engineIdleTimer >= engineIdleFrameTime) {
            engineIdleTimer -= engineIdleFrameTime;
            engineIdleFrame = (engineIdleFrame + 1) % 3; // 3 frame
        }
        engineIdleSprite.setTextureRect(sf::IntRect(engineIdleFrame * 48, 0, 48, 48));
    } else {
        engineBoostTimer += dt;
        if (engineBoostTimer >= engineBoostFrameTime) {
            engineBoostTimer -= engineBoostFrameTime;
            engineBoostFrame = (engineBoostFrame + 1) % 4; // 4 frame
        }
        engineBoostSprite.setTextureRect(sf::IntRect(engineBoostFrame * 48, 0, 48, 48));
    }

    // Update posisi engine di bawah pesawat
    sf::Vector2f pesawatPos = pesawat.getPosition();
    sf::Vector2f pesawatSize = pesawat.getSize();
    float engineY = pesawatPos.y + pesawatSize.y/2 + 5; // offset ke bawah
    float engineX = pesawatPos.x + pesawatSize.x/2 - 24; // tengah pesawat - setengah frame engine (48/2)
    engineIdleSprite.setPosition(engineX, engineY);
    engineBoostSprite.setPosition(engineX, engineY);

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
    lasers.erase(std::remove_if(lasers.begin(), lasers.end(), [topY](const sf::Sprite& l){
        return l.getPosition().y + l.getTexture()->getSize().y < topY;
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
                a->destroy(&explosionTexture);
                //a = asteroids.erase(a); // hapus asteroid yang kena laser
                score += 10;
                gameUI.setScore(score);
                break;
            } else {
                ++a;
            }
        }
        if (hit) {
            explodeSound.play();
            l = lasers.erase(l); // hapus laser yang kena asteroid
        } else {
            ++l;
        }
    }
    asteroids.erase(
        std::remove_if(asteroids.begin(), asteroids.end(),
            [](const Asteroid& a) { return a.isDestroyed() && !a.isAnimating(); }),
        asteroids.end()
    );

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

                // cek high score?
                const auto& entries = leaderboard.getEntries();
                if (entries.size() < 10 || score > entries.back().score){
                    if (entries.size() < 10 || score > entries.back().score){
                        // Ambil tanggal dan waktu sekarang
                        char date[11], timeStr[9];
                        std::time_t t = std::time(nullptr);
                        std::tm* now = std::localtime(&t);
                        std::strftime(date, sizeof(date), "%Y-%m-%d", now);
                        std::strftime(timeStr, sizeof(timeStr), "%H:%M:%S", now);

                        LeaderboardEntry entry;
                        entry.name = "PLAYER"; //nama default
                        entry.score = score;
                        entry.date = date;
                        entry.time = timeStr;
                        entry.elapsed = static_cast<int>(elapsedTime);
                        leaderboard.addEntry(entry);
                        leaderboard.save("leaderboard.txt");
                    }
                }
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
    elapsedTime = 0.0f;
    gameUI.setLives(lives);
    gameUI.setScore(score);
    gameUI.setGameOver(false);
    elapsedClock.restart();
    asteroids.clear();
    lasers.clear();
    pesawat.setPosition(400.0f, 300.0f);
    camera.reset();
}

void Game::render() {
    window.clear();
    window.setView(window.getDefaultView());
    if (state == GameState::Splash) {
        splashScreen.draw(window);
        //return;
    }
    if (state == GameState::Menu) {
        mainMenu.draw(window);
        window.display();
        return;
    }
    if (state == GameState::Leaderboard){
        window.clear();
        mainMenu.drawLeaderboard(window, leaderboard.getEntries(), font);
        window.display();
        return;
    }
    if(state == GameState::Playing || state == GameState::GameOver) {
        window.clear();
        window.setView(camera.getView());
        window.draw(bgRect);
        if (isBoosting) {
            window.draw(engineBoostSprite);
        } else {
            window.draw(engineIdleSprite);
        }
        window.draw(pesawat);
        for(const auto& laser : lasers){
            window.draw(laser);
        }
        for (const auto& asteroid : asteroids) {
            asteroid.draw(window);
        }
        window.setView(window.getDefaultView());
        gameUI.draw(window);

        
    }

    window.display();
}

bool Game::isRunning() const {
    return running && window.isOpen();
}