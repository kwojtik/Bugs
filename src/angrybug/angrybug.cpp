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
    m_vision *= 30;
    m_speed = 1.0f;
}

bool AngryBug::is_within_bounds(sf::Vector2f position, 
    int width, 
    int height)
{
    return (position.x >= 0
        && position.x < width
        && position.y >= 0
        && position.y < height);
}

int AngryBug::check_smell(std::vector<std::vector<float>> smell)
{
    sf::Vector2f left_cell = getPosition() + m_moves[(((m_direction-1)%6) + 6 )%6];
    sf::Vector2f front_cell = getPosition() + m_moves[m_direction%6];
    sf::Vector2f right_cell = getPosition() + m_moves[(m_direction+1)%6];

    int width = smell.size();
    int height = smell[0].size();

    int smell_intensity = 0;
    int direction = m_direction;

    if(is_within_bounds(left_cell, width, height))
    {
        if(smell[left_cell.x][left_cell.y] > m_smell)
        {
            direction = (((m_direction-1)%6) + 6 )%6;
            smell_intensity = smell[left_cell.x][left_cell.y];
        }
    }
    if(is_within_bounds(front_cell, width, height))
    {
        if(smell[front_cell.x][front_cell.y] > m_smell && smell[front_cell.x][front_cell.y] > smell_intensity)
        {
            direction = m_direction%6;
            smell_intensity = smell[front_cell.x][front_cell.y];
        }
    }
    if(is_within_bounds(right_cell, width, height))
    {
        if(smell[right_cell.x][right_cell.y] > m_smell && smell[right_cell.x][right_cell.y] > smell_intensity)
        {
            direction = (m_direction+1)%6;
            smell_intensity = smell[right_cell.x][right_cell.y];
        }
    }

    return direction;
}

int AngryBug::check_vision(Bug bug)
{
    sf::Vector2f pos = bug.get_position();
    float dist = distance_between_bugs(pos);

    if(dist > m_vision)
    {
        return m_direction;
    }

    sf::Vector2f direction = (m_moves[m_direction]).normalized();
    sf::Vector2f pos_vector = (get_position() - pos).normalized();

    float dot = direction.x * pos_vector.x + direction.y * pos_vector.y;
    float cross = direction.x * pos_vector.y - direction.y * pos_vector.x;
    float angle = std::acos(dot) * 180 / 3.1415;

    if(angle <= 30)
    {
        if (std::abs(angle) < 5.f) {
            return m_direction;
        } else if (cross > 0) {
            return (((m_direction-1)%6) + 6 )%6;
        } else if (cross < 0) {
            return (m_direction+1)%6;
        }
    }
    
    return m_direction;
}

int AngryBug::check_sound(Bug bug)
{
    float sound = bug.emiting_sound();
    
    if(sound > 0)
    {
        float distance = distance_between_bugs(bug.get_position());

        float loudness = sound*(20/(distance*distance));

        if(loudness > m_hearing)
        {
            sf::Vector2f pos = bug.get_position();

            sf::Vector2f direction = (m_moves[m_direction]).normalized();
            sf::Vector2f pos_vector = (get_position() - pos).normalized();

            float dot = direction.x * pos_vector.x + direction.y * pos_vector.y;
            float cross = direction.x * pos_vector.y - direction.y * pos_vector.x;
            float angle = std::acos(dot) * 180 / 3.1415;

            if (std::abs(angle) < 5.f) {
                return m_direction;
            } else if (cross > 0) {
                return (((m_direction-1)%6) + 6 )%6;
            } else if (cross < 0) {
                return (m_direction+1)%6;
            }
        }
    }

    return m_direction;
}

int AngryBug::attack(
    Bug bug,
    std::vector<std::vector<float>> smell)
{
    if(!bug.is_angry() && !bug.is_dying())
    {
        if(distance_between_bugs(bug.get_position()) < 7)
        {
            m_energy += bug.get_energy();
            return -2;
        }
        else
        {
            int smell_result = check_smell(smell);
            int vision_result = check_vision(bug);
            int sound_result = check_sound(bug);

            int avr = (((smell_result + vision_result + sound_result) / 3)+6)%6;

            return smell_result;
        }
    }

    return 0;
}

int AngryBug::reproduce(std::vector<Bug>* bugs)
{
    return 0;
}

int AngryBug::calculate_next_direction(
    int move, 
    std::vector<Bug>* bugs, 
    std::vector<std::vector<float>> smell)
{
    for(auto it = bugs->begin(); it != bugs->end();)
    {
        int result = attack(*it, smell);

        if(result == -2)
        {
            it->die();
            it = bugs->erase(it);
            return m_direction;
        }
        else if(result == m_direction)
        {
            it++;
        }
        else
        {
            m_direction = 0;
            return result;
        }
    }

    m_direction = (((m_direction-m_move_genome[m_direction])%6) + 6 )%6;
    return m_direction;
}
