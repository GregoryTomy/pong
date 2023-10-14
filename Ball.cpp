#include "Ball.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"

Ball::Ball(float startX, float startY)
{
    m_Position.x = startX;
    m_Position.y = startY;

    m_Shape.setSize(Vector2f(10, 10));
    m_Shape.setPosition(m_Position);
}

FloatRect Ball::getPosition() { return m_Shape.getGlobalBounds(); }

RectangleShape Ball::getShape() { return m_Shape; }

float Ball::getXVelocity() { return m_DirectionX; }

// reverse the direction X
void Ball::reboundSides() { m_DirectionX = -m_DirectionX; }

void Ball::reboundBatorTop() { m_DirectionY = -m_DirectionY; }

// reset if player mnissed the ball
void Ball::reboundBottom()
{
    m_Position.y = 100;
    m_Position.x = 500;
    // m_DirectionY = -m_DirectionY;
}

void Ball::update(Time dt)
{
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();

    m_Shape.setPosition(m_Position);
}
