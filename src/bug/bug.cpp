#include "bug.h"


Bug::Bug()
{
    setSize(sf::Vector2f(3, 3));
    setFillColor(sf::Color::Red);
    setPosition(sf::Vector2f({0.0, 0.0}));

    m_energy = 200;
    m_age = 0;

    m_max_age = 500;
    m_adult_age = 50;

    m_energy_needed = 30;

    m_speed = 1;

    m_is_angry = false;
    m_is_dead = false;
    m_moves = 
            {
                sf::Vector2f({0, 2}),
                sf::Vector2f({2, 1}),
                sf::Vector2f({2, -1}),
                sf::Vector2f({0, -2}),
                sf::Vector2f({-2, -1}),
                sf::Vector2f({-2, 1})
            };
}

Bug::Bug(sf::Vector2f position, std::vector<int> move_genome, int speed)
{
    setSize(sf::Vector2f(3, 3));
    setFillColor(sf::Color::Green);
    setPosition(position);

    m_energy = 200;
    m_age = 0;

    m_max_age = 500;
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
    m_speed = 1;
    m_direction = 0;

    m_is_angry = false;
    m_is_dead = false;

    m_moves = 
        {
            sf::Vector2f({0, 2}),
            sf::Vector2f({2, 1}),
            sf::Vector2f({2, -1}),
            sf::Vector2f({0, -2}),
            sf::Vector2f({-2, -1}),
            sf::Vector2f({-2, 1})
        };
}

sf::Vector2f Bug::get_position()
{
    return getPosition();
}

int Bug::get_energy()
{
    return m_energy;
}

float Bug::distance_between_bugs(sf::Vector2f bug_position)
{
    return sqrt((get_position().x-bug_position.x)*(get_position().x-bug_position.x)+
    (get_position().y-bug_position.y)*(get_position().y-bug_position.y));
}

bool Bug::is_angry()
{
    return m_is_angry;
}

bool Bug::is_dying()
{
    if(m_energy < 0 || m_age > m_max_age || m_is_dead)
    {
        die();
        return true;
    }
    
    return false;
}

float Bug::emiting_sound()
{
    return m_emited_sound;
}

void Bug::die()
{
    m_energy = 0;
    m_is_dead = true;
}

bool Bug::can_reproduce()
{
    return m_age > m_adult_age && m_energy > m_energy_needed;
}

int Bug::reproduce(std::vector<Bug>* bugs)
{
    Bug new_bug(get_position(), m_move_genome, m_speed);

    bugs->push_back(new_bug);

    m_energy /= 2;

    return 1;
}

int Bug::calculate_next_direction(
    int move, 
    std::vector<Bug>* bugs, 
    std::vector<std::vector<float>> smell)
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

void Bug::eat(std::vector<Food>* food)
{
    for(auto it = food->begin(); it != food->end();)
    {
        if(distance_between_bugs(it->get_position()) < 2)
        {
            m_energy = it->eat();
            it = food->erase(it);
        }
        else
        {
            it++;
        }
    }
}

void Bug::move(
    int move, 
    int height, 
    int width, 
    std::vector<Bug>* bugs, 
    std::vector<std::vector<float>> smell,
    std::vector<Food>* food)
{
    int reproduction = 0;

    if(can_reproduce())
    {
        reproduction = reproduce(bugs);
    }

    if(m_time_since_move%m_speed == 0)
    {
        m_energy--;

        m_direction = (m_direction + calculate_next_direction(move, bugs, smell)) % 6;

        setPosition(calculate_position(height, width));

        m_time_since_move = 0;

        m_emited_sound = m_speed;
    }
    else
    {
        m_emited_sound = 0;
    }

    eat(food);

    m_time_since_move++;
    m_age++;

    return;
}
