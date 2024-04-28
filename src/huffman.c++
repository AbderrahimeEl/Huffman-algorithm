#include <cstdlib>
#include "../include/huffman.h"
#include "huffman.h"

Node::Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr), next(nullptr), prev(nullptr) {}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        cout << arr[i];

    cout << "\n";
}

char Node::getChar()
{
    return ch;
}
int Node::getFreq()
{
    return freq;
}
void Node::setChar(char c)
{
    ch = c;
}
void Node::setFreq(int f)
{
    freq = f;
}

minHeap::minHeap(int size, int capacity)
{
    this->size = size;
    this->capacity = capacity;
    this->array = new Node *[this->capacity];

    for (int i = 0; i < capacity; i++)
    {
        array[i] = new Node('$', 0);
    }
}

void minHeap::setSize(int size)
{
    this->size = size;
}

void minHeap::setCapacity(int capacity)
{
    this->capacity = capacity;
}

int minHeap::getSize()
{
    return this->size;
}

int minHeap::getCapacity()
{
    return this->capacity;
}

Node **minHeap::getArr()
{
    return array;
}

void minHeap::insertChar(char c)
{
    if (array[c - 97]->getChar() == '$' && array[c - 97]->getFreq() == 0)
    {
        array[c - 97]->setChar(c);
        array[c - 97]->setFreq(1);
    }
    else
        array[c - 97]->setFreq(array[c - 97]->getFreq() + 1);
}

void minHeap::insertString(const char *str)
{
    while (*str != '\0')
    {
        this->insertChar(*str);
        str++;
    }
}

void minHeap::displayArray()
{
    for (int i = 0; i < capacity; i++)
    {
        if (this->array[i] == nullptr)
            continue;
        cout << array[i]->getChar() << "   :" << array[i]->getFreq() << endl;
    }
}

linkedList::linkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}
void linkedList::insertNode(Node *node)
{
    if (this->size == 0)
    {
        this->head = node;
        this->tail = node;
        this->size++;
        return;
    }
    Node *temp = this->head;
    // start insertion
    if (temp->getFreq() >= node->getFreq())
    {
        this->head->prev = node;
        node->next = this->head;
        this->head = node;
        this->size++;
        return;
    }
    // end insertion
    temp = this->tail;
    if (this->tail->getFreq() <= node->getFreq())
    {
        this->tail->next = node;
        node->prev = this->tail;
        this->tail = node;
        this->size++;
        return;
    }
    // middle insertion
    temp = this->head;
    Node *temp2 = temp->next;
    while (temp->next != NULL)
    {
        if (temp->next->getFreq() >= node->getFreq())
        {
            node->prev = temp;
            temp->next = node;
            node->next = temp2;
            temp2->prev = node;
            this->size++;
            return;
        }
        temp = temp->next;
        if (temp != NULL)
            temp2 = temp->next;
    }
}

void linkedList::display()
{
    Node *temp;
    temp = this->head;
    while (temp != NULL)
    {
        printf("%c --> %d\n", temp->getChar(), temp->getFreq());
        temp = temp->next;
    }
    printf("\tsize = %d", this->size);
    printf("\n\n\n");
}

void linkedList::arrToLinkedList(Node **array, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (array[i]->getChar() == '$' && array[i]->getFreq() == 0)
            continue;
        this->insertNode(array[i]);
    }
}

Node *linkedList::extractMin()
{
    // this->display();
    if (this->size == 0)
        return nullptr;

    Node *minNode = this->head;
    Node *temp = this->head->next;

    while (temp != nullptr)
    {
        if (temp->getFreq() < minNode->getFreq())
            minNode = temp;
        temp = temp->next;
    }

    if (minNode == this->head)
    {
        this->head = minNode->next;
        if (this->head != nullptr)
            this->head->prev = nullptr;
    }
    else if (minNode == this->tail)
    {
        this->tail = minNode->prev;
        if (this->tail != nullptr)
            this->tail->next = nullptr;
    }
    else
    {
        minNode->prev->next = minNode->next;
        minNode->next->prev = minNode->prev;
    }

    this->size--;
    return minNode;
}

void linkedList::buildHuffmanTree()
{
    Node *left, *right, *top;
    while (this->size > 1)
    {
        left = extractMin();
        right = extractMin();
        top = new Node('0', left->getFreq() + right->getFreq());
        top->left = left;
        top->right = right;
        this->insertNode(top);
    }
}
void linkedList::printCodes(Node* temp,string str)
{
    if(!temp) return;
    if (temp->getChar() != '0')
        cout << temp->getChar() << ": " << str << "\n";

    printCodes(temp->left, str + "0");
    printCodes(temp->right, str + "1");
}