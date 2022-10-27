#include "lists_functions.hpp"

void list_ctor(struct lists * list)
{
    assert(list != NULL);
    
    list->head = 0;
    list->tail = 0;
    list->free = 1;
    list->size = 0;
    list->is_sort = 1;
    list->capacity = MAX_LIST_SIZE;

    list->node = (struct list_elem * ) calloc(list->capacity, 3 * (sizeof(elem_t) + 1));
    //list->list_elem->data = (elem_t *) calloc(list->capacity, sizeof(elem_t));

    list_completion(list);
/*
    list->node[0].data = 0;
    list->node[0].next = 0;
    list->node[0].prev = 0;

    
    list->head = 0;
    list->tail = 0; 
    list->free = 1; 
    list->size = 0;  

    for(int i = list->free; i < list->capacity; i++)
    {
    list->node[i].data = 0;
    list->node[i].next = i + 1; 
    list->node[i].prev = -1;  
    }  

    list->node[list->capacity].data = 0;
    list->node[list->capacity].next = 0; 
    list->node[list->capacity].prev = -1;
*/     
}

void list_completion(struct lists * list)
{
    list->node[0].data = 0;
    list->node[0].next = 0;
    list->node[0].prev = 0;

    list->node[1].data = 555;
    list->node[1].next = 0; 
    list->node[1].prev = 5;

    list->node[2].data = 222;
    list->node[2].next = 4; 
    list->node[2].prev = 3;

    list->node[3].data = 111;
    list->node[3].next = 2; 
    list->node[3].prev = 0;

    list->node[4].data = 333;
    list->node[4].next = 5; 
    list->node[4].prev = 2;

    list->node[5].data = 444;
    list->node[5].next = 1; 
    list->node[5].prev = 4;
    
    for(int i = 6; i < list->capacity; i++)
    {
    list->node[i].data = 0;
    list->node[i].next = i + 1; 
    list->node[i].prev = -1;  
    }  

    list->node[list->capacity].data = 0;
    list->node[list->capacity].next = 0; 
    list->node[list->capacity].prev = -1;         

    list->head = 3;
    list->tail = 1; 
    list->free = 6; 
    list->size = 5;   
}

int push_front(struct lists * list, int value)
{
    assert(list != NULL);

    int next_free = list->node[list->free].next;

    list->node[list->free].data = value; //кладем значение в следующую пустую ячейку
    list->node[list->free].next = list->head; //ставим следующий элемент
    list->node[list->free].prev = 0;

    
    if (list->head != 0) //поменять указатель у бывшего первого элемента
    {
        list->node[list->head].prev = list->free;
    }

    list->head = list->free; //меняем указатель на первый элемент
    
    if (list->size == 0) //если не было ни одного элемента
    {
        list->tail = list->free;
        list->tail = list->free;
    }

    list->free = next_free; //передвигаем указатель free
    
    (list->size)++;

    return list->head;
}

int pop_front(struct lists * list, int * value)
{
    //assert(list->head != 0); //?
    assert(list != NULL);
    assert(list->size != 0); //в списке есть элементы

    *value = list->node[list->tail].data;

    int new_free = list->head; 
    int new_next_for_free = list->free;

    int next_head = list->node[list->head].next;
    
    list->node[list->head].data = -1;
    list->node[list->head].next = -1;
    list->node[list->head].prev = -1;

    list->head = next_head; //сдвигаем указатель на голову

    if (list->head != 0) //меняем указатель для нового первого элемента
    {
        list->node[list->head].prev  = 0;
    }

    if (list->head == list->tail) //если в списке всего один элемент
    {
        list->tail = 0;
        list->head = 0;
        list->size = 0;
    }  

    list->free = new_free; 
    list->node[new_free].next  = new_next_for_free; 

    (list->size)--;
}


int push_back(struct lists * list, int value)
{
    assert(list != NULL);

    int next_free = list->node[list->free].next;

    list->node[list->free].data = value;
    list->node[list->free].next = 0; 
    list->node[list->free].prev = list->tail;

    if (list->tail != 0) 
    {
        list->node[list->tail].prev = list->free;
    }

    list->tail = list->free;

    if (list->size == 0)
    {
        list->head = list->free;
        list->head = list->free;
    }

    list->free = next_free;

    (list->size)++;

    return list->tail;
}

