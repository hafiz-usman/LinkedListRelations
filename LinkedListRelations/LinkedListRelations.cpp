// LinkedListRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

//
// If you want to use sentinal nodes for search and/or delete, you should ensure callers aren't going to make concurrent calls
// If concurrency is a requirement, you're better off using plain-old null pointer checks!
//
const int c_sentinalValue = -1;

struct Node
{
    int val;
    Node* next;
    Node() :
        val(c_sentinalValue),
        next(nullptr)
    {}
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
    NodeDouble() :
        val(c_sentinalValue),
        next(nullptr),
        prev(nullptr)
    {}
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
        _head(nullptr),
        _tail(nullptr),
        _pSentinal(&_sentinal)
    {
        //setup the sentinal node!
        _pSentinal->val = c_sentinalValue;
    }

    Node* getHead()
    {
        return _head;
    }

    Node* getTail()
    {
        return _tail;
    }

    void create(vector<int>& input)
    {
        if (_head != nullptr)
        {
            cout << "Can't override existing list!" << endl;
            return;
        }

        if (input.size() == 0)
        {
            return;
        }

        _head = new Node(input[0]);
        _tail = _head;
        for (int i = 1; i < input.size(); i++)
        {
            assert(input[i] != c_sentinalValue); // we use -1 to indicate failure!
            _tail->next = new Node(input[i]);
            _tail = _tail->next;
        }
    }

