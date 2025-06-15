#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "bug.h"

class SmellMap
{
    private:
    sf::RenderWindow* m_window;
    std::vector<std::vector<float>> m_smell_grid;
    int m_width;
    int m_height;

    public:
    SmellMap();
    std::vector<std::vector<float>> get_grid();
    void set_render_window(
        sf::RenderWindow* window, 
        int height, 
        int width);
    void apply_diffusion();
    void draw();
    void simulate(std::vector<Bug> bugs);
};