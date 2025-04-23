#include "game.h"


Game::Game()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    m_window_width = 1000;
    m_window_height = 2000;

    m_window.create(sf::VideoMode({m_window_width, m_window_height}, desktop.bitsPerPixel), "Bugs", sf::Style::None);
    m_window.setFramerateLimit(60);
}

void Game::run(int bugs_amount)
{
    return;
}

void Game::render()
{
    return;
}
