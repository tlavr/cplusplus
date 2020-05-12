// Last edit 05.05.2020 by Lavrukhin Timur
//
// This file contains functions to create and remove every 5th node from the simple linked list:
//
// main()	-	main function of the programm, 
//				creates simple linked list,
//				and outputs it before and after processing
//
// struct List - basic structure for linked list
//
// newNode = addNexNode(node, payload) - function to add new node to the list
//				node	-    parent node for the new node
//              payload -	 new node's payload
//				newNode	-	 pointer to the new created node
//
// void removeEvery5thNode(head)  - function to remove every 5th node beginning with the "head" node passed to it
//              head    -	 node from which need to remove every 5th node


#include <iostream>

using namespace std;

struct List{
	struct List* next;
	int payload;
};

struct List* addNextNode(struct List* node, int nextPayload) {
	struct List* nextNode = new struct List;
	nextNode->payload = nextPayload;
	nextNode->next = NULL;
	node->next = nextNode;
	return nextNode;
}

void printAllNodes(struct List head) {
	struct List* curNode = &head;
	while (curNode != NULL){
		cout << "Payload: " << curNode->payload << "\tnode: " << curNode << "\tnode next: " << curNode->next << endl;
		curNode = curNode->next;
	}
}

void removeEvery5thNode(struct List head) {
	struct List* curNode = &head;
	struct List* prevNode;
	int cnt = 1;
	while (curNode != NULL){
		if (cnt % 5 == 0) {
			prevNode->next = curNode->next;
			curNode = curNode->next;
		}
		else {
			prevNode = curNode;
			curNode = curNode->next;
		}
		++cnt;
	} 
}
 
int main() {
	struct List head;
	struct List* curNode = &head;
	head.payload = 1;
	head.next = NULL;

	for (int ii = 2; ii < 26; ++ii) {
		curNode = addNextNode(curNode, ii);
	}
	cout << "before: " << endl;
	printAllNodes(head);
	removeEvery5thNode(head);
	cout << "after: " << endl;
	printAllNodes(head);
	return 0;
}