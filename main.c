#include <stdio.h>
#include "graph.h"
int main()
{
    pnode temp = NULL;
    pnode *head = &temp;
    char input = '\0';
    while (scanf("%c", &input) != EOF)
    {
        printf("%c\n", input);
        if (input == 'A')
        {
            build_graph_cmd(head);
        }
        else if (input == 'D')
        {
           delete_node_cmd(head);
        }
        else if (input == 'S')
        {
           shortsPath_cmd(*head);
        }
        printf("\n");
        printGraph_cmd(*head);
        
    }
    return 0;
}