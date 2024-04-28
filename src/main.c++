#include "../include/huffman.h"

int main()
{
	minHeap M(15, 15);
	M.insertString("abaccaefgabcdcdba");
	M.displayArray();
	string str;
	linkedList L;
	L.arrToLinkedList(M.getArr(),M.getSize());
	L.display();
	L.buildHuffmanTree();
	L.display();
	L.printCodes(L.head,str);
	return 0;
}