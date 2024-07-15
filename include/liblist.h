#ifndef __LIB_HEADER__
#define __LIB_HEADER__

#include <stdio.h>
#include <stdbool.h>

typedef struct List {
    void **data;
    size_t size;
    size_t capacity;
} List;

/*
 TODO:
   Just ideas here..
   Maybe we should make another List structure with function pointers instead?
*/

List *NewList(List *optional); // Creates a new empty List
void ListFreeMemory(List *list); // Free memory allocated by List
void ListAdd(List *list, void *data); // Add an element to the List
void *ListSet(List *list, unsigned int index, void *data); // Set an element to the specified index and return the element
void *ListRemoveIndex(List *list, unsigned int index); // Remove the element from the List by index and return the element
void *ListRemove(List *list, void *data); // Remove the element from the List and return the element
void ListClear(List *list); // Removes all of the elements from this list.
bool ListContains(List *list, void *data); // Returns true if the list contains the element passed, or else false.

/*
    -> #ListFilter() 
    -> Example usage:

    bool IsEven(void *data) {
        int value = *((int *)data);
        return (value % 2 == 0);
    }

    List *evenNumbers = ListFilter(list, IsEven);

    printf("Even numbers in the 'evenNumbers' #List:\n");
    for (int i = 0; i < evenNumbers->size; i++) {
        printf(" - %d\n", *((int *)ListGet(evenNumbers, i)));
    }
*/
List *ListFilter(List *list, bool (*predicate)(void *)); // Returns a new list consisting of the elements of this provided list that match the provided predicate.

/*
    -> #ListForEach()
    -> Example usage:

    -> with Lambda
    #define lambda(lambda$_ret, lambda$_args, lambda$_body)\
        ({\
            lambda$_ret lambda$__anon$ lambda$_args\
            lambda$_body\
            &lambda$__anon$;\
        })

    printf("\nForEach evennumber\n");
    ListForEach(evenNumbers, lambda(void, (void *data), {
        int i = *((int*) data);
        printf(" * %d\n", i);
    }));

    -> without Lambda

    void handle(void *data) {
        printf(" - %d\n", *((int*) data));
    }

    ListForEach(evenNumbers, handle);
*/
void ListForEach(List *list, void (*function)(void *)); // Applies a function to each element in the list.
void ListShuffle(List *list); // Shuffle the list's elements

void *ListGet(List *list, unsigned int index); // Gets element at index or (THROWS EXCEPTION if index is out of bounds) and return it.
int ListIndexOf(List *list, void *data);  // Return the element at index or(THROWS EXCEPTION if data is NULL and will return -1)
void *ListPop(List *list); // Removes last element from List and returns it.
void *ListFirst(List *list); // Gets first element from List and returns it.
void *ListLast(List *list); // Gets last element from List and returns it.
void *ListNext(List *list, void *data); // Gets next element after passed (void *)data parameter and return it.
void *ListPrev(List *list, void *data); // Get previous element before passed (void *)data parameter and return it.
size_t ListSize(List *list); // Returns the number of elements from the given List.
bool isListEmpty(List *list); // Returns true if the map is empty, false otherwise.
void ListCopy(List *source, List *dest); // Copy elements from source List to destination List

#endif //__LIB_HEADER__