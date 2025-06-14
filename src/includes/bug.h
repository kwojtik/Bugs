#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>


class Bug : public sf::RectangleShape
{
    private:
    int m_energy;
    int m_age;
    int m_max_age;
    int m_adult_age;
    int m_energy_needed;
    int m_speed;
    int m_time_since_move;
    const std::vector<sf::Vector2f> m_moves = 
        {
            sf::Vector2f({0, 2}),
            sf::Vector2f({2, 1}),
            sf::Vector2f({2, -1}),
            sf::Vector2f({0, -2}),
            sf::Vector2f({-2, -1}),
            sf::Vector2f({-2, 1})
        };
    std::vector<int> m_move_genome;
    int m_move_sum;
    std::vector<float> m_move_probability;
    int m_direction;

    public:
    Bug();
    Bug(sf::Vector2f position, std::vector<int> move_genome, int speed);
    bool is_dying();
    bool can_reproduce();
    int reproduce();
    int calculate_next_direction(int move);
    sf::Vector2f calculate_position(int height, int width);
    void move(int move, int height, int width);
};