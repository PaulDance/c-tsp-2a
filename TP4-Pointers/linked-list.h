#include <stdbool.h>


#ifndef TP4_POINTERS_LINKED_LIST_H
#define TP4_POINTERS_LINKED_LIST_H

typedef struct LinkedList {
    void* head;
    struct LinkedList* tail;
} LinkedList;

bool isEmpty(LinkedList* linkedList);

void initLinkedList(LinkedList* linkedList, void* head, LinkedList* tail);

LinkedList* newLinkedList();

LinkedList* newLinkedListOf(void* head, LinkedList* tail);

void withIntegerElements(const void* element);

void withFloatElements(const void* element);

void withStringElements(const void* element);

void printLinkedList(LinkedList* linkedList, void (* printElementFunction)(const void*));

void push(LinkedList* linkedList, void* element);

void pushLast(LinkedList* linkedList, void* element);

void* pop(LinkedList* linkedList);

void* popLast(LinkedList* linkedList);

void* getLast(LinkedList* linkedList);

size_t getLength(LinkedList* linkedList);

void insertElementAt(LinkedList* linkedList, void* element, size_t index);

void* removeElementAt(LinkedList* linkedList, size_t index);

void freeLinkedList(LinkedList* linkedList);

#endif //TP4_POINTERS_LINKED_LIST_H
