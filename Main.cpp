// File containing main

#include <iostream>
#include <fstream>
#include "Queue.cpp"
using namespace std;

int main()
{
    //ask for file name
    /*string fileName;
    cout << "Please enter a text file name: ";
    cin >> fileName;

    //validate entered file name
    while (fileName != "foo.txt" && fileName != "foo")
    {
        cout << "Cannot find file. Please reenter filename: ";
        cin >> fileName;
    }*/

    cout << "Opening foo.txt" << endl;

    fstream file;
    file.open("foo.txt");   //open the file

    if (!file)      //if file could not be opened, terminate the program
        return 0; 

    Queue queue;                      //priority queue that stores leaf nodes in ascending order of frequency
    char character; string temp = ""; //empty string to convert character to string for insertion
    while (file.get(character))       //read the file character by character
    {
        TreeNode* tmp = new TreeNode(temp + character, 1);  //store each character as a leaf node
        queue.enqueue(tmp); //enqueue each character according to its frequency
    }
    file.close();

    //------------------------Tree-based Huffman coding scheme----------------------
    //--------------------------------- OUTPUT ---------------------------------
    Tree* t1 = new Tree;
    t1->root = queue.InsertIntoTree(); //insert queue elements into tree

    cout << endl << "The simple Huffman coding is:" << endl;
    //encode the symbols and display the tree
    t1->EncodeLeafNodes(t1->root);

    //output encoding of each character of file
    temp = "";
    file.open("foo.txt");
    cout << "'";
    while (file.get(character))
    {
        cout << character;
        t1->binaryEncodeSymbols(t1->root, temp + character); //binary encode each character of file
    }
    cout << "' is encoded as: " << endl;
    cout << t1->Encoding << endl;   //display binary encoded string of text in file
    file.close();
    //------------------------------ OUTPUT END ------------------------------

    //-------------------------- Optimal Huffman tree ------------------------
    Tree* t2 = new Tree;
    while (queue.first->next != NULL) //until one element left in queue
    {
        //dequeue the first two elements of queue, i.e. elements with least frequencies
        TreeNode* tmp1 = queue.dequeue();
        TreeNode* tmp2 = queue.dequeue();

        //store a new node which sums the first two elements and stores the elements as left and right child
        TreeNode* newNode = new TreeNode;
        newNode->data = tmp1->data + tmp2->data;
        newNode->frequency = tmp1->frequency + tmp2->frequency;
        newNode->left = tmp1;
        newNode->right = tmp2;

        queue.enqueue(newNode); //enqueue the new node (that has sum of the least frequent symbols)

        t2->root = newNode; //root node will point to the newest node created
    }

    //------------------------------ OUTPUT ------------------------------
    cout << endl << "The optimal Huffman code is: " << endl;
    //encode the symbols and display the tree
    t2->EncodeLeafNodes(t2->root);

    temp = "";
    file.open("foo.txt");
    cout << "'";
    while (file.get(character))
    {
        cout << character;
        t2->binaryEncodeSymbols(t2->root, temp + character); //binary encode each character of file
    }
    cout << "' is encoded as: " << endl;
    cout << t2->Encoding << endl;   //display binary encoded string of text in file
    file.close();
    //------------------------------- OUTPUT END -------------------------------

    //---------------------------- COMPRESSION RATIO ----------------------------
    //compression ratio = bits required before compression / bits required after compression
    cout << endl << "The compression ratio is: " << endl;

    //queue first contains total no. of characters, and tree encoding will have a length
    cout << (queue.first->nodeData->frequency * 8.0) / t2->Encoding.length() << endl;

    return 0;
}
