#ifndef LISTS_FUNCTIONS_H_INCLUDED
#define LISTS_FUNCTIONS_H_INCLUDED

#include "utilities.hpp"

void list_ctor(struct lists * list);

void list_completion(struct lists * list);

void list_dump(struct lists * list);

int push_front(struct lists * list, int value);

int pop_front(struct lists * list, int * value);

int push_back(struct lists * list, int value);

int pop_back(struct lists * list, int * value);

int get_nth(struct lists * list, int index);

int insert(struct lists * list, int index, int value);

int delete_nth(struct lists * list, int index, int * value);

int sort(struct lists * list);

void list_dtor(struct lists * list);

#endif // LISTS_FUNCTIONS_H_INCLUDED