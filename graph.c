#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void build_graph_cmd(pnode *head)
{
    deleteGraph_cmd(head);
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

pnode getNode(pnode *head, int id)
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
    pnode src = getNode(head, id);

    if (src == NULL)
    {
        src = (pnode)malloc(sizeof(node));
        src->node_num = id;
        src->next = *head;
        src->edges = NULL;
        *head = src;
    }
    else
    {
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
        pnode destNode = getNode(head, dest);
        if (destNode == NULL)
        {
            destNode = (pnode)malloc(sizeof(node));
            destNode->node_num = dest;
            destNode->edges = NULL;
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
void deleteGraph_cmd(pnode *head)
{
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
    *head = NULL;
}
void delete_node_cmd(pnode *head)
{
    int key = -1;
    scanf("%d", &key);
    pnode nodeIndex = *head;
    pnode ans = NULL;
    while (nodeIndex != NULL)
    {
        if (nodeIndex->node_num == key)
        {
            ans = nodeIndex;
        }
        else
        {
            pedge edgeIndex = nodeIndex->edges;
            while (edgeIndex != NULL)
            {
                if (edgeIndex->endpoint->node_num == key)
                {
                    if (edgeIndex->next != NULL)
                    {
                        pedge temp = edgeIndex->next;
                        edgeIndex->endpoint = temp->endpoint;
                        edgeIndex->weight = temp->weight;
                        edgeIndex->next = temp->next;
                        free(temp);
                    }
                    else
                    {
                        pedge temp = edgeIndex;
                        free(temp);
                        edgeIndex = NULL;
                    }
                }
                else {
                    edgeIndex = edgeIndex->next;
                }
            }
        }
        nodeIndex = nodeIndex->next;
    }
    if (ans != NULL)
    {
        pedge edgeIndex = ans->edges;
        while (edgeIndex != NULL)
        {
            pedge temp = edgeIndex->next;
            free(edgeIndex);
            edgeIndex = temp;
        }
        if (ans->next != NULL)
        {
            pnode temp = ans->next;
            ans->node_num = temp->node_num;
            ans->edges = temp->edges;
            ans->next = temp->next;
            free(temp);
        }
        else
        {
            free(ans);
        }
    }
}