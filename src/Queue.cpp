// Implementation of min priority queue using linked list

#include <iostream>
#include <string>
#include "Tree.cpp"
using namespace std;

struct Node {
	TreeNode* nodeData;		//stores element of type TreeNode
	Node* next;				//pointer to next node

	Node() {}
	Node(TreeNode* n) {		//parametrized constructor
		nodeData = n;
		next = NULL;
	}
};

struct Queue {
	Node* first;
	Queue() { first = NULL; }

	void enqueue(TreeNode* t) {	//place TreeNode in queue according to its frequency
		if (first == NULL)	//first element being inserted
		{
			Node* temp = new Node(t);
			first = temp;
		}
		else	//queue already exists
		{
			Node* ptr = first;
			while (ptr != NULL)	//till last node
			{
				if (ptr->nodeData->data == t->data) //if a duplicate symbol is found
				{
					ptr->nodeData->frequency += 1;	//increment frequency of already stored symbol

					//need to sort the queue in ascending order
					Node* temp = ptr;
					while (temp->next != NULL)	//check till last element
					{
						if (temp->nodeData->frequency > temp->next->nodeData->frequency) //if current > next
						{
							//swap the elements
							//temp = next
							string s1 = temp->next->nodeData->data;
							int n1 = temp->next->nodeData->frequency;
							//next = current
							temp->next->nodeData->data = temp->nodeData->data;
							temp->next->nodeData->frequency = temp->nodeData->frequency;
							//current = temp
							temp->nodeData->data = s1;
							temp->nodeData->frequency = n1;
						}
						temp = temp->next;
					}
					//the element has been inserted in the correct place - return
					return;
				}
				ptr = ptr->next;
			}

			//a non-duplicate element is being inserted
			Node* tmp2 = new Node(t);
			Node* ptr2 = first;
			Node* pre = NULL;

			//if queue has not ended && added freq >= current freq, keep traversing
			while (ptr2 != NULL && tmp2->nodeData->frequency >= ptr2->nodeData->frequency)
			{
				pre = ptr2;
				ptr2 = ptr2->next;
			}

			if (pre == NULL) //no traversing has been done: need to add at first element
			{
				tmp2->next = first;
				first = tmp2;
			}
			else
			{	//add tmp2 in the middle of pre and ptr2
				pre->next = tmp2;
				tmp2->next = ptr2;
			}
		}
	}

	TreeNode* dequeue() {	//return first treeNode in queue
		TreeNode* temp = new TreeNode;

		//assign all values of first to temp
		temp->data = first->nodeData->data;
		temp->frequency = first->nodeData->frequency;
		temp->left = first->nodeData->left;
		temp->right = first->nodeData->right;

		//increment first and delete old first
		Node* ptr = first;
		first = first->next;
		delete ptr;

		//return the tree node that was in first
		return temp;
	}

	//Task 1 Insertion from queue into tree
	TreeNode* InsertIntoTree() { //insert each element of queue into tree without changing the queue
		Tree* t1 = new Tree;

		Node* ptr = first;	//store first element of queue

		while (ptr != NULL) //till last element of queue
		{
			t1->insertTask1(ptr->nodeData);	//insert each tree node in queue into tree
			ptr = ptr->next;
		}

		return t1->root;	//return the root node of the created tree
	}
};