#include "vector_functions.hpp"


float dot_product(Vector2D v1, Vector2D v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y));
}

Vector2D vector_sum(Vector2D v1, Vector2D v2)
{
    Vector2D result = {v1.x + v2.x, v1.y + v2.y};
    return result;
}

Vector2D vector_sub(Vector2D v1, Vector2D v2)
{
    Vector2D result = {v1.x - v2.x, v1.y - v2.y};
    return result;
}

Vector2D vector_scalar_product(Vector2D v1, float scalar)
{
    Vector2D result = {v1.x * scalar, v1.y * scalar};
    return result;
}

Vector2D vector_scalar_div(Vector2D v1, float scalar)
{
    Vector2D result = {v1.x / scalar, v1.y / scalar};
    return result;
}

float vector_get_magnitude(Vector2D v1)
{
    return std::sqrt(v1.x * v1.x + v1.y * v1.y);
}

Vector2D vector_set_magnitude(Vector2D v1, float scalar)
{
    float magnitude = vector_get_magnitude(v1);

    if (magnitude == 0) return {0, 0};
    
    Vector2D result = {v1.x * scalar / magnitude, v1.y * scalar / magnitude};
    return result;
}