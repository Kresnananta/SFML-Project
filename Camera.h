#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(float width, float height);

    void update(const sf::Vector2f& target, bool enableFollow, float threshold = 60.0f);
    void reset();
    sf::View& getView();
private:
    sf::View view;
    bool following = false;
    float threshold;
    sf::Vector2f defaultCenter;
};

#endif