    void print()
    {
        Node* temp = _head;
        cout << "  ";
        if (temp == nullptr)
        {
            cout << "EMPTY" << endl;
            return;
        }

        while (temp != nullptr)
        {
            cout << temp->val << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void insertAtHead(int val)
    {
        if (val == c_sentinalValue)
        {
            cout << "Can't insert value = " << val << " because it matches sentinal" << endl;
            return;
        }

        Node* temp = new Node(val);
        if (_head == nullptr)
        {
            // this is the first node in the list so just quickly keep track of it by making it the _tail
            _head = temp;
            _tail = temp;
            return;
        }
        temp->next = _head;
        _head = temp;
    }

    void insertAtTail(int val)
    {
        if (val == c_sentinalValue)
        {
            cout << "Can't insert value = " << val << " because it matches sentinal" << endl;
            return;
        }

        Node* temp = new Node(val);
        if (_head == nullptr)
        {
            _head = temp;
            _tail = temp;
            return;
        }
        _tail->next = temp;
        _tail = _tail->next;
    }

    Node* findValue(int val)
    {
        if (_tail == nullptr)
        {
            // we have an empty list, nothing to find
            return nullptr;
        }

        //
        // We're using the sentinal approach here. It helps to by removing one check (i.e. assembly-level branch) that we would have had
        // to do if using null approach 
        //      while(runner != nullptr)
        //      {
        //          if (runner->val == val)          <------ got rid of this check (aka branch)
        //              return runner;
        //          runner = runner->next;
        //      }
        //
        // Makes the code a bit more readable also but requires a little more setup and constant memory.
        // NOTE: Main drawback is that this approach wouldn't work if the list was shared across threads since each one would most likely require
        // a different sentinal value to be inserted. We'd have to introduce locks which would kill perf. So be CAREFUL!!
        // 
        // See NOTES section
        //

        // setup sentinal for search
        _pSentinal->val = val;
        _tail->next = _pSentinal;
        Node* runner = _head;
        while (runner->val != val)
        {
            runner = runner->next;
        }

        // restore _tail
        _tail->next = nullptr;

        if (runner == _pSentinal)
        {
            // not found!
            return nullptr;
        }
        return runner;
    }

    void deleteValue(int val)
    {
        if (_head == nullptr)
        {
            return;
        }

        // setup sentinal for search
        _pSentinal->val = val;
        _tail->next = _pSentinal;
        Node* prev = nullptr;
        Node* current = _head;
        while (current->val != val)
        {
            prev = current;
            current = current->next;
        }

        // restore _tail
        _tail->next = nullptr;

        if (current == _pSentinal)
        {
            // value wasn't found
            return;
        }

        if (prev == nullptr)
        {
            // value was found at head
            // delete head
            _head = _head->next;
            if (current == _tail)
            {
                //we're deleting the only node in the list
                _tail = _head;
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
    Node _sentinal;
    Node* const _pSentinal;
};

class DoubleLinkedList
{
    // menh!

    //
    // When/if implementing and CONCURRENCY IS NOT AN ISSUE, consider using two sentinal nodes - one called header other called trailer that are placed
    // at either end of the list. Like so:
    //NodeDouble _headerSentinal;
    //NodeDouble _trailerSentinal;
    //NodeDouble* const _header = &_headerSentinal;
    //NodeDouble* const _trailer = &_trailerSentinal;
    //
};

class DoubleCircularLinkedList
{
public:
    DoubleCircularLinkedList() :
        _pSentinal(&_sentinal)
    {
        // setup sentinal node
        _pSentinal->next = _pSentinal;
        _pSentinal->prev = _pSentinal;
    }

    NodeDouble* getHead()
    {
        return (_pSentinal->next == _pSentinal ? nullptr : _pSentinal->next);
    }

    NodeDouble* getTail()
    {
        return (_pSentinal->prev == _pSentinal ? nullptr : _pSentinal->prev);
    }

    void create(vector<int>& input)
    {
        if (_pSentinal->next != _pSentinal)
        {
            cout << "Can't override existing list!" << endl;
            return;
        }
        if (input.size() == 0)
        {
            return;
        }

        NodeDouble* temp = new NodeDouble(input[0]);
        _pSentinal->next = temp;
        _pSentinal->prev = temp;
        temp->next = _pSentinal;
        temp->prev = _pSentinal;
        for (int i = 1; i < input.size(); i++)
        {
            temp = new NodeDouble(input[i]);
            temp->prev = _pSentinal->prev;
            temp->next = _pSentinal;
            _pSentinal->prev->next = temp;
            _pSentinal->prev = temp;
        }
    }

    void print()
    {
        cout << "  ";
        if (_pSentinal->next == _pSentinal)
        {
            cout << "EMTPY";
            cout << endl;
            return;
        }

        NodeDouble* runner = _pSentinal->next;
        while (runner != _pSentinal)
        {
            cout << runner->val << " ";
            runner = runner->next;
        }
        cout << endl;
    }

    void printReverse()
    {
        cout << "  ";
        if (_pSentinal->prev == _pSentinal)
        {
            cout << "EMTPY";
            cout << endl;
            return;
        }

        NodeDouble* runner = _pSentinal->prev;
        while (runner != _pSentinal)
        {
            cout << runner->val << " ";
            runner = runner->prev;
        }
        cout << endl;
    }

    NodeDouble* findValue(int val)
    {
        if (_pSentinal->next == _pSentinal)
        {
            // empty list
            return nullptr;
        }

        int tempVal = _pSentinal->val;
        _pSentinal->val = val;

        NodeDouble* runner = _pSentinal->next;
        while (runner->val != val)
        {
            runner = runner->next;
        }

        _pSentinal->val = tempVal;

        if (runner == _pSentinal)
        {
            return nullptr;
        }
        return runner;
    }

    void insertAtHead(int val)
    {
        if (val == c_sentinalValue)
        {
            cout << "Can't insert value = " << val << " because it matches sentinal" << endl;
            return;
        }
        // Do NOT attempt to do this in your head!! Use whiteboard/paper!
        // Fixup temp first then sentinal->next->prev (i.e. actual head) then finally sentinal head pointer
        NodeDouble* temp = new NodeDouble(val);
        temp->next = _pSentinal->next;
        temp->prev = _pSentinal;
        _pSentinal->next->prev = temp;
        _pSentinal->next = temp;
    }

    void insertAtTail(int val)
    {
        if (val == c_sentinalValue)
        {
            cout << "Can't insert value = " << val << " because it matches sentinal" << endl;
            return;
        }

        // Do NOT attempt to do this in your head!! Use whiteboard/paper!
        // Fixup temp first then sentinal->prev->next (i.e. actual tail) then finally sentinal tail pointer
        NodeDouble* temp = new NodeDouble(val);
        temp->next = _pSentinal;
        temp->prev = _pSentinal->prev;
        _pSentinal->prev->next = temp;
        _pSentinal->prev = temp;
    }

    void deleteValue(int val)
    {
        if (_pSentinal->next == _pSentinal)
        {
            // empty list;
            return;
        }

        int tempVal = _pSentinal->val;
        _pSentinal->val = val;
        NodeDouble* runner = _pSentinal->next;
        while (runner->val != val)
        {
            runner = runner->next;
        }
        _pSentinal->val = tempVal;

        if (runner == _pSentinal)
        {
            // Not found
            return;
        }

        runner->next->prev = runner->prev;
        runner->prev->next = runner->next;
        delete runner;
    }

private:
    NodeDouble _sentinal;
    NodeDouble* const _pSentinal;
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

void testDoubleCircularLLFind()
{
    vector<int> input0{};
    vector<int> input1{ 1 };
    vector<int> input4{ 1,2,3,4, };

    NodeDouble* empty = nullptr;
    NodeDouble* one = nullptr;
    NodeDouble* four = nullptr;
    DoubleCircularLinkedList* dcll = nullptr;
    NodeDouble* temp = nullptr;

    DoubleCircularLinkedList dcll0;
    DoubleCircularLinkedList dcll1;
    DoubleCircularLinkedList dcll4;
    dcll0.create(input0);
    dcll1.create(input1);
    dcll4.create(input4);

    dcll = &dcll0;
    temp = dcll->getHead();
    assert(temp == nullptr);
    temp = dcll->getTail();
    assert(temp == nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);

    dcll = &dcll1;
    temp = dcll->getHead();
    assert(temp != nullptr);
    assert(temp->val == 1);
    temp = dcll->getTail();
    assert(temp != nullptr);
    assert(temp->val == 1);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);

    dcll = &dcll4;
    temp = dcll->getHead();
    assert(temp != nullptr);
    assert(temp->val == 1);
    temp = dcll->getTail();
    assert(temp != nullptr);
    assert(temp->val == 4);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) != nullptr);
    assert(dcll->findValue(3) != nullptr);
    assert(dcll->findValue(4) != nullptr);
    assert(dcll->findValue(5) == nullptr);
}

void testDoubleCircularLLInsertHead()
{
    vector<int> input0{};
    vector<int> input1{ 1 };
    vector<int> input4{ 1,2,3,4, };

    int val = -1;
    NodeDouble* empty = nullptr;
    NodeDouble* one = nullptr;
    NodeDouble* four = nullptr;
    DoubleCircularLinkedList* dcll = nullptr;

    DoubleCircularLinkedList dcll0;
    DoubleCircularLinkedList dcll1;
    DoubleCircularLinkedList dcll4;
    dcll0.create(input0);
    dcll1.create(input1);
    dcll4.create(input4);

    //sll0.print();
    //sll1.print();
    //sll4.print();

    val = 10;
    dcll0.insertAtHead(val);
    dcll1.insertAtHead(val);
    dcll4.insertAtHead(val);

    dcll = &dcll0;
    assert(dcll->getHead()->val == val);
    assert(dcll->getTail()->val == val);
    assert(dcll->findValue(val) != nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);

    dcll = &dcll1;
    assert(dcll->getHead()->val == val);
    assert(dcll->getTail()->val == 1);
    assert(dcll->findValue(val) != nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);

    dcll = &dcll4;
    assert(dcll->getHead()->val == val);
    assert(dcll->getTail()->val == 4);
    assert(dcll->findValue(val) != nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) != nullptr);
    assert(dcll->findValue(3) != nullptr);
    assert(dcll->findValue(4) != nullptr);
    assert(dcll->findValue(5) == nullptr);
}

void testDoubleCircularLLInsertTail()
{
    vector<int> input0{};
    vector<int> input1{ 1 };
    vector<int> input4{ 1,2,3,4, };

    int val = -1;
    NodeDouble* empty = nullptr;
    NodeDouble* one = nullptr;
    NodeDouble* four = nullptr;
    DoubleCircularLinkedList* dcll = nullptr;

    DoubleCircularLinkedList dcll0;
    DoubleCircularLinkedList dcll1;
    DoubleCircularLinkedList dcll4;
    dcll0.create(input0);
    dcll1.create(input1);
    dcll4.create(input4);

    //dcll0.print();
    //dcll1.print();
    //dcll4.print();
    val = 10;
    dcll0.insertAtTail(val);
    dcll1.insertAtTail(val);
    dcll4.insertAtTail(val);

    dcll = &dcll0;
    assert(dcll->getHead()->val == val);
    assert(dcll->getTail()->val == val);
    assert(dcll->findValue(val) != nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);

    dcll = &dcll1;
    assert(dcll->getHead()->val == 1);
    assert(dcll->getTail()->val == val);
    assert(dcll->findValue(val) != nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);

    dcll = &dcll4;
    assert(dcll->getHead()->val == 1);
    assert(dcll->getTail()->val == val);
    assert(dcll->findValue(val) != nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) != nullptr);
    assert(dcll->findValue(3) != nullptr);
    assert(dcll->findValue(4) != nullptr);
    assert(dcll->findValue(5) == nullptr);
}

void testDoubleCircularLLDelete()
{
    vector<int> input0{};
    vector<int> input1{ 1 };
    vector<int> input4{ 1,2,3,4, };

    int val = -1;
    NodeDouble* empty = nullptr;
    NodeDouble* one = nullptr;
    NodeDouble* four = nullptr;
    DoubleCircularLinkedList* dcll = nullptr;

    DoubleCircularLinkedList dcll0;
    DoubleCircularLinkedList dcll1;
    DoubleCircularLinkedList dcll4;
    dcll0.create(input0);
    dcll1.create(input1);
    dcll4.create(input4);

    //dcll0.print();
    //dcll1.print();
    //dcll4.print();

    val = 10;
    dcll0.deleteValue(val);
    dcll1.deleteValue(val);
    dcll4.deleteValue(val);

    dcll = &dcll0;
    assert(dcll->getHead() == nullptr);
    assert(dcll->getTail() == nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll = &dcll1;
    assert(dcll->getHead()->val == 1);
    assert(dcll->getTail()->val == 1);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll = &dcll4;
    assert(dcll->getHead()->val == 1);
    assert(dcll->getTail()->val == 4);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) != nullptr);
    assert(dcll->findValue(3) != nullptr);
    assert(dcll->findValue(4) != nullptr);
    assert(dcll->findValue(5) == nullptr);

