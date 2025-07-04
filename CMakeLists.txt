project(sfml-project)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(src)

set(SOURCES
    main.cpp
    Game.cpp
    Asteroid.cpp
    GameUI.cpp
    SplashScreen.cpp
    Menu_State.cpp
    Camera.cpp
    Leaderboard.cpp
)

add_executable(sfml-project ${SOURCES})

target_link_libraries(sfml-project sfml-graphics sfml-window sfml-system sfml-audio)