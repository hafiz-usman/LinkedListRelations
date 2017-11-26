// LinkedListRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int val;
    Node* next;
    Node(int v) :
        val(v),
        next(nullptr)
    {}
};

struct NodeDouble
{
    int val;
    NodeDouble* next;
    NodeDouble* prev;
    NodeDouble(int v) :
        val(v),
        next(nullptr),
        prev(nullptr)
    {}
};

struct NodeFlatten
{
    int val;
    NodeFlatten* next;
    NodeFlatten* down;
    NodeFlatten(int v) :
        val(v),
        next(nullptr),
        down(nullptr)
    {}
};

class CreateSingleLinkedList
{};

class CreateDoubleLinkedList
{
    // menh!
};

class CreateDoubleCircularLinkedList
{};

class FlattenLinkedList
{
public:
    Node* flattenAppendMethod(NodeFlatten* head);
    Node* flattenDownPreference(NodeFlatten* head);
    Node* flattenNextPreference(NodeFlatten* head);
};

class CloneLinkedList
{
public:
    Node* clone(Node* head);
    NodeDouble* clone(NodeDouble* head);
};

int main()
{

    return 0;
}

