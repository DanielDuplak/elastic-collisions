#include "circle_logic.hpp"


#define MAX_LVL 3
#define MAX_ENTITY_COUNT 4
#define CHILD_COUNT 4


struct EntityNode
{
    struct Circle* entity;
    struct EntityNode* next;
};


struct QuadTreeNode
{
    int x,y;
    int w,h;
    int lvl;
    int entity_count;
    struct EntityNode* entities;
    struct QuadTreeNode* children[CHILD_COUNT];
};




struct QuadTreeNode* create_quad_tree_node(int x, int y, int w, int h, int lvl);

void free_quadtreenode(struct QuadTreeNode* root);