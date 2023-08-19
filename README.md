# Data Compression
## Huffman coding for text files in C++

This project builds a data compression method: it conveys the same information in a smaller amount of space given some particular data. The focus is on compressing text files.

**How computers internally represent text**
Computers save information as a series of bytes. A byte is an eight-bit value that ranges from 0 to 255. It assigns each character to an eight-bit (a value from 0 to 255). The ASCII encoding is responsible for this mapping.
> For instance, consider the text “A b ????”. Using the ASCII table above, this is represented as the following sequence of bytes: “65 32 98 32 63 63 63 63”.
> If we write out the binary string for each character and concatenate them together, we get “0100000100100000011000100010000000111111001111110011111100111111”. Storing our original string with the ASCII encoding requires 8*8 = 64 bits.

If we weren’t forced to use eight bits for every character, and we could instead use the binary encoding “? = 0, [space] = 10, A = 110, b = 111”., then our string “A b ????” would become “11010111100000”. This is only 14 bits, significantly smaller than the 64 bits that ASCII requires. Also, none of these codes are a prefix of any others, so there is no ambiguity when decoding.
Here, the string is compressed by finding a different encoding for the characters, which minimized the number of bits needed.

### Huffman Trees
A Huffman code is defined by a tree, whose leaves are the symbols in the alphabet.
<img width="88" alt="Screenshot 2023-08-19 150937" src="https://github.com/maliha-masud/huffman-coding/assets/121713404/f5ff562a-6168-48e9-9232-080a790f55ae">

If we indicate going left by 0 and going right by 1, then the Huffman code for the above tree is:
<img width="43" alt="image" src="https://github.com/maliha-masud/huffman-coding/assets/121713404/f211c9b0-9f7b-471a-b483-0bfc72be58a8">

A string of symbols aadbaaca would be encoded as 0011100001010. The original 64 bits have been reduced to 13 bits. The reason we get compression is that the symbol “a” occurs quite frequently in the original and the Huffman code uses just one bit to encode it.

**Decoding a Huffman code**
Start at the root of the tree. If you are at a leaf output the symbol; otherwise, read a bit and go left if 0 and right if 1 is read and continue in that manner until reaching a leaf.

An optimal Huffman code is one that produces the shortest code given frequencies for the symbols. The algorithm uses a priority queue. First you need to calculate the frequency of each symbol in the input. Make a leaf node for each symbol and store its frequency in the node. Repeatedly do the following, find the two trees with the smallest frequencies. Make them the left and right children of a new node whose frequency the sum of the two frequencies. When one tree remains we are done.
