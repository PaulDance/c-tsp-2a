//
// Created by pauldance on 03/02/2020.
//

#include <stdio.h>
#include "linked-list.h"


int main() {
	LinkedList* linkedList = newLinkedListOf("hello", newLinkedListOf("world", newLinkedList()));
	printLinkedList(linkedList, withStringElements);
	printf("length: %lu\n", getLength(linkedList));
	
	pushLast(linkedList, "wow");
	printLinkedList(linkedList, withStringElements);
	printf("length: %lu\n", getLength(linkedList));
	
	printf("last: %s\n", getLast(linkedList));
	printf("pop: %s\n", pop(linkedList));
	printLinkedList(linkedList, withStringElements);
	printf("length: %lu\n", getLength(linkedList));
	
	printf("pop last: %s\n", popLast(linkedList));
	printLinkedList(linkedList, withStringElements);
	printf("length: %lu\n", getLength(linkedList));
	
	insertElementAt(linkedList, "cool", 0UL);
	insertElementAt(linkedList, "cool", 1UL);
	printLinkedList(linkedList, withStringElements);
	printf("length: %lu\n", getLength(linkedList));
	
	printf("pop 2nd element: %s\n", removeElementAt(linkedList, 1UL));
	printLinkedList(linkedList, withStringElements);
	printf("length: %lu\n", getLength(linkedList));
	
	freeLinkedList(linkedList);
	return 0;
}
