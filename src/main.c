#include <stdio.h>

#include "liblist.h"

// -> Create a new Empty list                              = NewList(NULL);
// -> Create a new list from a copy                        = NewList(List
// *source);

// -> Add an element to the list                           = ListAdd(List *list,
// void *data);

// -> Remove an element from the list                      = ListRemove(List
// *list, void *data);

// -> Remove last element from the list                    = ListPop(List
// *list);

// -> Print the list                                       = ListPrint(List
// *list);

// -> Get first element in the list                        = ListFirst(List
// *list);

// -> Get last element in the list                         = ListLast(List
// *list);

// -> Get next element in the list                         = ListNext(List
// *list, void *data);

// -> Get previous element in the list                     = ListPrev(List
// *list, void *data);

// -> Free entire list Memory                              = ListFree(List
// *list);

// -> Copy list to another list                            = ListCopy(List
// *source, List *dest);

int main(void) {
  List *list = NewList(NULL);

  int num = 69, num2 = 420;
  ListAdd(list, &num);
  ListAdd(list, &num2);

  printf("From 0 index: %d\n", *((int *)list->data[0]));

  printf("List Fetch Get Test (0 index): %d\n", *((int *)ListGet(list, -1)));
  printf("\nSize of our list = %d\n", list->size);

  printf("First element in the list = %d\n", *((int *)ListFirst(list)));
  printf("Last element in the list = %d\n", *((int *)ListLast(list)));

  ListPop(list);
  printf("Size of our list after POP = %d\n", list->size);
  printf("Last element after POP = %d\n", *((int *)ListLast(list)));

  List *newList = NewList(list);

  printf("\n --- NEW LIST ---\nSize of our new list = %d\n", newList->size);
  printf("Last element in the COPIED list = %d\n", *((int *)ListLast(newList)));

  ListFreeMemory(list);
  return 0;
}