    val = 5;
    dcll0.deleteValue(val);
    dcll1.deleteValue(val);
    dcll4.deleteValue(val);
    dcll = &dcll0;
    assert(dcll->getHead() == nullptr);
    assert(dcll->getTail() == nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll = &dcll1;
    assert(dcll->getHead()->val == 1);
    assert(dcll->getTail()->val == 1);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll = &dcll4;
    assert(dcll->getHead()->val == 1);
    assert(dcll->getTail()->val == 4);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) != nullptr);
    assert(dcll->findValue(3) != nullptr);
    assert(dcll->findValue(4) != nullptr);
    assert(dcll->findValue(5) == nullptr);

    val = 4;
    dcll0.deleteValue(val);
    dcll1.deleteValue(val);
    dcll4.deleteValue(val);
    dcll = &dcll0;
    assert(dcll->getHead() == nullptr);
    assert(dcll->getTail() == nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll = &dcll1;
    assert(dcll->getHead()->val == 1);
    assert(dcll->getTail()->val == 1);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll = &dcll4;
    assert(dcll->getHead()->val == 1);
    assert(dcll->getTail()->val == 3);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) != nullptr);
    assert(dcll->findValue(2) != nullptr);
    assert(dcll->findValue(3) != nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);

    val = 1;
    dcll0.deleteValue(val);
    dcll1.deleteValue(val);
    dcll4.deleteValue(val);
    dcll = &dcll0;
    assert(dcll->getHead() == nullptr);
    assert(dcll->getTail() == nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll = &dcll1;
    assert(dcll->getHead() == nullptr);
    assert(dcll->getTail() == nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll = &dcll4;
    assert(dcll->getHead()->val == 2);
    assert(dcll->getTail()->val == 3);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) != nullptr);
    assert(dcll->findValue(3) != nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll4.deleteValue(2);
    assert(dcll->getHead()->val == 3);
    assert(dcll->getTail()->val == 3);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) != nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
    dcll4.deleteValue(3);
    assert(dcll->getHead() == nullptr);
    assert(dcll->getTail() == nullptr);
    assert(dcll->findValue(-1) == nullptr);
    assert(dcll->findValue(0) == nullptr);
    assert(dcll->findValue(1) == nullptr);
    assert(dcll->findValue(2) == nullptr);
    assert(dcll->findValue(3) == nullptr);
    assert(dcll->findValue(4) == nullptr);
    assert(dcll->findValue(5) == nullptr);
}


int main()
{
    testSingleLLFind();
    testSingleLLInsertHead();
    testSingleLLInsertTail();
    testSingleLLDelete();

    testDoubleCircularLLFind();
    testDoubleCircularLLInsertHead();
    testDoubleCircularLLInsertTail();
    testDoubleCircularLLDelete();

    return 0;
}

//
// NOTES Section:
//
// Sentinal Nodes:
// https://en.wikipedia.org/wiki/Sentinel_node
// Sentinels are used as an alternative over using null as the path terminator in order to get one or more of the following benefits :
//    Increased speed of operations
//    Reduced algorithmic complexity and code size
//    Increased data structure robustness(arguably)
// However, sentinel nodes rely on shared memory, which requires extra code to avoid data races.This causes sentinel nodes to have poor performance on concurrent systems.
// Sentinal nodes also allow null to be inserted into the list since it's no longer the list terminator.
//
