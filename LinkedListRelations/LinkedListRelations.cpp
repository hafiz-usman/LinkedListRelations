// LinkedListRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <assert.h>

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

class SingleLinkedList
{
public:
    SingleLinkedList()
    {
        //create the sentinal node!
        _head = new Node(c_sentinalValue);
    }

    Node* getHead()
    {
        return _head->next;
    }

    void create(vector<int>& input)
    {
        if (input.size() == 0)
        {
            return;
        }
        // How do we use a sentinal node???
        _head->next = new Node(input[0]);
        Node* runner = _head->next;
        for (int i = 1; i < input.size(); i++)
        {
            assert(input[i] != c_sentinalValue); // we use -1 to indicate failure!
            runner->next = new Node(input[i]);
            runner = runner->next;
        }
    }

    void print()
    {
        Node* head = _head->next;
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

    void insertAtHead(int val)
    {
        Node* temp = new Node(val);
        temp->next = _head->next;
        _head->next = temp;
    }

    void insertAtTail(int val)
    {
        Node* temp = new Node(val);
        if (_head->next == nullptr)
        {
            _head->next = temp;
            return;
        }
        Node* runner = _head->next;
        while (runner->next != nullptr)
        {
            runner = runner->next;
        }
        runner->next = temp;
    }

    Node* findValue(int val)
    {
        Node* head = _head->next;
        while (head != nullptr)
        {
            if (head->val == val)
            {
                return head;
            }
            head = head->next;
        }
        return nullptr;
    }

    Node* deleteValue(int val)
    {
        Node* head = _head->next;
        if (head == nullptr)
        {
            return nullptr;
        }

        Node* prev = nullptr;
        Node* current = head;
        while (current != nullptr)
        {
            if (current->val == val)
            {
                break;
            }
            prev = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            // value wasn't found
            return nullptr;
        }

        if (prev == nullptr)
        {
            // delete head
            head = head->next;
            delete current;
            return head;
        }
        prev->next = current->next;
        delete current;
        return head;
    }

private:
    Node* _head;
    const int c_sentinalValue = -1;
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
    NodeDouble* findValue(NodeDouble* head, int val)
    {}
    NodeDouble* deleteValue(NodeDouble* head, int val)
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

int main()
{
    vector<int> input0{ };
    vector<int> input1{ 1 };
    vector<int> input4{ 1,2,3,4, };

    int val = -1;
    Node* empty = nullptr;
    Node* one = nullptr;
    Node* four = nullptr;
    SingleLinkedList* sll = nullptr;

    SingleLinkedList sll0;
    SingleLinkedList sll1;
    SingleLinkedList sll4;
    sll0.create(input0);
    sll1.create(input1);
    sll4.create(input4);

    sll0.print();
    sll1.print();
    sll4.print();

    vector<int> toFind;
    for (int i = -1; i <= input4.size(); i++)
    {
        toFind.push_back(i);
    }
    sll = &sll0;
    for (int i = 0; i < toFind.size(); i++)
    {
        int v = toFind[i];
        Node* temp = sll0.findValue(v);
        assert(temp == nullptr);
    }
    sll = &sll1;
    for (int i = 0; i < toFind.size(); i++)
    {
        int v = toFind[i];
        Node* temp = sll0.findValue(v);
        if (i == input1[0])
        {
            assert(temp != nullptr);
            assert(temp->val == i);
        }
        else
        {
            assert(temp == nullptr);
        }
    }
    sll = &sll4;
    int j = 0;
    for (int i = 0; i < toFind.size(); i++)
    {
        int v = toFind[i];
        Node* temp = sll0.findValue(v);
        if (toFind[i] == input4[j])
        {
            assert(temp != nullptr);
            assert(temp->val == input4[j]);
            j++;
        }
        else
        {
            assert(temp == nullptr);
        }
    }

    return 0;
}

