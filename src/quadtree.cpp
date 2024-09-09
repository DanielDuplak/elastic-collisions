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

void insert_entity_to_list(struct EntityNode* first, struct Circle* entity_to_insert)
{
    if(entity_to_insert == NULL)
    {
        return;
    }
    struct EntityNode* new_entity = (struct EntityNode*)malloc(sizeof(struct EntityNode));
    new_entity->entity = entity_to_insert;
    new_entity->next = NULL;
    if(first == NULL)
    {
        first = new_entity;
        return;
    }
    else if(first->next == NULL)
    {
        first->next = new_entity;
        return; 
    }
    struct EntityNode* temp = first->next;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_entity;

}


void insert(struct QuadTreeNode* node, struct Circle* entity)
{
    if(node == NULL || entity == NULL)
    {
        return;
    }

    if(node->entity_count < MAX_ENTITY_COUNT || node->lvl == MAX_LVL)
    {

    }
}