#include "LinkedList_string.h"
#include <string>
#include <stdexcept>

using namespace std;
LinkedList::LinkedList() : head(nullptr) {}

LinkedList::LinkedList(const LinkedList& other) : head(nullptr)
{
    Node* walk = other.head;
    while (walk)
    {
        push_back(walk->data);
        walk = walk->next;
    }
}

LinkedList::~LinkedList()
{
    Node* walk = head;
    while (walk != nullptr)
    {
        Node* steady = walk->next;
        delete walk;
        walk = steady;
    }
    head = nullptr;
}

string& LinkedList::at(int index)
{
    if (index < 0 || index >= size())
    {
        throw out_of_range("index out of range");
    }
    Node* walk = head;
    for (int i = 0; i < index; ++i)
        walk = walk->next;
    return walk->data;
}

string& LinkedList::front()
{
    return head->data;
}

string& LinkedList::back()
{
    if (!head)
        throw out_of_range("empty list");
    Node* walk = head;
    while (walk->next)
        walk = walk->next;
    return walk->data;
}

void LinkedList::push_back(const string& value)
{
    if (!head)
    {
        push_front(value);
        return;
    }
    Node* walk = head;
    while (walk->next)
        walk = walk->next;
    walk->next = new Node(value);
}

void LinkedList::pop_back()
{
    if (!head)
        return;
    if (!head->next)
    {
        delete head;
        head = nullptr;
        return;
    }
    Node* prev = head;
    Node* cur = head->next;
    while (cur->next)
    {
        prev = cur;
        cur = cur->next;
    }
    delete cur;
    prev->next = nullptr;
}

void LinkedList::push_front(const string& value)
{
    Node* walk = new Node(value);
    walk->next = head;
    head = walk;
}

void LinkedList::pop_front()
{
    if (head == nullptr)
        return;

    Node* walk = head;
    head = head->next;
    delete walk;
}

void LinkedList::insert_at(int index, const string& value)
{
    if (head == nullptr)
        throw out_of_range("empty list");
    else if (index < 0 || index > this->size())
        throw out_of_range("index is out of range");
    else if (index == this->size())
    {
        this->push_back(value);
        return;
    }
    else if (index == 0)
    {
        this->push_front(value);
        return;
    }
    Node* walk = head;
    int i = 0;
    while (walk->next != nullptr && i < index - 1)
    {
        walk = walk->next;
        i++;
    }
    Node* steady = new Node(value);
    steady->next = walk->next;
    walk->next = steady;
}

void LinkedList::insert_after(int index, const string& val)
{
    if (index < 0 || index >= this->size())
        throw out_of_range("index out of range");
    this->insert_at(index + 1, val);
}

void LinkedList::erase_at(int index)
{
    if (index < 0 || index >= this->size())
        throw out_of_range("index out of range");
    else if (head == nullptr)
        throw out_of_range("empty list");
    else if (index == 0)
    {
        this->pop_front();
        return;
    }
    Node* walk = head;
    Node* steady;
    for (int i = 0; i < index - 1; ++i)
    {
        walk = walk->next;
    }
    steady = walk;
    walk = walk->next;
    steady->next = walk->next;
    delete walk;
}

