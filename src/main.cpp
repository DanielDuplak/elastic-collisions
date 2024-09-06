#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>  
#include "circle_logic.hpp"




int main() 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Elastic Collisions");

    //window.setFramerateLimit(60);

    Circle circles[OBJECT_COUNT];

    for (int i = 0; i < OBJECT_COUNT; ++i) 
    {
        circles[i].position = 
        { 
            static_cast<float>(std::rand() % (window.getSize().x - 401) + 200), 
            static_cast<float>(std::rand() % (window.getSize().y - 401) + 200) 
        };
        circles[i].velocity = { static_cast<float>(std::rand() % 700 - 351), static_cast<float>(std::rand() % 700 - 351) };
        //circles[i].velocity = { 0.0f, 0.0f };
        circles[i].acceleration = { 0.0f, 0.0f };
        circles[i].mass = static_cast<float>(std::rand() % 100 + 20);

        create_circle(&circles[i]);
    }

    //SKOPIROVANE
    sf::Font font;
    if (!font.loadFromFile("ARIAL.TTF"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::Yellow);
    fpsText.setPosition(10.f, 10.f);
    //SKOPIROVANE

    sf::Clock clock;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float delta_time = clock.restart().asSeconds();

        /*
        float kinetic_energy = 0;
        for(int i = 0; i < OBJECT_COUNT; i++)
        {
            kinetic_energy += (0.5f * circles[i].mass * std::pow(vector_get_magnitude(circles[i].velocity), 2));
        }
        printf("kinetic energy: %f\n", kinetic_energy);
        */
        

        float fps = 1.f / delta_time;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

        window.clear(sf::Color(100, 100, 100, 255));

        for (int i = 0; i < OBJECT_COUNT; ++i) 
        {
            update_circle_edge_collision(&circles[i], delta_time, window);
            for(int j = i+1; j < OBJECT_COUNT; j++)
            {
                handle_circle_collision(&circles[i], &circles[j]);
            }
            window.draw(circles[i].shape);
        }
        window.draw(fpsText);

        window.display();
    }

    return 0;
}
