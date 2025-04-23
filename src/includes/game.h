#pragma once

#include <SFML/Graphics.hpp>

class Game
{
    private:
    sf::RenderWindow m_window;
    unsigned int m_window_width;
    unsigned int m_window_height;

    public:
    Game();
    void run(int bugs_amount);
    void render();
};