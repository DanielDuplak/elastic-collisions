#include "quadtree.hpp"




struct QuadTreeNode* create_quad_tree_node(int x, int y, int w, int h, int lvl)
{
    struct QuadTreeNode* node = (struct QuadTreeNode*)malloc(sizeof(struct QuadTreeNode));
    if(node == NULL) return NULL;

    node->x = x;
    node->y = y;
    node->w = w;
    node->h = h;
    node->entities = NULL;

    for(int i = 0; i < CHILD_COUNT; i++)
    {
        node->children[i] = NULL;
    }

    return node;
}


void free_entities(struct EntityNode* first)
{
    if(first == NULL) return;

    while (first)
    {
        EntityNode* next = first->next;
        free(first);
        first = next;
    }
}

void free_quadtreenode(struct QuadTreeNode* root)
{
    if(root == NULL) return;

    for(int i = 0; i < CHILD_COUNT; i++)
    {
        if(root->children[i])
        {
            free_quadtreenode(root->children[i]);
        }
    }
    free_entities(root->entities);
    free(root);
}