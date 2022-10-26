#include "lists_functions.hpp"
 
int main(void) 
{
    struct lists list = {-1, -1, -1, -1};
    
    list_ctor(&list);

    //for(int it = 0; it < list.capacity; it++) 
    //{
    //    printf("%2d -> %3d %3d %3d \n", it, list.list_elem[it].data, list.list_elem[it].next, list.list_elem[it].prev);
    //}

    list_dump(&list);

    //push_front(&list, 666);
    //list_dump(&list);
    //push_front(&list, 777);
    //list_dump(&list);    

    //push_back(&list, 666);
    //list_dump(&list);
    //push_back(&list, 777);
    //list_dump(&list); 

    int a = 0;

    //pop_back(&list, &a);
    //printf("val = %d\n", a);   
    //list_dump(&list);
    //pop_back(&list, &a);
    //printf("val = %d\n", a);
    //list_dump(&list);
    
    //pop_front(&list, &a);
    //printf("val = %d\n", a);   
    //list_dump(&list);
    //pop_front(&list, &a);
    //printf("val = %d\n", a);
    //list_dump(&list);

    //printf("val = %d\n", get_nth(&list, 3));

    //printf("val = %d\n", insert(&list, 3, 666));

    //list_dump(&list);

    //delete_nth(&list, 3, &a);

    //printf("a = %d\n", a);

    //list_dump(&list);

    sort(&list);

    list_dump(&list);

    list_dtor(&list);

    return 0;
}