#ifndef __LIB_HEADER__
#define __LIB_HEADER__

#include <stdio.h>

#define INIT_CAP 10

typedef struct List {
    void *data[INIT_CAP];
    size_t size;
    size_t capacity;
} List;

List *NewList(List *optional);
void ListFreeMemory(List *list);
void ListAdd(List *list, void *data);
void ListRemove(List *list, void *data);
void ListPop(List *list);
void *ListFirst(List *list);
void *ListLast(List *list);
void *ListNext(List *list, void *data);
void *ListPrev(List *list, void *data);
void ListCopy(List *source, List *dest);

#endif //__LIB_HEADER__