#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void build_graph_cmd(pnode *head)
{
    deleteGraph_cmd(head);
    *head = NULL;
    int size = 0;
    scanf("%d", &size);
    char n = 'B';
    scanf("%c", &n);
    for (int i = 0; i < size; ++i)
    {
        scanf("%c", &n);
        insert_node_cmd(head);
    }
}

pnode findNode(pnode *head, int id)
{
    pnode index = *head;
    while (index != NULL)
    {
        if (index->node_num == id)
        {
            return index;
        }
        index = index->next;
    }
    return NULL;
}

void insert_node_cmd(pnode *head)
{
    int id = -1;
    scanf("%d", &id);
    pnode src = findNode(head, id);
    
    if (src == NULL) {
        src = (pnode)malloc(sizeof(node));
        src->node_num = id;
        src->next = *head;
        src->edges = NULL;
        *head = src;
    }
    else {
        pedge index = src->edges;
        while (index != NULL)
        {
            pedge temp = index->next;
            free(index);
            index = temp;
        }
        src->edges = NULL;
    }
    pedge *lastEdge = &(src->edges);
    int dest = -1;
    while (scanf("%d", &dest) != 0)
    {
        pnode destNode = findNode(head, dest);
        if (destNode == NULL)
        {
            destNode = (pnode)malloc(sizeof(node));
            destNode->node_num = dest;
            destNode->edges =NULL;
            destNode->next = *head;
            *head = destNode;
        }
        int weight = -1;
        scanf("%d", &weight);

        *lastEdge = (pedge)malloc(sizeof(edge));
        (*lastEdge)->endpoint = destNode;
        (*lastEdge)->weight = weight;
        (*lastEdge)->next = NULL;
        lastEdge = &((*lastEdge)->next);
    }
}
void printGraph_cmd(pnode head)
{
    pnode nodeIndex = head;
    while (nodeIndex != NULL)
    {
        printf("Node %d: ", nodeIndex->node_num);
        pedge edgeIndex = nodeIndex->edges;
        while (edgeIndex != NULL)
        {
            printf("dest %d: weight %d, ", edgeIndex->endpoint->node_num, edgeIndex->weight);
            edgeIndex = edgeIndex->next;
        }
        printf("\n");
        nodeIndex = nodeIndex->next;
    }
}
void deleteGraph_cmd(pnode* head) {
    pnode nodeIndex = *head;
    while (nodeIndex != NULL)
    {
        pedge edgeIndex = nodeIndex->edges;
        while (edgeIndex != NULL)
        {
            pedge temp = edgeIndex;
            edgeIndex = edgeIndex->next;
            free(temp);
        }
        pnode temp = nodeIndex;
        nodeIndex = nodeIndex->next;
        free(temp);
    }
}