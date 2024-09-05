#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>  
#include "vector_functions.hpp"
#include <cmath>


#define OBJECT_COUNT 10

struct Circle
{
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    float mass;
    sf::CircleShape shape;
};


void create_circle(Circle* circle)
{
    float radius = std::sqrt(circle->mass) * 10.0f;

    circle->shape.setRadius(radius);
    circle->shape.setFillColor(sf::Color::White);
    circle->shape.setOutlineThickness(5.0f);
    circle->shape.setOutlineColor(sf::Color::Black);

    circle->shape.setPosition(circle->position.x - radius, circle->position.y - radius);
}

void update_circle_edge_collision(Circle* circle, float delta_time, const sf::RenderWindow& window)
{
    
    circle->velocity.x += circle->acceleration.x * delta_time;
    circle->velocity.y += circle->acceleration.y * delta_time;

    circle->position.x += circle->velocity.x * delta_time;
    circle->position.y += circle->velocity.y * delta_time;

    float radius = circle->shape.getRadius();

    if (circle->position.x - radius <= 0.0f)
    {
        circle->position.x = radius;
        circle->velocity.x *= -1;
    }
    else if(circle->position.x + radius >= window.getSize().x)
    {
        circle->position.x = window.getSize().x - radius;
        circle->velocity.x *= -1;
    }

    if (circle->position.y - radius <= 0.0f)
    {
        circle->position.y = radius;
        circle->velocity.y *= -1;
    }
    else if(circle->position.y + radius >= window.getSize().y)
    {
        circle->position.y = window.getSize().y - radius;
        circle->velocity.y *= -1;
    }

    circle->shape.setPosition(circle->position.x - radius, circle->position.y - radius);
    
}

void handle_circle_collision(Circle* circle1, Circle* circle2)
{
    float distance = vector_get_magnitude(vector_sub(circle1->position, circle2->position));

    if(distance > (circle1->shape.getRadius() + circle2->shape.getRadius()))
    {
        return;
    }

    Vector2D line_of_impact_vector = vector_sub(circle2->position, circle1->position);
    Vector2D velocity_difference_vector = vector_sub(circle2->velocity, circle1->velocity);

    float distance_squared = distance * distance;

    float velocity_impact_dot = dot_product(velocity_difference_vector, line_of_impact_vector);
    float mass_ratio = (2 * circle2->mass) / (circle1->mass + circle2->mass);

    Vector2D new_velocity1 = vector_sum(
        circle1->velocity,
        vector_scalar_product(
            line_of_impact_vector,
            mass_ratio * velocity_impact_dot / distance_squared
        ));

    line_of_impact_vector = vector_sub(circle1->position, circle2->position);
    velocity_difference_vector = vector_sub(circle1->velocity, circle2->velocity);

    velocity_impact_dot = dot_product(velocity_difference_vector, line_of_impact_vector);
    mass_ratio = (2 * circle1->mass) / (circle1->mass + circle2->mass);

    Vector2D new_velocity2 = vector_sum(
        circle2->velocity,
        vector_scalar_product(
            line_of_impact_vector,
            mass_ratio * velocity_impact_dot / distance_squared
        ));

    float overlap = distance - (circle1->shape.getRadius() + circle2->shape.getRadius());
    Vector2D direction = vector_set_magnitude(line_of_impact_vector, overlap * 0.5f);
    circle1->position = vector_sub(circle1->position, direction);
    circle2->position = vector_sum(circle2->position, direction);

    circle1->velocity = new_velocity1;
    circle2->velocity = new_velocity2;
}


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
        circles[i].mass = static_cast<float>(std::rand() % (100 - 20 + 1) + 20);

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
