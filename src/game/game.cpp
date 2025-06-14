#include "game.h"


Game::Game()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    m_window_width = 1500;
    m_window_height = 1000;

    m_window.create(sf::VideoMode({m_window_width, m_window_height}, desktop.bitsPerPixel), "Bugs", sf::Style::None);
    m_window.setFramerateLimit(60);
}

sf::Vector2f Game::random_within_bounds()
{
    sf::Vector2f random({float(rand()%m_window_width), float(rand()%m_window_height)});

    return random;
}

std::vector<int> Game::generate_move_genome()
{
    std::vector<int> move_genome;

    for(int i = 0; i < 6; i++)
    {
        int is_negative = rand()%2 ? 1 : -1;
        move_genome.push_back(rand()%5*is_negative);
    }

    return move_genome;
}

void Game::run(int bugs_amount)
{
    for(int i=0; i < bugs_amount; i++)
    {
        Bug bug(random_within_bounds(), generate_move_genome(), rand()%10);

        m_bugs.push_back(bug);
    }

    while(m_window.isOpen())
    {

        while(const std::optional event = m_window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                m_window.close();
                break;
            }

            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if(keyPressed->scancode == sf::Keyboard::Scancode::Right)
                {
                    render();
                }
            }
        }
    }
}

void Game::render()
{
    m_window.clear();
    
    for(Bug& bug : m_bugs)
    {
        bug.move(rand()%100, m_window_height, m_window_width);
        m_window.draw(bug);
    }

    m_window.display();
}
