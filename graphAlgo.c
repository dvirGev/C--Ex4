#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define fullSize 1000000
typedef struct Dijkstra_Node
{
    pnode node;
    struct Dijkstra_Node *dad;
    int weight;
    int isUse;
    struct Dijkstra_Node *next;
} Dnode, *pDnode;

pDnode buildDijkstra_NodeList(pnode start, int src)
{
    pDnode head = NULL;
    pDnode *index = &head;
    while (start != NULL)
    {
        (*index) = (pDnode)malloc(sizeof(Dnode));
        (*index)->node = start;
        if (start->node_num == src)
        {
            (*index)->dad = (*index);
            (*index)->weight = 0;
        }
        else
        {
            (*index)->dad = NULL;
            (*index)->weight = fullSize;
        }
        (*index)->isUse = 0;
        (*index)->next = NULL;
        index = &((*index)->next);
        start = start->next;
    }
    return head;
}
void deleteList(pDnode list) {
    while (list != NULL)
    {
        pDnode temp = list;
        list = list->next;
        free(temp);
    }
}
pDnode getPDnode(pDnode list, int want)
{
    while (list != NULL)
    {
        if (list->node->node_num == want)
        {
            return list;
        }
        list = list->next;
    }
    return NULL;
}
pDnode minInList(pDnode head)
{
    pDnode ans = NULL;
    while (head != NULL)
    {
        if (!head->isUse && head->weight < fullSize && (ans == NULL || ans->weight < head->weight))
        {
            ans = head;
        }
        head = head->next;
    }
    if (ans != NULL)
    {
        ans->isUse = 1;
    }
    return ans;
}
void shortsPath_cmd(pnode head)
{
    int src = -1, dest = -1;
    scanf("%d %d", &src, &dest);
    pDnode list = buildDijkstra_NodeList(head, src);

    pDnode u = minInList(list);
    while (u != NULL)
    {
        pedge edgeIndex = u->node->edges;
        while (edgeIndex != NULL)
        {
            //relax
            pDnode v = getPDnode(list, edgeIndex->endpoint->node_num);
            int newDist = u->weight + edgeIndex->weight;
            if (v->weight > newDist)
            {
                v->weight = newDist;
                v->dad = u;
            }
            edgeIndex = edgeIndex->next;
        }
        u = minInList(list);
    }
    int dis = getPDnode(list, dest)->weight;
    dis = (dis == fullSize)? -1: dis;
    printf("Dijsktra shortest path: %d ", dis);
    deleteList(list);
}