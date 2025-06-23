#include "Camera.h"
#include <cmath>

Camera::Camera(float width, float height)
    : view(sf::FloatRect(0, 0, width, height)), threshold(60.f)
{
    defaultCenter = sf::Vector2f(width / 2.f, height / 2.f);
    view.setCenter(defaultCenter);
}

void Camera::update(const sf::Vector2f& target, bool enableFollow, float threshold) {
    if (!following && enableFollow) {
        if (std::abs(target.x - defaultCenter.x) > threshold ||
            std::abs(target.y - defaultCenter.y) > threshold) {
            following = true;
        }
    }
    if (following && enableFollow) {
        view.setCenter(target);
    }
}

void Camera::reset() {
    following = false;
    view.setCenter(defaultCenter);
}

sf::View& Camera::getView() {
    return view;
}