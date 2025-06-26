#pragma once

#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>


class Food : public sf::RectangleShape
{
    private:
    int m_satiety;

    public:
    Food();
    Food(sf::Vector2f position);
    sf::Vector2f get_position();
    int eat();
};
