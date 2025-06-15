#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "bug.h"
#include "smellmap.h"

class Game
{
    private:
    sf::RenderWindow m_window;
    unsigned int m_window_width;
    unsigned int m_window_height;
    std::vector<Bug> m_bugs;
    SmellMap m_smellmap;

    public:
    Game();
    sf::Vector2f random_within_bounds();
    std::vector<int> generate_move_genome();
    void run(int bugs_amount);
    void render();
};