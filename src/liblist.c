#include "liblist.h"

#include <stdlib.h>

List *NewList(List *optional) {
  List *list = malloc(sizeof(List));

  if (list == NULL) {
    fprintf(stderr, "Failed creating new list, ERROR ALLOCATING MEMORY\n");
    exit(EXIT_FAILURE);
  }

  *list->data = malloc(INIT_CAP * sizeof(void *));

  if (list->data == NULL) {
    fprintf(stderr,
            "Failed to allocate memory for List's data field. ERROR ALLOCATING "
            "MEMORY\n");
    free(list);
    exit(EXIT_FAILURE);
  }

  list->size = 0;
  list->capacity = INIT_CAP;

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
    *list->data = realloc(list->data, list->capacity * sizeof(void *));

    if (list->data == NULL) {
      fprintf(
          stderr,
          "Failed to allocate memory for List's data field. ERROR ALLOCATING "
          "MEMORY\n");
      ListFreeMemory(list);
      exit(EXIT_FAILURE);
    }
  }

  list->data[list->size++] = data;
}

void ListRemove(List *list, void *data) {
  for (int i = 0; i < list->size; i++) {
    if (list->data[i] == data) {
      list->data[i] = list->data[list->size - 1];
      list->data[list->size - 1] = NULL;
      list->size--;
      return;
    }
  }

  fprintf(stderr, "Failed to remove data from list. Data not found\n");
  exit(EXIT_FAILURE);
}

void ListPop(List *list) {
  if (list->size == 0) {
    fprintf(stderr, "Failed to pop element from list. List is empty\n");
    exit(EXIT_FAILURE);
  }

  void *last = ListLast(list);
  last = NULL;
  list->size--;
}

void *ListFirst(List *list) {
  if (list->size == 0) {
    fprintf(stderr, "Failed to get first element from list. List is empty\n");
    exit(EXIT_FAILURE);
  }

  return list->data[0];
}

void *ListLast(List *list) {
  if (list->size == 0) {
    fprintf(stderr, "Failed to get last element from list. List is empty\n");
    exit(EXIT_FAILURE);
  }

  return list->data[list->size - 1];
}

void *ListNext(List *list, void *data) {
  for (int i = 0; i < list->size; i++) {
    if (list->data[i] == data) {
      return list->data[i + 1];
    }
  }

  fprintf(stderr, "Failed to get next element from list. Data not found\n");
  exit(EXIT_FAILURE);
}

void *ListPrev(List *list, void *data) {
  for (int i = 0; i < list->size; i++) {
    if (list->data[i] == data) {
      return list->data[i - 1];
    }
  }

  fprintf(stderr, "Failed to get previous element from list. Data not found\n");
  exit(EXIT_FAILURE);
}

void ListCopy(List *source, List *dest) {
  for (int i = 0; i < source->size; i++) {
    ListAdd(dest, source->data[i]);
  }

  dest->size = source->size;
  dest->capacity = source->capacity;
}