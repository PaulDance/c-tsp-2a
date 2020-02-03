//
// Created by pauldance on 03/02/2020.
//

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
	}
	else {
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

void* pop(LinkedList* linkedList) {
	if (isEmpty(linkedList)) {
		return NULL;
	}
	else {
		void* result = linkedList->head;
		
		linkedList->head = linkedList->tail->head;
		linkedList->tail = linkedList->tail->tail;
		
		return result;
	}
}
