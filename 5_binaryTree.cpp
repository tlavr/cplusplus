// Last edit 05.05.2020 by Lavrukhin Timur
//
// This file contains functions to create simple binary tree, traverse it to determine it's depth and return all paths with such depth:
//
// main()	-	main function of the programm, 
//				creates simple binary tree,
//				and traverses it, outputs the depth and all paths with such depth
//
// struct TreeNode	- basic structure for binary tree
//
// Path				- list of pointers to TreeNodes
// Paths			- vector of Path
// newNode = addNexNode(node, payload) - function to add new node to the list
//				node	-    parent node for the new node
//              payload -	 new node's payload
//				newNode	-	 pointer to the new created node
//
// newNode = makeNode(nodeValue)	- function creates new node with payload of nodeValue and return pointer to it
//					nodeValue	-	payload of created TreeNode
//					newNode		-	pointer to created TreeNode
//
// newChild = addChild(curNode, childNode,isLeft) - function adds left or right child to curNode
//					curNode		-	pointer to parent TreeNode which needs to add the childNode
//					childNode	-	pointer to child TreeNode to addChild
//					isLeft		-	true of false, if true - add as leftChild, if false - add as rightChild
//					newChild 	-	pointer to added child (used to add childs to this child)
//
// printTreeNode(node), printPaths(treePaths)	-	auxilary functions to output nodes and paths	
//
// depth = detDepth(curNode, treePaths)	-	function to determine the depth of tree and add all paths to treePaths
//					curNode		-	pointer to the root TreeNode of the binary tree
//					treePaths	-	vector of lists of TreeNodes to save all paths, in output contains all paths in the tree
//					depth		-	int numbers is depth of the tree
//
// void detPaths(treePaths, depth)	-	function processes treePaths vector from detDepth to obtain paths of needed depth
//					depth		-	int number is depth of the paths to obtain
//					treePaths	-	treePaths vector from detDepth
//
// depth = traverseTree(head, treePaths)	-	function uses detPaths and detDepth functions and traverses the tree 
//												to return depth and paths of such depth to vector passed to it
//					head		-	pointer to root node of the tree	
//					treePaths	-	vector to save paths of determined depth
//					depth		-	int number is depth of the tree

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

struct TreeNode {
	struct TreeNode* leftChild;
	struct TreeNode* rightChild;
	int nodeValue;
};

typedef list <struct TreeNode*> Path;
typedef vector<Path> Paths;

struct TreeNode *makeNode(int nodeValue) {
	struct TreeNode *newNode = new struct TreeNode;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	newNode->nodeValue = nodeValue;
	return newNode;
}

struct TreeNode *addChild(struct TreeNode *curNode, struct TreeNode *childNode, bool isLeft) {
	if (isLeft)
		curNode->leftChild = childNode;
	else
		curNode->rightChild = childNode;
	return childNode;
}

void printTreeNode(struct TreeNode* node) {
	cout.width(12);
	cout << "nodeValue: ";
	cout.width(5);
	cout << node->nodeValue;
	cout.width(10);
	cout << "node: ";
	cout.width(10);
	cout << node;
	cout.width(14);
	cout << "leftChild: ";
	cout.width(10);
	cout << node->leftChild;
	cout.width(15);
	cout << "rightChild: ";
	cout.width(10);
	cout << node->rightChild << endl;
}

void printPaths(Paths& treePaths) {
	int cnt = 1;
	for (auto ii = treePaths.begin(); ii != treePaths.end(); ++ii) {
		cout << "Path " << cnt << ": " << endl;
		++cnt;
		for (auto jj = ii->begin(); jj != ii->end(); ++jj)
			printTreeNode(*jj);
	}
}

int detDepth(struct TreeNode* curNode, Paths& treePaths){
	int depth = 1, depthLeft = 0, depthRight = 0;
	//printTreeNode(curNode);

	if (curNode->leftChild != NULL) {
		depthLeft = detDepth(curNode->leftChild, treePaths);
		treePaths.back().push_front(curNode);
	}
	if (curNode->rightChild != NULL) {
		depthRight = detDepth(curNode->rightChild, treePaths);
		treePaths.back().push_front(curNode);
	}
	if (curNode->leftChild == NULL && curNode->rightChild == NULL) {
		Path tmp;
		tmp.push_front(curNode);
		treePaths.push_back(tmp);
	}
	depth += max(depthLeft, depthRight);
	return depth;
}

void detPaths(Paths& treePaths, int depth) {
	for (auto ii = treePaths.rbegin(); ii != treePaths.rend()-1; ++ii) {
		bool needAdd = false;
		for (auto jj = ii->rbegin(); jj != ii->rend(); ++jj) {
			if(needAdd)
				(ii + 1)->push_front(*jj);
			if (*jj == *((ii + 1)->begin()))
				needAdd = true;
		}
	}
	
	treePaths.erase(remove_if(treePaths.begin(),treePaths.end(),[&depth](const Path &it){
		return it.size() < depth;
		}),\
		treePaths.end());
	/*auto ii = treePaths.begin();
	while(ii != treePaths.end()) {
		if (ii->size() < depth) {
			treePaths.erase(ii);
			ii = treePaths.begin();
		}
		else
			++ii;
	}*/
}

int traverseTree(struct TreeNode* head, Paths& treePaths) {
	if (head == NULL)
		return 0;
	int treeDepth = 0;
	treeDepth = detDepth(head, treePaths);
	detPaths(treePaths, treeDepth);
	cout << "Tree depth is " << treeDepth << endl;
	printPaths(treePaths);
	return treeDepth;
}

int main() {
	// tree structure for example:								depth	
	//							0									1
	//				1						2						2
	//			3	    4				5       6					3
	//	     7	  8		   9					   10				4
	//		    11								12					5
	//		 13									    14				6
	//		    15								 17	   16			7

	struct TreeNode *head, *head2, *head3, *tmp1, *tmp2, *tmp3;	
	Paths treePaths, tr2, tr3;

	head = makeNode(0);
	tmp1 = addChild(head, makeNode(1), true);
	tmp2 = addChild(tmp1, makeNode(3), true);
	tmp3 = addChild(tmp1, makeNode(4), false);
	tmp1 = addChild(tmp3, makeNode(9), false);
	tmp1 = addChild(tmp2, makeNode(7), true);
	tmp3 = addChild(tmp2, makeNode(8), false);
	tmp2 = addChild(tmp3, makeNode(11), true);
	tmp3 = addChild(tmp2, makeNode(13), true);
	tmp2 = addChild(tmp3, makeNode(15), false);
	tmp1 = addChild(head, makeNode(2), false);
	tmp2 = addChild(tmp1, makeNode(5), true);
	tmp3 = addChild(tmp1, makeNode(6), false);
	tmp2 = addChild(tmp3, makeNode(10), false);
	tmp3 = addChild(tmp2, makeNode(12), true);
	tmp2 = addChild(tmp3, makeNode(14), false);
	tmp3 = addChild(tmp2, makeNode(16), false);
	tmp3 = addChild(tmp2, makeNode(17), true);
	cout << "Example #1: " << endl;
	traverseTree(head, treePaths);

	head2 = makeNode(0);
	tmp1 = addChild(head2, makeNode(1), true);
	tmp2 = addChild(head2, makeNode(2), false);
	tmp3 = addChild(tmp2, makeNode(3), true);
	cout << "Example #2: " << endl;
	traverseTree(head2, tr2);

	head3 = NULL;
	cout << "Example #3: " << endl;
	traverseTree(head3, tr3);

	return 0;
}