#include "lists_functions.hpp"
#include "check_functions.hpp"

int dump_counter = 0;

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
    

    for (int index = list->free; index < list->capacity; index++) //заполнение свободных узлов
    {
        
        fprintf (graph_file, "    node%d [shape = Mrecord, style=filled, label = \"%d|", index, index);
        
        fprintf (graph_file, "%d", list->node[index].data);
        
        fprintf (graph_file,"|{%d|%d}\"]\n", list->node[index].prev, list->node[index].next);
    }    

    fprintf (graph_file, "\n    ");

    for (size_t index = 0; index < list->capacity - 1; index++) //невидимые стрелки для ровной линии
    {
        fprintf (graph_file, "node%d -> node%d [style = \"invis\", weight = 300]\n    ", index, index + 1);
    }
   
    fprintf(graph_file, "\n    ");

	fprintf(graph_file, "head [shape = doublecircle, style = filled, fillcolor= \"#CD5C5C\"]\n    "
    "head -> node%d [color = \"black\", weight = 1] {rank = same; node%d}\n    ", list->node[0].next, list->node[0].next); //#800000

    fprintf (graph_file, "\n    ");


    fprintf(graph_file, "edge [dir = forward, arrowhead = vee, color = \"#A52A2A\"]\n    "); 

    fprintf (graph_file, "\n    ");

    int next = 0;//list->node[0].next;

    color = 13458524;

    for (int index = 0; index <= list->size; index++)
    { 

        fprintf (graph_file, "node%d -> node%d\n    ", next, list->node[next].next);
        next = list->node[next].next;
    }
    fprintf(graph_file, "\n    ");

    next = list->node[0].next;

    for (int index = 0; index < list->size; index++)
    { 
        fprintf (graph_file, "    node%d [fillcolor= \"#%x\"]\n    ", next, color + 10*index);
        next = list->node[next].next;
    }

    fprintf(graph_file, "\n    ");

    fprintf(graph_file, "tail [shape = doublecircle, style = filled, fillcolor= \"#%x\"]\n    "
    "tail -> node%d [color = \"black\"] {rank = same; node%d}\n    ", color + 10*(list->size - 1), list->node[0].prev, list->node[0].prev); 

    fprintf (graph_file, "\n    ");

    fprintf(graph_file, "edge [dir = right, color = \"#F4A460\"]\n    ");

    fprintf(graph_file, "\n    ");

    next = list->free;

    color = 16757363;

    fprintf(graph_file, "free [shape = doublecircle, style = filled, fillcolor= \"#%x\"]\n    "
    "free -> node%d [color = \"black\", weight = 1] {rank = same; node%d}\n    ", color, list->free, list->free);

    fprintf(graph_file, "\n    ");
        

    for (int index = 0; index < list->capacity - list->size - 1; index++)
    {
        
        fprintf (graph_file, "node%d -> ", next);
        next = list->node[next].next;
    }

    fprintf(graph_file, "node%d    ", next);   

    fprintf(graph_file, "[style = dashed]\n    ");

    next = list->free;

    for (int index = 0; index < list->capacity - list->size - 1; index++)
    {
        fprintf(graph_file, "    node%d [fillcolor= \"#%x\"]\n    ", next, color + 4*index);
        next = list->node[next].next;
    }  
    
    next = list->free + list->capacity - list->size - 1;

    //fprintf(graph_file, "node%d -> node%d [color = black]\n}", next, list->node[next].next);


    fprintf(graph_file, "}");
    fclose(graph_file);

    //system("dot input.dot -Tpng -o output.png");


    char cmd_string[100] = "";

    sprintf (cmd_string, "dot input.dot -Tpng -o output%d.png", dump_counter);
    system (cmd_string);    

    dump_counter++;
}

void build_png_to_html(struct lists * list)
{
    FILE* file = fopen("output.html", "wb");

    fprintf (file, " <pre>\n\n");

    //fprintf (file, " HEAD = %d\n TAIL = %d\n FREE = %d\n SIZE = %d\n CAPACITY = %d\n\n", list->head, list->tail, list->free, list->size, list->capacity);
    
    for (int index = 0; index < dump_counter; index++)
    {
        fprintf (file, "<image src = \"output%d.png\" /image>\n", index);
    }

    fclose (file);
}
