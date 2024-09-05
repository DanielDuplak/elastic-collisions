#include <cmath>

struct Vector2D 
{
    float x;
    float y;
};

float dot_product(Vector2D v1, Vector2D v2);

Vector2D vector_sum(Vector2D v1, Vector2D v2);

Vector2D vector_sub(Vector2D v1, Vector2D v2);

Vector2D vector_scalar_product(Vector2D v1, float scalar);

Vector2D vector_scalar_div(Vector2D v1, float scalar);

float vector_get_magnitude(Vector2D v1);

Vector2D vector_set_magnitude(Vector2D v1, float scalar);
