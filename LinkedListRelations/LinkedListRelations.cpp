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
    SingleLinkedList() :
        _tail(nullptr)
    {
        //create the sentinal node!
        _head = new Node(c_sentinalValue);
    }

    Node* getHead()
    {
        return _head->next;
    }

    Node* getTail()
    {
        return _tail;
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
        _tail = runner;
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
        if (_head->next == nullptr)
        {
            // this is the first node in the list so just quickly keep track of it by making it the _tail
            _tail = temp;
        }
        temp->next = _head->next;
        _head->next = temp;
        
    }

    void insertAtTail(int val)
    {
        Node* temp = new Node(val);
        if (_head->next == nullptr)
        {
            _head->next = temp;
            _tail = temp;
            return;
        }
        Node* runner = _head->next;
        while (runner->next != nullptr)
        {
            runner = runner->next;
        }
        runner->next = temp;
        _tail = temp;
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

    void deleteValue(int val)
    {
        if (_head->next == nullptr)
        {
            return;
        }

        Node* prev = nullptr;
        Node* current = _head->next;
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
            return;
        }

        if (prev == nullptr)
        {
            // value was found at head
            // delete head
            _head->next = _head->next->next;
            if (current == _tail)
            {
                //we're deleting the only node in the list
                _tail = _head->next;
            }
            delete current;
            return;
        }

        // value was found at some node other than head
        // delete non-head node
        prev->next = current->next;
        if (current == _tail)
        {
            //we're deleting the last node in the list
            _tail = prev;
        }
        delete current;
        return;
    }

private:
    Node* _head;
    Node* _tail;
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

void testSingleLLFind()
{
    vector<int> input0{};
    vector<int> input1{ 1 };
    vector<int> input4{ 1,2,3,4, };

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

    sll = &sll0;
    assert(sll->getHead() == nullptr);
    assert(sll->getTail() == nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);

    sll = &sll1;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == 1);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);

    sll = &sll4;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == 4);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) != nullptr);
    assert(sll->findValue(3) != nullptr);
    assert(sll->findValue(4) != nullptr);
    assert(sll->findValue(5) == nullptr);
}

void testSingleLLInsertHead()
{
    vector<int> input0{};
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

    //sll0.print();
    //sll1.print();
    //sll4.print();

    val = 10;
    sll0.insertAtHead(val);
    sll1.insertAtHead(val);
    sll4.insertAtHead(val);

    sll = &sll0;
    assert(sll->getHead()->val == val);
    assert(sll->getTail()->val == val);
    assert(sll->findValue(val) != nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);

    sll = &sll1;
    assert(sll->getHead()->val == val);
    assert(sll->getTail()->val == 1);
    assert(sll->findValue(val) != nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);

    sll = &sll4;
    assert(sll->getHead()->val == val);
    assert(sll->getTail()->val == 4);
    assert(sll->findValue(val) != nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) != nullptr);
    assert(sll->findValue(3) != nullptr);
    assert(sll->findValue(4) != nullptr);
    assert(sll->findValue(5) == nullptr);
}

void testSingleLLInsertTail()
{
    vector<int> input0{};
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

    //sll0.print();
    //sll1.print();
    //sll4.print();
    val = 10;
    sll0.insertAtTail(val);
    sll1.insertAtTail(val);
    sll4.insertAtTail(val);

    sll = &sll0;
    assert(sll->getHead()->val == val);
    assert(sll->getTail()->val == val);
    assert(sll->findValue(val) != nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);

    sll = &sll1;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == val);
    assert(sll->findValue(val) != nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);

    sll = &sll4;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == val);
    assert(sll->findValue(val) != nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) != nullptr);
    assert(sll->findValue(3) != nullptr);
    assert(sll->findValue(4) != nullptr);
    assert(sll->findValue(5) == nullptr);
}

void testSingleLLDelete()
{
    vector<int> input0{};
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

    //sll0.print();
    //sll1.print();
    //sll4.print();

    val = 10;
    sll0.deleteValue(val);
    sll1.deleteValue(val);
    sll4.deleteValue(val);

    sll = &sll0;
    assert(sll->getHead() == nullptr);
    assert(sll->getTail() == nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll = &sll1;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == 1);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll = &sll4;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == 4);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) != nullptr);
    assert(sll->findValue(3) != nullptr);
    assert(sll->findValue(4) != nullptr);
    assert(sll->findValue(5) == nullptr);

    val = 5;
    sll0.deleteValue(val);
    sll1.deleteValue(val);
    sll4.deleteValue(val);
    sll = &sll0;
    assert(sll->getHead() == nullptr);
    assert(sll->getTail() == nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll = &sll1;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == 1);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll = &sll4;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == 4);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) != nullptr);
    assert(sll->findValue(3) != nullptr);
    assert(sll->findValue(4) != nullptr);
    assert(sll->findValue(5) == nullptr);

    val = 4;
    sll0.deleteValue(val);
    sll1.deleteValue(val);
    sll4.deleteValue(val);
    sll = &sll0;
    assert(sll->getHead() == nullptr);
    assert(sll->getTail() == nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll = &sll1;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == 1);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll = &sll4;
    assert(sll->getHead()->val == 1);
    assert(sll->getTail()->val == 3);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) != nullptr);
    assert(sll->findValue(2) != nullptr);
    assert(sll->findValue(3) != nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);

    val = 1;
    sll0.deleteValue(val);
    sll1.deleteValue(val);
    sll4.deleteValue(val);
    sll = &sll0;
    assert(sll->getHead() == nullptr);
    assert(sll->getTail() == nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll = &sll1;
    assert(sll->getHead() == nullptr);
    assert(sll->getTail() == nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll = &sll4;
    assert(sll->getHead()->val == 2);
    assert(sll->getTail()->val == 3);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) != nullptr);
    assert(sll->findValue(3) != nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll4.deleteValue(2);
    assert(sll->getHead()->val == 3);
    assert(sll->getTail()->val == 3);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) != nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
    sll4.deleteValue(3);
    assert(sll->getHead() == nullptr);
    assert(sll->getTail() == nullptr);
    assert(sll->findValue(-1) == nullptr);
    assert(sll->findValue(0) == nullptr);
    assert(sll->findValue(1) == nullptr);
    assert(sll->findValue(2) == nullptr);
    assert(sll->findValue(3) == nullptr);
    assert(sll->findValue(4) == nullptr);
    assert(sll->findValue(5) == nullptr);
}

int main()
{
    testSingleLLFind();
    testSingleLLInsertHead();
    testSingleLLInsertTail();
    testSingleLLDelete();

    return 0;
}

