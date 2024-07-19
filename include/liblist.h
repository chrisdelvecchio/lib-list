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

// Creates a new empty List
List *NewList(List *optional);

// Free memory allocated by List
void ListFreeMemory(List *list);

// Add an element to the List
void ListAdd(List *list, void *data);

// Set an element to the specified index and return the element
void *ListSet(List *list, unsigned int index, void *data);

// Remove the element from the List by index and return the element
void *ListRemoveIndex(List *list, unsigned int index);

// Remove the element from the List and return the element
void *ListRemove(List *list, void *data);

// Removes all of the elements from this list.
void ListClear(List *list);

// Returns true if the list contains the element passed, or else false.
bool ListContains(List *list, void *data);

/*
    -> #ListFilter()
    -> Returns a new list consisting of the elements of this provided list
   that match the provided predicate.
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
List *ListFilter(List *list, bool (*predicate)(void *));

/* Returns the first occurrence of the element in the list,
 based on the provided predicate, or NULL if not found. */
void *ListFind(List *list, bool (*predicate)(void *));

/* Sort the elements of the list according to the provided predicate */
void ListSort(List *list, int (*compare)(const void *, const void *));

/*
    -> #ListForEach()
    -> Applies a function to each element in the list
    -> Example usage:

    -> [with Lambda]
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

    -> [without Lambda]

    void handle(void *data) {
        printf(" - %d\n", *((int*) data));
    }

    ListForEach(evenNumbers, handle);
*/
void ListForEach(List *list, void (*function)(void *));

/* Shuffle the list's elements */
void ListShuffle(List *list);

/* Gets element at index or (THROWS EXCEPTION if index is out of bounds) and
 * return it. */
void *ListGet(List *list, unsigned int index);

/* Return the element at index or(THROWS EXCEPTION if data is NULL and will
 * return -1) */
int ListIndexOf(List *list, void *data);

// Removes last element from List and returns it.
void *ListPop(List *list);

// Gets first element from List and returns it.
void *ListFirst(List *list);

// Gets last element from List and returns it.
void *ListLast(List *list);

// Gets next element after passed (void *) data parameter and return it.
void *ListNext(List *list, void *data);

// Get previous element before passed (void *) data parameter and return it.
void *ListPrev(List *list, void *data);

// Returns the number of elements from the given List.
size_t ListSize(List *list);

// Returns true if the map is empty, false otherwise.
bool isListEmpty(List *list);

// Copy elements from source List to destination List
void ListCopy(List *source, List *dest);

#endif  //__LIB_HEADER__