#include "Camera.hpp"
#include <algorithm>

Camera::Camera(sf::Vector2f viewSize, sf::Vector2f mapSize)
    : m_mapSize(mapSize)
{
    m_view.setSize(viewSize);
    m_view.setCenter(clampCenter(mapSize / 2.f));
}

void Camera::follow(sf::Vector2f targetPosition)
{
    m_view.setCenter(clampCenter(targetPosition));
}

const sf::View& Camera::getView() const
{
    return m_view;
}

sf::Vector2f Camera::clampCenter(sf::Vector2f center) const
{
    const sf::Vector2f halfView = m_view.getSize() / 2.f;

    const float minX = halfView.x;
    const float minY = halfView.y;
    const float maxX = m_mapSize.x - halfView.x;
    const float maxY = m_mapSize.y - halfView.y;

    center.x = std::clamp(center.x, minX, maxX);
    center.y = std::clamp(center.y, minY, maxY);

    return center;
}
