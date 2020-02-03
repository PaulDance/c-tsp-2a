//
// Created by pauldance on 03/02/2020.
//

#include <stdio.h>
#include "linked-list.h"


int main() {
	LinkedList* linkedList = newLinkedListOf("hello", newLinkedListOf("world", newLinkedList()));
	printLinkedList(linkedList, withStringElements);
	push(linkedList, "wow");
	printLinkedList(linkedList, withStringElements);
	printf("%s\n", pop(linkedList));
	printLinkedList(linkedList, withStringElements);
	
	//freeLinkedList(linkedList);
	return 0;
}
