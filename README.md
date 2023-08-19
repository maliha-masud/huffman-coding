# Data Compression
## Huffman coding for text files in C++

## Project Description
This project builds a data compression method; i.e., it conveys the same information in a smaller amount of space given some particular data. The focus is on compressing text files.

**How computers internally represent text**

Computers save information as a series of bytes. A byte is an eight-bit value that ranges from 0 to 255. It assigns each character to an eight-bit (a value from 0 to 255). The ASCII encoding is responsible for this mapping.
> For instance, consider the text “A b ????”. Using the ASCII table above, this is represented as the following sequence of bytes: “65 32 98 32 63 63 63 63”.
> If we write out the binary string for each character and concatenate them together, we get “0100000100100000011000100010000000111111001111110011111100111111”. Storing our original string with the ASCII encoding requires 8*8 = 64 bits.

If we weren’t forced to use eight bits for every character, and could instead use the binary encoding “? = 0, [space] = 10, A = 110, b = 111”., then the string “A b ????” would become “11010111100000”. This is only 14 bits, significantly smaller than the 64 bits that ASCII requires. Also, none of these codes are a prefix of any others, so there is no ambiguity when decoding.
Here, the string is compressed by finding a different encoding for the characters, which minimized the number of bits needed.

### Huffman Trees
A Huffman code is defined by a tree whose leaves are the symbols in the alphabet.

<img width="200" alt="image" src="https://github.com/maliha-masud/huffman-coding/assets/121713404/f446cb73-0621-451d-a3c2-314f5c9cf827">

If we indicate going left by 0 and going right by 1, then the Huffman code for the above tree is:

<img width="77" alt="image" src="https://github.com/maliha-masud/huffman-coding/assets/121713404/ae6aa108-6cbf-4d95-a788-eca093d716aa">

> **A string of symbols "aadbaaca" would be encoded as 0011100001010. The original 64 bits have been reduced to 13 bits. We get compression because the symbol “a” occurs quite frequently in the original and the Huffman code uses just one bit to encode it.**

**Decoding a Huffman code**

Start at the root of the tree. If you are at a leaf output the symbol; otherwise, read a bit and go left if 0 and right if 1 is read and continue in that manner until reaching a leaf.

An optimal Huffman code is one that produces the shortest code given frequencies for the symbols. The algorithm uses a priority queue. First, the frequency of each symbol in the input is calculated. A leaf node is made for each symbol, and its frequency is stored in the node.

The following is done repeatedly:
* Find the two trees with the smallest frequencies.
* Make them the left and right children of a new node whose frequency the sum of the two frequencies.
* When one tree remains, it is done.
>**In the example above the frequencies are a:5, b:1, c:1, d:1**

<img width="209" alt="image" src="https://github.com/maliha-masud/huffman-coding/assets/121713404/bd4a9508-9108-4403-ad43-3562255d6bb0">

---

<img width="299" alt="image" src="https://github.com/maliha-masud/huffman-coding/assets/121713404/443c9120-e3c9-427a-8e39-8e646b316237">


## Code Description
The program reads the file "foo.txt", computes the optimal Huffman code of the string in the file, and prints it. The compression ratio is then printed.
* A simple tree-based Huffman coding scheme and its results are also shown.
* In case of the optimal Huffman code, it is efficiently traversed to generate the code to be printed out.
* The compression ratio is calculated by multiplying the number of characters in the text file by 8 (as each character is represented by 8 bits if no compression is done), and dividing it by the number of bits generated by the Huffman Tree.

In the main function, the file "foo.txt" is opened, read character by character, and each character is entered into the queue once (without repetition). If a repeat character is found, its frequency is updated in the queue. With every insertion, the queue also sorts itself in ascending order.

**Building a simple Huffman tree**

Every queue node is passed to the insert function of the Huffman tree. In the insert function, the first two elements of the queue become the leaf nodes of the Huffman tree and then the tree is built from bottom to top. Finally, the Huffman tree is constructed in a way that every character is a leaf node.
To encode the leaf nodes, the root node of the tree is passed to the function which encodes every leaf node of the tree. A “0” is added to the binary code of the nodes every time we move to the left of the tree. Otherwise, a “1” is added to the binary code of the node. By this approach, the binary codes of the leaf nodes (the nodes containing the characters) are created.
Lastly, the recursive function binaryEncodeSymbols() is used to encode the whole text file data. Each character of the file is searched in the tree and, when found, its respective binary encoding is stored for display.

**Constructing an optimal Huffman Tree**

Firstly, a while loop is used until one element is left in the priority queue. Within the loop, the dequeue() function of the queue is called twice; this function operates on the principle of "delete at start". Then an optimal Huffman tree is constructed by creating a new node dynamically which stores the sum of the frequencies and data of the two dequeued elements and stores those two particular elements as its left and right children.
Then the enqueue() function inserts the new node into the queue according to its frequency. This is repeated until the while loop is exited (one tree is left in the queue).
The nodes in the tree are encoded using the same EncodeLeafNodes() function as described above. Finally, the whole text file is encoded using Huffman Tree.
