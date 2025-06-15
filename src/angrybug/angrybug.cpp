#include "angrybug.h"


AngryBug::AngryBug() :
    Bug()
{
    setFillColor(sf::Color::Red);

    m_is_angry = true;
    m_hearing = 0.1f;
    m_vision = 1.0f - m_hearing;
    m_smell = 1.0f - (m_vision*0.5f);
    m_speed = 1.0f;
}

AngryBug::AngryBug(
    sf::Vector2f position, 
    std::vector<int> move_genome, 
    int speed) :
    Bug(position, move_genome, speed)
{
    setFillColor(sf::Color::Red);

    m_is_angry = true;
    m_hearing = speed;
    m_vision = 1.0f - m_hearing;
    m_smell = 1.0f - (m_vision*0.5f);
    m_speed = 1.0f;
}

int AngryBug::calculate_next_direction(
    int move, 
    std::vector<Bug>* bugs, 
    std::vector<std::vector<float>> smell)
{
    // for(Bug& bug : bugs)
    // {
    //     if(!bug.is_angry())
    //     {
    //         return 0;
    //     }
    // }
    return 0;
}
