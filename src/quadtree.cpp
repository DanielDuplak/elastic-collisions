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

int is_inside_boundary(struct QuadTreeNode* node, struct Circle* entity)
{
    float radius = entity->shape.getRadius();
    float cx0 = entity->position.x - radius;
    float cx1 = entity->position.x + radius;
    float cy0 = entity->position.y - radius;
    float cy1 = entity->position.y + radius;

    return( (cx0 >= node->x && cx0 <= (node->x+node->w)) || (cx1 >= node->x && cx1 <= (node->x+node->w)) ||
            (cy0 >= node->y && cy0 <= (node->y+node->h)) || (cy1 >= node->y && cy1 <= (node->y+node->h)) );
}


void insert(struct QuadTreeNode* node, struct Circle* entity)
{
    if(node == NULL || entity == NULL)
    {
        return;
    }

    if(node->entity_count < MAX_ENTITY_COUNT || node->lvl == MAX_LVL)
    {
        insert_entity_to_list(node->entities, entity);
    }
    else
    {
        if(node->children[0] == NULL)
        {
            node->children[0] = create_quad_tree_node(node->x, node->y, node->w/2, node->y/2, node->lvl+1);
            node->children[1] = create_quad_tree_node(node->x+node->w/2, node->y, node->w/2, node->y/2, node->lvl+1);
            node->children[2] = create_quad_tree_node(node->x, node->y+node->h/2, node->w/2, node->y/2, node->lvl+1);
            node->children[3] = create_quad_tree_node(node->x+node->w/2, node->y+node->h/2, node->w/2, node->y/2, node->lvl+1);

            
        }
    }
}