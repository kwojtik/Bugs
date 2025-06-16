#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>


class Bug : public sf::RectangleShape
{
    protected:
    int m_energy;
    int m_age;
    int m_max_age;
    int m_adult_age;
    int m_energy_needed;
    int m_speed;
    int m_time_since_move;
    std::vector<sf::Vector2f> m_moves;
    std::vector<int> m_move_genome;
    int m_move_sum;
    std::vector<float> m_move_probability;
    int m_direction;
    bool m_is_angry;
    float m_emited_sound;
    bool m_is_dead;

    public:
    Bug();
    Bug(
        sf::Vector2f position, 
        std::vector<int> move_genome, 
        int speed);
    sf::Vector2f get_position();
    int get_energy();
    float distance_between_bugs(sf::Vector2f bug_position);
    bool is_angry();
    bool is_dying();
    float emiting_sound();
    void die();
    bool can_reproduce();
    virtual int reproduce(std::vector<Bug>* bugs);
    virtual int calculate_next_direction(
        int move, 
        std::vector<Bug>* bugs, 
        std::vector<std::vector<float>> smell);
    sf::Vector2f calculate_position(int height, int width);
    void move(
        int move, 
        int height, 
        int width, 
        std::vector<Bug>* bugs, 
        std::vector<std::vector<float>> smell);
};