#include "liblist.h"

#include <stdlib.h>

List *NewList(List *optional) {
  List *list = malloc(sizeof(List));

  if (list == NULL) {
    fprintf(stderr, "Failed creating new list, ERROR ALLOCATING MEMORY\n");
    exit(EXIT_FAILURE);
  }

  list->data = malloc(10 * sizeof(void *));

  if (list->data == NULL) {
    fprintf(stderr,
            "Failed to allocate memory for List's data field. ERROR ALLOCATING "
            "MEMORY\n");
    free(list);
    exit(EXIT_FAILURE);
  }

  list->size = 0;
  list->capacity = 10;

  if (optional != NULL) {
    ListCopy(optional, list);
  }
  return list;
}

void ListFreeMemory(List *list) {
  free(list->data);
  free(list);
}

void ListAdd(List *list, void *data) {
  if (list->size >= list->capacity) {
    list->capacity *= 2;
    list->data = realloc(list->data, list->capacity * sizeof(void *));

    if (list->data == NULL) {
      fprintf(
          stderr,
          "Failed to allocate memory for List's data field. ERROR ALLOCATING "
          "MEMORY\n");
      ListFreeMemory(list);
      exit(EXIT_FAILURE);
    }
  }

  list->data[list->size] = data;
  list->size += 1;
}

void *ListSet(List *list, unsigned int index, void *data) {
  if (index >= list->size) {
    fprintf(stderr, "Failed to set data at index '%i'. Index out of bounds\n",
            index);
    exit(EXIT_FAILURE);
    return NULL;
  }

  void *old_data = list->data[index];
  list->data[index] = data;
  return old_data;
}

static inline void HandleElementRemove(List *list, size_t index) {
  list->data[index] = list->data[list->size - 1];
  list->data[list->size - 1] = NULL;
  list->size -= 1;
}

void *ListRemoveIndex(List *list, unsigned int index) {
  if (isListEmpty(list)) {
    fprintf(stderr, "LIST REMOVE BY INDEX EXCEPTION: Failed to remove by index '%i' from list. List is empty\n",
            index);
    exit(EXIT_FAILURE);
    return NULL;
  }

  for (size_t i = 0; i < list->size; i++) {
    void *data = ListGet(list, index);
    HandleElementRemove(list, index);

    if (data != NULL) {
      return data;
    }
  }
}

void *ListRemove(List *list, void *data) {
  for (size_t i = 0; i < list->size; i++) {
    if (list->data[i] == data) {
      HandleElementRemove(list, i);
      return data;
    }
  }

  fprintf(stderr, "LIST REMOVE EXCEPTION: Failed to remove data from list. Data not found\n");
  exit(EXIT_FAILURE);
}

void ListClear(List *list) {
  if (isListEmpty(list)) {
    fprintf(stderr, "LIST CLEAR EXCEPTION: Failed to clear list. List is already empty\n");
    exit(EXIT_FAILURE);
    return;
  }

  for (size_t i = 0; i < list->size; i++) {
    list->data[i] = NULL;
  }

  list->size = 0;
}

bool ListContains(List *list, void *data) {
  if (isListEmpty(list)) {
    printf("LIST QUERY EXCEPTION: #List may not contain any data when size is 0");
    return false;
  }

  if (data == NULL) {
    fprintf(stderr,
            "\n'LIST QUERY EXCEPTION: void *data' passed in function #ListContains() throws "
            "NullPointerException");
    exit(EXIT_FAILURE);
    return false;
  }

  for (size_t i = 0; i < list->size; i++) {
    if (list->data[i] == data) {
      return true;
    }
  }

  return false;
}

List *ListFilter(List *list, bool (*predicate)(void *)) {
  List *filtered = NewList(NULL);

  for (size_t i = 0; i < list->size; i++) {
    if (predicate(list->data[i])) {
      ListAdd(filtered, list->data[i]);
    }
  }

  return filtered;
}

void ListForEach(List *list, void (*function)(void *)) {
  for (size_t i = 0; i < list->size; i++) {
    function(list->data[i]);
  }
}

void *ListGet(List *list, unsigned int index) {
  if (index >= list->size) {
    fprintf(stderr,
            "\nLIST GET EXCEPTION: #List struct ArrayIndexOutOfBoundsException: '%i' \n Failed to "
            "fetch data from list.\n",
            index);
    exit(EXIT_FAILURE);
    return NULL;
  }

  if (list->data[index] == NULL) {
    fprintf(stderr,
            "\nLIST GET EXCEPTION: #List struct NullPointerException: '%i' \n Failed to fetch data "
            "from list.\n",
            index);
    exit(EXIT_FAILURE);
    return NULL;
  }

  return list->data[index];
}

void *ListPop(List *list) {
  if (isListEmpty(list)) {
    fprintf(stderr, "LIST POP EXCEPTION: Failed to pop element from list. List is empty\n");
    exit(EXIT_FAILURE);
    return NULL;
  }

  void *last = ListRemove(list, ListLast(list));
  return last;
}

void *ListFirst(List *list) {
  if (isListEmpty(list)) {
    fprintf(stderr, "LIST QUERY FIRST EXCEPTION: Failed to get first element from list. List is empty\n");
    exit(EXIT_FAILURE);
    return NULL;
  }

  return list->data[0];
}

void *ListLast(List *list) {
  if (isListEmpty(list)) {
    fprintf(stderr, "LIST QUERY LAST EXCEPTION: Failed to get last element from list. List is empty\n");
    exit(EXIT_FAILURE);
    return NULL;
  }

  return list->data[list->size - 1];
}

void *ListNext(List *list, void *data) {
  for (size_t i = 0; i < list->size; i++) {
    if (list->data[i] == data) {
      return list->data[i + 1];
    }
  }

  fprintf(stderr, "LIST QUERY NEXT EXCEPTION: Failed to get next element from list. Data not found\n");
  exit(EXIT_FAILURE);
  return NULL;
}

void *ListPrev(List *list, void *data) {
  for (size_t i = 0; i < list->size; i++) {
    if (list->data[i] == data) {
      return list->data[i - 1];
    }
  }

  fprintf(stderr, "LIST QUERY PREVIOUS EXCEPTION: Failed to get previous element from list. Data not found\n");
  exit(EXIT_FAILURE);
  return NULL;
}

size_t ListSize(List *list) { return list->size; }
bool isListEmpty(List *list) {
  if (ListSize(list) == 0) return true;
  return false;
}

void ListCopy(List *source, List *dest) {
  for (size_t i = 0; i < source->size; i++) {
    ListAdd(dest, source->data[i]);
  }

  dest->size = source->size;
  dest->capacity = source->capacity;
}