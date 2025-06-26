#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "bug.h"


class AngryBug : public Bug
{
    float m_hearing;
    float m_vision;
    float m_smell;

    public:
    AngryBug();
    AngryBug(
        sf::Vector2f position, 
        std::vector<int> move_genome, 
        int speed);
    bool is_within_bounds(sf::Vector2f position, 
        int width, 
        int height);
    int check_smell(std::vector<std::vector<float>> smell);
    int check_vision(Bug bug);
    int check_sound(Bug bug);
    int attack(
        Bug bug,
        std::vector<std::vector<float>> smell);
    int reproduce(std::vector<Bug>* bugs);
    int calculate_next_direction(
        int move, 
        std::vector<Bug>* bugs, 
        std::vector<std::vector<float>> smell);
    void eat(std::vector<Food>* food);
};