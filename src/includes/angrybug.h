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
    
    int calculate_next_direction(
        int move, 
        std::vector<Bug>* bugs, 
        std::vector<std::vector<float>> smell);
};