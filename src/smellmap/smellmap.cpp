#include "smellmap.h"


SmellMap::SmellMap()
    : m_window(nullptr)
{
}

std::vector<std::vector<float>> SmellMap::get_grid()
{
    return m_smell_grid;
}

void SmellMap::set_render_window(sf::RenderWindow* window, int height, int width)
{
    m_window = window;
    m_width = width;
    m_height = height;
    m_smell_grid = std::vector<std::vector<float>>(width, std::vector<float>(height, 0.0f));
}

void SmellMap::apply_diffusion()
{
    std::vector<std::vector<float>> tmp_smell_grid = m_smell_grid;

    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            float total_smell = m_smell_grid[i][j];
            float remaining = total_smell * (3.0f/8.0f);
            float diffusing = total_smell * (1.0f/8.0f);

            tmp_smell_grid[i][j] = remaining;

            if(i > 0) {
                tmp_smell_grid[i-1][j] += diffusing;
            }
            if(i < m_width - 1) {
                tmp_smell_grid[i+1][j] += diffusing;
            }
            if(j > 0) {
                tmp_smell_grid[i][j-1] += diffusing;
            }
            if(j < m_height - 1) {
                tmp_smell_grid[i][j+1] += diffusing;
            }
        }
    }

    m_smell_grid = tmp_smell_grid;
}

void SmellMap::draw()
{
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            float intensity = std::min(m_smell_grid[i][j], 1.0f);
            if(intensity > 0.00001)
            {
                sf::RectangleShape cell(sf::Vector2f({1, 1}));
                cell.setPosition(sf::Vector2f({float(i), float(j)}));
                cell.setFillColor(sf::Color(120 + 135 * intensity, 0, 110 + 129 * intensity));
                m_window->draw(cell);
            }
            else
            {
                m_smell_grid[i][j] = 0;
            }
        }
    }
}

void SmellMap::simulate(std::vector<Bug> bugs)
{
    apply_diffusion();
    
    for(Bug buggy : bugs)
    {
        if(!buggy.is_dying())
        {
            sf::Vector2f position = buggy.get_position();
            
            if(position.x >= 0 && position.y >= 0 && position.x < m_width && position.y < m_height)
            {
                m_smell_grid[position.x][position.y] = 1.0f;
            }
        }
    }

    draw();
}