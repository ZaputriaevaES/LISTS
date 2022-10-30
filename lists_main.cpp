#include "lists_functions.hpp"
#include "check_functions.hpp"
 
int main(void) 
{
    struct lists list = {-1, -1, -1, -1};
    
    list_ctor(&list);

    list_dump(&list);

    insert(&list, 0, 111);
    insert(&list, 0, 222);
    insert(&list, 0, 333);
    insert(&list, 0, 444);

    list_dump(&list);

    sort(&list);

    list_dump(&list);

    insert(&list, 2, 666);

    list_dump(&list);
    
    insert(&list, 2, 777);
    list_dump(&list);

    graph_list_dump(&list);

    build_png_to_html(&list);

    list_dtor(&list);

    return 0;
}