#include <stdlib.h>
#include <stdio.h>
#include "linked-list.h"


bool isEmpty(LinkedList* linkedList) {
    return linkedList->head == NULL && linkedList->tail == NULL;
}

void initLinkedList(LinkedList* linkedList, void* head, LinkedList* tail) {
    linkedList->head = head;
    linkedList->tail = tail;
}

LinkedList* newLinkedList() {
    return (LinkedList*) malloc(sizeof(LinkedList));
}

LinkedList* newLinkedListOf(void* head, LinkedList* tail) {
    LinkedList* linkedList = newLinkedList();
    initLinkedList(linkedList, head, tail);
    return linkedList;
}

void withIntegerElements(const void* element) {
    printf("%i", *((const int*) element));
}

void withFloatElements(const void* element) {
    printf("%f", *((const double*) element));
}

void withStringElements(const void* element) {
    printf("\"%s\"", (const char*) element);
}

void printLinkedList(LinkedList* linkedList, void (* printElementFunction)(const void*)) {
    if (isEmpty(linkedList)) {
        puts("[]");
    } else {
        printf("[");

        for (LinkedList* ll = linkedList; !isEmpty(ll); ll = ll->tail) {
            printElementFunction(ll->head);
            printf(", ");
        }

        puts("\b\b]");
    }
}

void push(LinkedList* linkedList, void* element) {
    linkedList->tail = newLinkedListOf(linkedList->head, linkedList->tail);
    linkedList->head = element;
}

void pushLast(LinkedList* linkedList, void* element) {
    LinkedList* ll = linkedList;

    while (!isEmpty(ll)) {
        ll = ll->tail;
    }

    push(ll, element);
}

void* pop(LinkedList* linkedList) {
    if (isEmpty(linkedList)) {
        return NULL;
    } else {
        void* result = linkedList->head;

        linkedList->head = linkedList->tail->head;
        linkedList->tail = linkedList->tail->tail;

        return result;
    }
}

void* getLast(LinkedList* linkedList) {
    if (isEmpty(linkedList)) {
        return NULL;
    } else {
        LinkedList* ll = linkedList;

        while (!isEmpty(ll->tail)) {
            ll = ll->tail;
        }

        return ll->head;
    }
}

void* popLast(LinkedList* linkedList) {
    if (isEmpty(linkedList)) {
        return NULL;
    } else {
        LinkedList* ll = linkedList;

        while (!isEmpty(ll->tail)) {
            ll = ll->tail;
        }

        void* result = ll->head;

        ll->head = ll->tail->head;
        ll->tail = ll->tail->tail;

        return result;
    }
}

size_t getLength(LinkedList* linkedList) {
    size_t length = 0UL;

    for (LinkedList* ll = linkedList; !isEmpty(ll); ll = ll->tail) {
        length++;
    }

    return length;
}

void insertElementAt(LinkedList* linkedList, void* element, size_t index) {
    LinkedList* ll = linkedList;

    while (!isEmpty(ll) && index != 0UL) {
        ll = ll->tail;
        index--;
    }

    if (index == 0UL) {
        push(ll, element);
    }
}

void* removeElementAt(LinkedList* linkedList, size_t index) {
    LinkedList* ll = linkedList;

    while (!isEmpty(ll) && index != 0UL) {
        ll = ll->tail;
        index--;
    }

    if (index != 0UL) {
        return NULL;
    } else {
        return pop(ll);
    }
}

void freeLinkedList(LinkedList* linkedList) {
    if (!isEmpty(linkedList)) {
        freeLinkedList(linkedList->tail);
    }

    free(linkedList);
}