void LinkedList::erase(const string& e)
{
    if (!head)
        throw out_of_range("empty list");
    if (head->data == e)
    {
        pop_front();
        return;
    }
    Node* prev = head;
    Node* cur = head->next;
    while (cur)
    {
        if (cur->data == e)
        {
            prev->next = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void LinkedList::clear()
{
    Node* walk = head;
    while (walk != nullptr)
    {
        Node* steady = walk->next;
        delete walk;
        walk = steady;
    }
    head = nullptr;
}

int LinkedList::size() const
{
    if (head == nullptr)
        return 0;
    int size = 0;
    Node* walk = head;
    while (walk != nullptr)
    {
        walk = walk->next;
        size++;
    }
    return size;
}

bool LinkedList::empty() const
{
    return head == nullptr;
}

Node& LinkedList::findMiddleNode()
{
    if (!head)
        throw out_of_range("empty list");

    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return *slow;
}

Node& LinkedList::getSmallestNode()
{
    if (!head)
        throw out_of_range("empty list");

    Node* smallest = head;
    Node* cur = head->next;

    while (cur)
    {
        if (cur->data < smallest->data)
            smallest = cur;
        cur = cur->next;
    }

    return *smallest;
}

void LinkedList::moveSmallestToFront()
{
    if (!head || !head->next)
        return;

    Node* prevSmallest = nullptr;
    Node* smallest = head;

    Node* prev = head;
    Node* cur = head->next;

    while (cur)
    {
        if (cur->data < smallest->data)
        {
            smallest = cur;
            prevSmallest = prev;
        }
        prev = cur;
        cur = cur->next;
    }

    if (!prevSmallest)
        return;

    prevSmallest->next = smallest->next;

    smallest->next = head;
    head = smallest;
}

LinkedList& LinkedList::operator=(const LinkedList& lhs)
{
    if (this == &lhs)
        return *this;
    clear();
    Node* walk = lhs.head;
    while (walk)
    {
        push_back(walk->data);
        walk = walk->next;
    }
    return *this;
}

bool LinkedList::operator==(const LinkedList& lhs) const
{
    Node* a = head;
    Node* b = lhs.head;
    while (a && b)
    {
        if (a->data != b->data)
            return false;
        a = a->next;
        b = b->next;
    }
    return a == nullptr && b == nullptr;
}

ostream& operator<<(ostream& out, const LinkedList& list)
{
    Node* walk = list.head;
    while (walk)
    {
        out << walk->data;
        if (walk->next)
            out << "->";
        walk = walk->next;
    }
    return out;
}

void printMenu()
{
    cout << "\nMenu:\n1. Add an element\n2. Remove an element by value\n3. Access an element at index\n4. Insert an element at index\n5. Insert an element after index\n6. Remove an element at index\n7. Print the linked list\n8. Print the size of the linked list\n9. Check if the linked list is empty\n10. Clear the linked list\n11. Print the middle node\n12. Print the smallest node\n13. Move smallest node to front\nx. Exit" << endl;
    cout << "Make your choice: ";
}

int main()
{
    LinkedList ll;
    string choice;

    cout << "Welcome to the Linked List Program!" << endl;
    cout << endl;
    while (choice != "x")
    {
        printMenu();
        cin >> choice;
        if (choice == "1")
        {
            string val;
            cout << "Enter a value: ";
            getline(cin >> ws, val);
            ll.push_back(val);
            cout << "Value added successfully!" << endl;
        }
        else if (choice == "2")
        {
            string val;
            cout << "Enter the value you want to remove: ";
            getline(cin >> ws, val);
            try
            {
                ll.erase(val);
                cout << "Successfully removed the value." << endl;
            }
            catch (const out_of_range& ex)
            {
                cout << "Error: " << ex.what() << endl;
            }
        }
        else if (choice == "3")
        {
            int idx;
            cout << "Enter index: ";
            cin >> idx;
            try
            {
                string& value = ll.at(idx);
                cout << "Index " << idx << " has: " << value << "." << endl;
            }
            catch (const out_of_range& ex)
            {
                cout << "Error: " << ex.what() << endl;
            }
        }
        else if (choice == "4")
        {
            int idx;
            cout << "Enter index: ";
            cin >> idx;
            string val;
            cout << "Enter value you want to insert at index " << idx << ": ";
            getline(cin >> ws, val);
            try
            {
                ll.insert_at(idx, val);
                cout << "Successfully added value!" << endl;
            }
            catch (const out_of_range& ex)
            {
                cout << "Error: " << ex.what() << endl;
            }
        }
        else if (choice == "5")
        {
            int idx;
            cout << "Enter index: ";
            cin >> idx;
            string val;
            cout << "Enter value you want to insert after index " << idx << ": ";
            getline(cin >> ws, val);
            try
            {
                ll.insert_after(idx, val);
                cout << "Successfully added value!" << endl;
            }
            catch (const out_of_range& ex)
            {
                cout << "Error: " << ex.what() << endl;
            }
        }
        else if (choice == "6")
        {
            int idx;
            cout << "Enter index to remove: ";
            cin >> idx;
            try
            {
                ll.erase_at(idx);
                cout << "Successfully removed the value at index " << idx << "." << endl;
            }
            catch (const out_of_range& ex)
            {
                cout << "Error: " << ex.what() << endl;
            }
        }
        else if (choice == "7")
        {
            cout << ll << endl;
        }
        else if (choice == "8")
        {
            cout << "Size of linked list is: " << ll.size() << endl;
        }
        else if (choice == "9")
        {
            cout << "Linked list is " << (ll.empty() ? "empty" : "not empty") << endl;
        }
        else if (choice == "10")
        {
            ll.clear();
            cout << "Linked list is now empty!" << endl;
        }
        else if (choice == "11")
        {
            try
            {
                string value = ll.findMiddleNode().data;
                cout << "Middle node is: " << value << endl;
            }
            catch (const out_of_range& ex)
            {
                cout << "Error: " << ex.what() << endl;
            }
        }
        else if (choice == "12")
        {
            try
            {
                string value = ll.getSmallestNode().data;
                cout << "Smallest node is: " << value << endl;
            }
            catch (const out_of_range& ex)
            {
                cout << "Error: " << ex.what() << endl;
            }
        }
        else if (choice == "13")
        {
            ll.moveSmallestToFront();
            cout << "Successfully moved the smallest node to front!" << endl;
        }
    }
    cout << "Thank you for using our program! Now exiting..." << endl;

    return 0;
}