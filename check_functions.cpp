#include "lists_functions.hpp"
#include "check_functions.hpp"

void graph_list_dump(struct lists * list)
{
    FILE * graph_file = fopen("input.dot", "w");

    fprintf (graph_file, "digraph LIST{\n    splines=ortho\n    rankdir=LR\n    node [color = \"#800000\"]\n    ");

    int color = 0;

    for (int index = 0; index < list->free; index++) //заполнение занятых узлов
    {

        fprintf (graph_file, "    node%d [shape = Mrecord, style=filled, label = \"%d|", index, index);
        
        fprintf (graph_file, "%d", list->node[index].data);
        
        fprintf (graph_file,"|{%d|%d}\"]\n", list->node[index].prev, list->node[index].next);
    }

    fprintf (graph_file, "    node0 [fillcolor= \"#B0C4DE\"]\n    ");
    

    for (int index = list->free; index <= list->capacity; index++) //заполнение свободных узлов
    {
        
        fprintf (graph_file, "    node%d [shape = Mrecord, style=filled, label = \"%d|", index, index);
        
        fprintf (graph_file, "%d", list->node[index].data);
        
        fprintf (graph_file,"|{%d|%d}\"]\n", list->node[index].prev, list->node[index].next);
    }    

    fprintf (graph_file, "\n    ");

    for (size_t index = 0; index <= list->capacity - 1; index++) //невидимые стрелки для ровной линии
    {
        fprintf (graph_file, "node%d -> node%d [style = \"invis\", weight = 300]\n    ", index, index + 1);
    }
   
    fprintf(graph_file, "\n    ");

	fprintf(graph_file, "head [shape = doublecircle, style = filled, fillcolor= \"#CD5C5C\"]\n    "
    "head -> node%d [color = \"#800000\", weight = 1] {rank = same; node%d}\n    ", list->head, list->head);

    fprintf (graph_file, "\n    ");


    fprintf(graph_file, "edge [dir = forward, arrowhead = vee, color = \"#A52A2A\"]\n    "); 

    fprintf (graph_file, "\n    ");

    int next = list->head;

    color = 13458524;

    for (int index = 0; index < list->size - 1; index++)
    { 

        fprintf (graph_file, "node%d -> node%d\n    ", next, list->node[next].next);
        next = list->node[next].next;
    }
    fprintf (graph_file, "\n    ");

    next = list->head;

    for (int index = 0; index < list->size; index++)
    { 
        fprintf (graph_file, "    node%d [fillcolor= \"#%x\"]\n    ", next, color + 10*index);
        next = list->node[next].next;
    }

    fprintf (graph_file, "\n    ");

    fprintf(graph_file, "tail [shape = doublecircle, style = filled, fillcolor= \"#%x\"]\n    "
    "tail -> node%d [color = \"#800000\"] {rank = same; node%d}\n    ", color + 10*(list->size - 1), list->tail, list->tail); 

    fprintf (graph_file, "\n    ");

    fprintf(graph_file, "edge [dir = right, color = \"#F4A460\"]\n    ");

    fprintf (graph_file, "\n    ");

    next = list->free;

    color = 16757363;

    fprintf(graph_file, "free [shape = doublecircle, style = filled, fillcolor= \"#%x\"]\n    "
    "free -> node%d [color = \"#800000\", weight = 1] {rank = same; node%d}\n    ", color, list->free, list->free);

    fprintf (graph_file, "\n    ");
        

    for (int index = 0; index < list->capacity - list->size - 1; index++)
    {
        
        fprintf (graph_file, "node%d -> ", next);
        next = list->node[next].next;
    }

    fprintf(graph_file, "node%d\n    ", next);   

    next = list->free;

    for (int index = 0; index < list->capacity - list->size; index++)
    {
        fprintf (graph_file, "    node%d [fillcolor= \"#%x\"]\n    ", next, color + 4*index);
        next = list->node[next].next;
    }  
    
    next = list->free + list->capacity - list->size - 1;

    fprintf(graph_file, "node%d -> node%d [color = black]\n}", next, list->node[next].next);


    fprintf(graph_file, "}");
    fclose(graph_file);

    system("dot input.dot -Tpng -o output.png");
   
}

