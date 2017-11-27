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
            assert(input[i] != -1); // we use -1 to indicate failure!
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

    Node* findValue(Node* head, int val)
    {
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
    NodeDouble* findValue(NodeDouble* head, int val)
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

void testFindSingleLinkedList(SingleLinkedListOperations& sllo, vector<Node*>& headList, int val)
{
    vector<vector<bool>> toFind(headList.size(), vector<bool>(val + 2, false));
    for (int i = 0; i < toFind.size(); i++)
    {
        for (int j = 0; j < toFind[i].size(); j++)
        {
            Node* temp = sllo.findValue(headList[i], j);
            if (temp == nullptr)
            {
                toFind[i][j] = false;
            }
            else
            {
                toFind[i][j] = true;
            }
        }
    }
    for (int i = 0; i < toFind.size(); i++)
    {
        cout << "FindValue for List[" << i << "]:" << endl;
        for (int j = 0; j < toFind[i].size(); j++)
        {
            cout << "  ";
            cout << "toFind[" << i << "][" << j << "]=" << toFind[i][j] << endl;
        }
    }
}

void testSingleLinkedListOperations(vector<int>& input)
{
    cout << "TEST SINGLE LL OPERATIONS" << endl;

    SingleLinkedListOperations sllo;
    Node* headEmpty = nullptr;
    Node* headOne = nullptr;
    Node* headInput = nullptr;
    const int headOneValue = input.back() + 1;
    int val = headOneValue + 1;
    vector<Node*> headList;

    cout << "Create Single LLs (set 1):" << endl;
    Node* headEmpty1 = sllo.create(vector<int>());
    Node* headOne1 = sllo.create(vector<int>{headOneValue});
    Node* headInput1 = sllo.create(input);
    headEmpty = headEmpty1;
    headOne = headOne1;
    headInput = headInput1;
    cout << "Print Single LLs (set 1):" << endl;
    sllo.print(headEmpty);
    sllo.print(headOne);
    sllo.print(headInput);
    val++;
    cout << "Insert to Head of Single LLs (set 1):" << endl;
    cout << "Value = " << val << endl;
    sllo.insertAtHead(headEmpty, val);
    sllo.insertAtHead(headOne, val);
    sllo.insertAtHead(headInput, val);
    cout << "Print Single LLs (set 1):" << endl;
    sllo.print(headEmpty);
    sllo.print(headOne);
    sllo.print(headInput);

    val++;
    cout << "Create Single LLs (set 2):" << endl;
    Node* headEmpty2 = sllo.create(vector<int>());
    Node* headOne2 = sllo.create(vector<int>{headOneValue});
    Node* headInput2 = sllo.create(input);
    headEmpty = headEmpty;
    headOne = headOne;
    headInput = headInput;
    cout << "Insert to Tail of Single LLs (set 2):" << endl;
    cout << "Value = " << val << endl;
    sllo.insertAtTail(headEmpty, val);
    sllo.insertAtTail(headOne, val);
    sllo.insertAtTail(headInput, val);
    cout << "Print Single LLs (set 2):" << endl;
    sllo.print(headEmpty);
    sllo.print(headOne);
    sllo.print(headInput);

    val++;
    cout << "Create Single LLs (set 3):" << endl;
    Node* headEmpty3 = sllo.create(vector<int>());
    Node* headOne3 = sllo.create(vector<int>{headOneValue});
    Node* headInput3 = sllo.create(input);
    headEmpty = headEmpty3;
    headOne = headOne3;
    headInput = headInput3;
    cout << "Insert to Tail of Single LLs (set 3):" << endl;
    cout << "Value = " << val << endl;
    sllo.insertAtTail(headEmpty, val);
    sllo.insertAtTail(headOne, val);
    sllo.insertAtTail(headInput, val);
    val++;
    cout << "Insert to Head of Single LLs (set 3):" << endl;
    cout << "Value = " << val << endl;
    sllo.insertAtHead(headEmpty, val);
    sllo.insertAtHead(headOne, val);
    sllo.insertAtHead(headInput, val);
    cout << "Print Single LLs:" << endl;
    sllo.print(headEmpty);
    sllo.print(headOne);
    sllo.print(headInput);

    val++;
    cout << "Create Single LLs (set 4):" << endl;
    Node* headEmpty4 = sllo.create(vector<int>());
    Node* headOne4 = sllo.create(vector<int>{headOneValue});
    Node* headInput4 = sllo.create(input);
    headEmpty = headEmpty4;
    headOne = headOne4;
    headInput = headInput4;
    cout << "TEST FIND" << endl;
    headList.clear();
    headList.push_back(headEmpty);
    headList.push_back(headOne);
    headList.push_back(headInput);
    testFindSingleLinkedList(sllo, headList, val);
    cout << "Insert to Tail of Single LLs (set 4):" << endl;
    cout << "Value = " << val << endl;
    sllo.insertAtTail(headEmpty, val);
    sllo.insertAtTail(headOne, val);
    sllo.insertAtTail(headInput, val);
    cout << "TEST FIND" << endl;
    headList.clear();
    headList.push_back(headEmpty);
    headList.push_back(headOne);
    headList.push_back(headInput);
    testFindSingleLinkedList(sllo, headList, val);
    val++;
    cout << "Insert to Head of Single LLs (set 4):" << endl;
    cout << "Value = " << val << endl;
    sllo.insertAtHead(headEmpty, val);
    sllo.insertAtHead(headOne, val);
    sllo.insertAtHead(headInput, val);
    cout << "Print Single LLs:" << endl;
    sllo.print(headEmpty);
    sllo.print(headOne);
    sllo.print(headInput);
    cout << "TEST FIND" << endl;
    headList.clear();
    headList.push_back(headEmpty);
    headList.push_back(headOne);
    headList.push_back(headInput);
    testFindSingleLinkedList(sllo, headList, val);
}

int main()
{
    vector<int> input{1,2,3,4,};
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

