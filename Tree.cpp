// Implementation of tree

#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
	string data;			//stores the symbol
	int frequency;			//stores the individual frequency or sum of frequencies
	string BinaryCode;		//stores binary encoding of each character in the tree
	//pointers to left and right children
	TreeNode* left;
	TreeNode* right;

	TreeNode() {			//default constructor
		data = "";
		frequency = 0;
		BinaryCode = "";
	}

	TreeNode(string d, int frq) {	//parametrized constructor
		data = d;
		frequency = frq;
		BinaryCode = "";
		left = right = NULL;
	}
};

struct Tree
{
	TreeNode* root;
	string Encoding = "";	//string to store encoding of characters

	Tree() { root = NULL; }

	//insert a leaf node into tree - TASK 1
	void insertTask1(TreeNode* n) {
		if (root == NULL)	//first element being inserted
		{
			TreeNode* temp = new TreeNode;	//empty node
			temp->left = n;
			temp->right = NULL;
			root = temp;
		}
		else if (root->right == NULL)	//second element being added
		{
			root->right = n;
		}
		else	//two or more elements present
		{	//add to top
			TreeNode* tmp = new TreeNode;	//empty node
			tmp->right = n;
			tmp->left = root;
			root = tmp; //root moves up
			return;
		}
	}

	//encode each leaf node (symbol) according to its position and display
	void EncodeLeafNodes(TreeNode* n) {
		//add "0" to Binary code every time we go left
		if (n->left->left != NULL)	//if second last level not reached
		{
			n->left->BinaryCode = n->BinaryCode + "0";
			EncodeLeafNodes(n->left);
		}

		//if leaf node at next level, output
		if (n->left->left == NULL && n->left->right == NULL)
		{
			n->left->BinaryCode = n->BinaryCode + "0";
			if (n->left->data != "\n")
				cout << n->left->data << ' ' << n->left->BinaryCode << endl;
			else
				cout << "\\n" << ' ' << n->left->BinaryCode << endl;
		}

		//add "1" to Binary code every time we go right
		if (n->right->right != NULL)
		{
			n->right->BinaryCode = n->BinaryCode + "1";
			EncodeLeafNodes(n->right);
		}

		//if leaf node at next level, output
		if (n->right->left == NULL && n->right->right == NULL)
		{
			n->right->BinaryCode = n->BinaryCode + "1";
			if (n->right->data != "\n")
				cout << n->right->data << ' ' << n->right->BinaryCode << endl;
			else
				cout << "\\n" << ' ' << n->right->BinaryCode << endl;
		}
	}

	void binaryEncodeSymbols(TreeNode* n, string d) {
		if (n == NULL)	//if node is null, return
			return;

		//if leaf child has same data as the one we want to encode then store its encoding
		if ((n->left == NULL && n->right == NULL) && n->data == d)
			Encoding += n->BinaryCode;

		binaryEncodeSymbols(n->left, d);	//repeat for left subtree
		binaryEncodeSymbols(n->right, d);	//repeat for right subtree
	}
};