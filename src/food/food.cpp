#include "food.h"


Food::Food()
{
    setSize(sf::Vector2f(2, 2));
    setFillColor(sf::Color::Yellow);
    setPosition(sf::Vector2f(1, 1));
}

Food::Food(sf::Vector2f position)
{
    setSize(sf::Vector2f(2, 2));
    setFillColor(sf::Color::Yellow);
    setPosition(position);

    m_satiety = 50 + (rand()%500);
}

sf::Vector2f Food::get_position()
{
    return getPosition();
}

int Food::eat()
{
    std::cout << "eaten!\n";
    return m_satiety;
}
