#include <stdio.h>
#include "graph.h"
int main()
{
    char input = '\0';
    scanf("%c", &input);
    pnode temp = NULL;
    pnode *head = &temp;
    build_graph_cmd(head);
    printGraph_cmd(*head);
    printf("\n");
    deleteGraph_cmd(head);
    printGraph_cmd(*head);
    return 0;
}