#include "bug.h"


Bug::Bug()
{
    setSize(sf::Vector2f(3, 3));
    setFillColor(sf::Color::Red);
    setPosition(sf::Vector2f({0.0, 0.0}));

    m_energy = 100;
    m_age = 0;

    m_max_age = 100;
    m_adult_age = 50;

    m_energy_needed = 30;

    m_speed = 1;
}

Bug::Bug(sf::Vector2f position, std::vector<int> move_genome, int speed)
{
    setSize(sf::Vector2f(3, 3));
    setFillColor(sf::Color::Red);
    setPosition(position);

    m_energy = 100;
    m_age = 0;

    m_max_age = 100;
    m_adult_age = 50;

    m_energy_needed = 30;

    m_speed = speed;

    m_move_genome = move_genome;

    for(auto mg : m_move_genome)
    {
        float move_probability = pow(2, mg);
        m_move_sum += move_probability;
        m_move_probability.push_back(move_probability);
    }

    m_time_since_move=0;
    m_speed=1;
    m_direction = 0;
}

bool Bug::is_dying()
{
    if(m_energy < 0 || m_age > m_max_age)
    {
        return true;
    }

    return false;
}

bool Bug::can_reproduce()
{
    return m_age > m_adult_age && m_energy > m_energy_needed;
}

int Bug::reproduce()
{

    m_energy /= 2;

    return m_energy;
}

int Bug::calculate_next_direction(int move)
{
    int direction = 0;
    
    for(int i = 0; i < 6; i++)
    {
        move -= m_move_probability[i];
        if(move < 0)
        {
            direction = i;
            break;
        }
    }

    return direction;
}

sf::Vector2f Bug::calculate_position(int height, int width)
{
    sf::Vector2f position = getPosition() + m_moves[m_direction];

    if(position.x > width)
    {
        position.x = width-3;
    }
    if(position.y > height)
    {
        position.y = height-3;
    }    
    if(position.x < 0)
    {
        position.x = 3;
    }
    if(position.y < 0)
    {
        position.y = 3;
    }

    return position;
}

void Bug::move(int move, int height, int width)
{
    int reproduction = 0;

    if(can_reproduce())
    {
        reproduction = reproduce();
    }

    if(m_time_since_move%m_speed == 0)
    {
        m_energy--;

        m_direction = (m_direction + calculate_next_direction(move)) % 6;

        setPosition(calculate_position(height, width));

        m_time_since_move = 0;
    }

    m_time_since_move++;
    m_age++;

    return;
}
