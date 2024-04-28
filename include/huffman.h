#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
using namespace std;
class Node
{
private:
    char ch;
    int freq;

public:
    Node(char c, int f);
    char getChar();
    int getFreq();
    void setChar(char c);
    void setFreq(int f);
    Node *left, *right;
    Node *next, *prev;
};

class linkedList
{
private:
    /* data */
public:
    Node *head;
    Node *tail;
    int size;
    linkedList();
    void insertNode(Node *node);
    void display();
    void arrToLinkedList(Node **, int);
    Node *extractMin();
    void buildHuffmanTree();
    void encode();
    void printCodes(Node *temp, string str);
};

class minHeap
{
private:
    int size;
    int capacity;
    Node **array;

public:
    minHeap(int size, int capacity);
    Node **getArr();
    void setSize(int);
    void setCapacity(int);
    int getSize();
    int getCapacity();
    void insertChar(char c);
    void insertString(const char *str);
    void displayArray();
};

#endif