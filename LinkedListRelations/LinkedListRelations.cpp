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

class SingleLinkedListOperations
{
public:
    Node* create(vector<int>& input)
    {
        if (input.size() == 0)
        {
            return nullptr;
        }
        // How do we use a sentinal node???
        Node* head = new Node(input[0]);
        Node* runner = head;
        for (int i = 1; i < input.size(); i++)
        {
            runner->next = new Node(input[i]);
            runner = runner->next;
        }
        return head;
    }

    void print(Node* head)
    {
        cout << "  ";
        if (head == nullptr)
        {
            cout << "EMPTY" << endl;
            return;
        }

        while (head != nullptr)
        {
            cout << head->val << " ";
            head = head->next;
        }
        cout << endl;
    }

    void insertAtHead(Node*& head, int val)
    {
        Node* temp = new Node(val);
        temp->next = head;
        head = temp;
    }

    void insertAtTail(Node*& head, int val)
    {
        Node* temp = new Node(val);
        if (head == nullptr)
        {
            head = temp;
            return;
        }
        Node* runner = head;
        while (runner->next != nullptr)
        {
            runner = runner->next;
        }
        runner->next = temp;
    }

    Node* findValue(int val)
    {}
    Node* deleteValue(int val)
    {}
};

class DoubleLinkedListOperations
{
    // menh!
};

class DoubleCircularLinkedListOperations
{
public:
    NodeDouble* create(vector<int>& input)
    {}
    void insertAtHead(NodeDouble* head, int val)
    {}
    void insertAtTail(NodeDouble* head, int val)
    {}
    NodeDouble* findValue(int val)
    {}
    NodeDouble* deleteValue(int val)
    {}
};

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

void testSingleLinkedListOperations(vector<int>& input)
{
    cout << "TEST SINGLE LL OPERATIONS" << endl;

    SingleLinkedListOperations sllo;
    cout << "Create Single LLs:" << endl;
    Node* headEmpty = sllo.create(vector<int>());
    Node* headOne = sllo.create(vector<int>{10});
    Node* headInput = sllo.create(input);

    cout << "Print Single LLs:" << endl;
    sllo.print(headEmpty);
    sllo.print(headOne);
    sllo.print(headInput);

    int val;

    val = 11;
    cout << "Insert to Head of Single LLs:" << endl;
    cout << "Value = " << val << endl;
    sllo.insertAtHead(headEmpty, val);
    sllo.insertAtHead(headOne, val);
    sllo.insertAtHead(headInput, val);
    cout << "Print Single LLs:" << endl;
    sllo.print(headEmpty);
    sllo.print(headOne);
    sllo.print(headInput);

    val = 12;
    cout << "Create Single LLs (set 2):" << endl;
    Node* headEmpty2 = sllo.create(vector<int>());
    Node* headOne2 = sllo.create(vector<int>{10});
    Node* headInput2 = sllo.create(input);
    cout << "Insert to Tail of Single LLs (set 2):" << endl;
    cout << "Value = " << val << endl;
    sllo.insertAtTail(headEmpty2, val);
    sllo.insertAtTail(headOne2, val);
    sllo.insertAtTail(headInput2, val);
    cout << "Print Single LLs:" << endl;
    sllo.print(headEmpty2);
    sllo.print(headOne2);
    sllo.print(headInput2);
}

int main()
{
    vector<int> input{1,2,3,4,5,6,7,8,9,};
    cout << "ORIGINAL:" << endl;
    cout << "  ";
    for (auto a : input)
    {
        cout << a << " ";
    }
    cout << endl;

    testSingleLinkedListOperations(input);

    return 0;
}

