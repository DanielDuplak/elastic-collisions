#include <SFML/Graphics.hpp>
#include "vector_functions.hpp"


#define OBJECT_COUNT 10

struct Circle
{
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    float mass;
    sf::CircleShape shape;
};



void create_circle(Circle* circle);

void update_circle_edge_collision(Circle* circle, float delta_time, const sf::RenderWindow& window);

void handle_circle_collision(Circle* circle1, Circle* circle2);