int pop_back(struct lists * list, int * value)
{
    assert(list != NULL);
    assert(list->size != 0);

    *value = list->node[list->tail].data; 

    int new_free = list->tail; 
    int new_next_for_free = list->free;

    int next_tail = list->node[list->tail].prev;

    list->node[list->tail].data = -1;
    list->node[list->tail].next = -1;
    list->node[list->tail].prev = -1;

    list->tail = next_tail;

    if (list->tail != 0)
    {
        list->node[list->tail].next  = 0;
    }

    if (list->head == list->tail) 
    {
        list->tail = 0;
        list->head = 0;
        list->size = 0;
    }    

    list->free = new_free;
    list->node[new_free].next  = new_next_for_free;

    (list->size)--;    
}

int get_nth(struct lists * list, int index) //вычисление физического номера по логическому
{
    assert(list != NULL);
    assert(list->size != 0);
    
    int tmp = list->head;
    int i = 1;
 
    while (i < index) 
    {
        //printf("%d, val = %d\n", tmp, list->node[tmp].data);
        tmp = list->node[tmp].next;
        i++;
    }
 
    return tmp;    
}

int insert(struct lists * list, int index, int value)
{
    assert(list != NULL);

    int next_free = list->node[list->free].next;

    int elm = get_nth(list, index);

    //printf("elm = %d\n", elm);

    list->node[list->free].data = value;
    list->node[list->free].next = elm; 
    list->node[list->free].prev = list->node[elm].prev; 

    if(elm == 1 || (list->size == 0))
    {
        push_front(list, value); 
    }

    list->node[(list->node[elm].prev)].next = list->free; //переписываем указатели

    list->node[elm].prev = list->free;

    list->free = next_free;

    (list->size)++; 

    list->is_sort = 0;   
 
    return list->node[elm].prev;
}   

int delete_nth(struct lists * list, int index, int * value)
{
    assert(list != NULL);
    assert(list->size != 0);

    int elm = get_nth(list, index);

    *value = list->node[elm].data;

    if(elm == 1 || (list->size == 0))
    {
        pop_front(list, value); 
    }

    int new_free = elm; 
    int new_next_for_free = list->free;

    list->node[(list->node[elm].prev)].next = list->node[elm].next; //меняем указатели

    list->node[(list->node[elm].next)].prev = list->node[elm].prev;

    list->node[elm].data = -1;
    list->node[elm].next = new_next_for_free; 
    list->node[elm].prev = -1;  

    list->free = new_free;  

    list->is_sort = 0;  

    (list->size)--;
}

int sort(struct lists * list)
{
    assert(list != NULL);

    struct list_elem * new_data = (struct list_elem * ) calloc(list->capacity, 3 * (sizeof(elem_t) + 1));

    int elm = list->head;

    for(int i = 1; i <= list->size; i++)
    {
        (new_data + i)->data = list->node[elm].data;
        (new_data + i)->next = list->node[elm].next;
        (new_data + i)->prev = list->node[elm].prev;
        elm = list->node[elm].next;
    }

    elm = list->free;

    for(int i = list->size + 1; i <= list->capacity; i++) 
    {
        (new_data + i)->data = list->node[elm].data;
        (new_data + i)->next = list->node[elm].next;
        (new_data + i)->prev = list->node[elm].prev;
        elm = list->node[elm].next;
    }    

    list->head = 1;
    list->tail = list->size;

    struct list_elem * old_data = list->node;

    list->node = new_data;

    list->is_sort = 1;   

    free(old_data);
}

void list_dump(struct lists * list)
{
    printf("\nN:    ");
    for(int it = 0; it <= list->capacity; it++) 
    {
        printf("%3d ", it);
    }    
    
    printf("\nDATA: ");
    for(int it = 0; it <= list->capacity; it++) 
    {
        printf("%3d ", list->node[it].data);
    }

    printf("\nNEXT: ");
    for(int it = 0; it <= list->capacity; it++) 
    {
        printf("%3d ", list->node[it].next);
    }

    printf("\nPREV: ");
    for(int it = 0; it <= list->capacity; it++) 
    {
        printf("%3d ", list->node[it].prev);
    }  
    printf("\n");   

    printf("HEAD = %d  TAIL = %d FREE = %d SIZE = %d\n", list->head, list->tail, list->free, list->size);   
}

void list_dtor(struct lists * list)
{
    list->head = -1;
    list->tail = -2;
    list->free = -50;
    list->size = -1;
    list->capacity = -MAX_LIST_SIZE;
    free(list->node);
}