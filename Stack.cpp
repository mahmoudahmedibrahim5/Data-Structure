#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

typedef struct node
{
    int data;
    struct node* next;
    struct node* previous;
}ST_node_t;

class AbstractDoubleLinkedList {
    virtual void Add(int data) = 0;
    virtual void addToIndex(int index, int data) = 0;
    virtual int get(int index) = 0;
    virtual void set(int index, int data) = 0;
    virtual void clear() = 0;
    virtual bool isEmpty() = 0;
    virtual void remove(int index) = 0;
    virtual int size() = 0;
    virtual bool contain(int data) = 0;
    virtual void printList(void) = 0;
};

class DoubleLinkedList :AbstractDoubleLinkedList {
protected:
    ST_node_t* Head;
    int Size;
public:
    // Constructor
    DoubleLinkedList(ST_node_t* head, int size) {
        Head = head;
        Size = size;
    }

    // Setters and Getters
    void setHead(ST_node_t* head) {
        Head = head;
    }
    ST_node_t* getHead(void) {
        return Head;
    }
    void setSize(int size) {
        Size = size;
    }
    int getSize(void) {
        return Size;
    }

    // Methods
    void Add(int data)
    {
        ST_node_t* newNode = (ST_node_t*)malloc(sizeof(ST_node_t));
        newNode->data = data;
        ST_node_t* ptr = Head;
        if (Size == 0)
        {
            newNode->next = Head;
            newNode->previous = NULL;
            Head = newNode;
        }
        else
        {
            for (int i = 0; i < Size - 1; i++)
            {
                ptr = ptr->next;
            }
            newNode->next = NULL;
            newNode->previous = ptr->next;
            ptr->next = newNode;
        }
        Size++;
    }

    void addToIndex(int index, int data) {
        if (index <= Size)
        {
            ST_node_t* newNode = (ST_node_t*)malloc(sizeof(ST_node_t));
            newNode->data = data;
            ST_node_t* ptr = Head;
            if (index == 0)
            {
                ptr->previous = newNode;
                newNode->next = Head;
                newNode->previous = NULL;
                Head = newNode;
            }
            else
            {
                for (int i = 0; i < index - 1; i++)
                {
                    ptr = ptr->next;
                }
                newNode->next = ptr->next;
                newNode->previous = ptr;
                ptr->next = newNode;
                ptr->next->previous = newNode;
            }
            Size++;
        }
    }

    int get(int index) {
        if (index < Size)
        {
            ST_node_t* ptr = Head;
            for (int i = 0; i < index; i++)
            {
                ptr = ptr->next;
            }
            return ptr->data;
        }
        return 0;
    }

    void set(int index, int data) {
        if (index < Size)
        {
            ST_node_t* next = Head;
            for (int i = 0; i < index; i++)
            {
                next = next->next;
            }
            next->data = data;
        }
    }

    void clear() {
        ST_node_t* ptr = Head;
        Head = NULL;
        Size = 0;
        ST_node_t* clr = ptr;
        for (int i = 0; i < Size; i++)
        {
            free(clr);
            ptr = ptr->next;
            clr = ptr;
        }
        free(clr);
    }

    bool isEmpty() {
        return (Size == 0);
    }

    void remove(int index) {
        if (index < Size)
        {
            ST_node_t* ptr = Head;
            ST_node_t* temp = ptr;
            if (Size == 1)
            {
                Head = NULL;
                free(ptr);
            }
            else if (index == 0)
            {
                Head = ptr->next;
                ptr->next->previous = NULL;
                ptr->next = NULL;
                ptr->previous = NULL;
                free(ptr);
            }
            else if (index == Size - 1)
            {
                for (int i = 0; i < index - 1; i++)
                {
                    ptr = ptr->next;
                    temp = ptr;
                }
                temp = temp->next;
                ptr->next = NULL;
                free(temp);
            }
            else
            {
                for (int i = 0; i < index - 1; i++)
                {
                    ptr = ptr->next;
                    temp = ptr;
                }
                temp = temp->next;
                ptr->next = temp->next;
                temp->next->previous = ptr;
                temp->next = NULL;
                temp->previous = NULL;
                free(temp);
            }
            Size--;
        }
    }

    int size() {
        return Size;
    }

    DoubleLinkedList sublist(int fromIndex, int toIndex)
    {
        DoubleLinkedList sub = DoubleLinkedList(0, NULL);
        if (fromIndex >= 0 && toIndex < Size)
        {
            ST_node_t* ptr = Head;
            for (int i = 0; i < fromIndex; i++)
            {
                ptr = ptr->next;
            }
            sub.setHead(ptr);
            ptr->previous = NULL;
            for (int j = fromIndex; j < toIndex; j++)
            {
                sub.Add(ptr->data);
                ptr = ptr->next;
            }
            sub.Add(ptr->data);
            ptr->next = NULL;
        }
        return sub;
    }

    bool contain(int data) {
        if (Size != 0)
        {
            ST_node_t* ptr = Head;
            for (int i = 0; i < Size; i++)
            {
                if (ptr->data == data)
                    return true;
                ptr = ptr->next;
            }
        }
        return false;
    }

    void printList(void)
    {
        printf("[");
        ST_node_t* nxt = Head;
        for (int i = 0; i < Size; i++)
        {
             printf("%d%c ", nxt->data, (i==Size-1)?']':',');
             nxt = nxt->next;
        }
        if(Size == 0)
            printf("]");
    }
};

class Stack : public DoubleLinkedList {
    ST_node_t* stackPtr;
public:
    Stack(ST_node_t* head, int size):DoubleLinkedList(head, size){
        stackPtr = head;
    }

    // Methods
    void push(int data)
    {
        ST_node_t* newNode = (ST_node_t*)malloc(sizeof(ST_node_t));
        newNode->data = data;
        newNode->next = NULL;
        newNode->previous = stackPtr;
        if (Size == 0) {
            Head = newNode;
        }
        else {
            stackPtr->next = newNode;
        }
        stackPtr = newNode;
        Size++;
    }
    int pop(void)
    {
        if (Size == 1)
        {
            int data = stackPtr->data;
            Head = NULL;
            stackPtr = Head;
            Size--;
            return data;
        }
        else if (Size != 0)
        {
            int data = stackPtr->data;
            stackPtr = stackPtr->previous;
            stackPtr->next->previous = NULL;
            stackPtr->next = NULL;
            Size--;
            return data;
        }
        else
            throw Size;
    }
    int peek(void)
    {
        if(Size!=0)
            return stackPtr->data;
        else
            throw Size;
    }
    void printStack(void)
    {
        printf("[");
        ST_node_t* nxt = stackPtr;
        for (int i = 0; i < Size; i++)
        {
            printf("%d%c ", nxt->data, (i == Size - 1) ? ']' : ',');
            nxt = nxt->previous;
        }
        if (Size == 0)
            printf("]");
    }
};

int main()
{
    // Input List from the user
    stringstream line;
    vector <int> array;
    string input;
    Stack s1 = Stack(NULL, 0);
    char comma;
    int vector_elements;
    getline(cin, input);
    line << input;
    while (1)
    {
        line >> comma;
        if (input[1] == ']' || comma == ']') break;
        line >> vector_elements;
        array.push_back(vector_elements);
    }
    for (int i = 0; i < array.size(); i++)
    {
        s1.push(array[array.size() - 1 - i]);
    }

    string command;
    getline(cin, command);
    if (command == "push")
    {
        int data;
        cin >> data;
        s1.push(data);
        s1.printStack();
    }
    else if (command == "pop")
    {
        try{
            s1.pop();
            s1.printStack();
        }
        catch (int num){
            printf("Error");
        }
    }
    else if (command == "peek")
    {
        if (s1.size() == 0)
            printf("Error");
        else
            printf("%d", s1.peek());
    }
    else if (command == "isEmpty")
    {
        if (s1.isEmpty())
            printf("True");
        else
            printf("False");
    }
    else if (command == "size")
    {
        printf("%d", s1.size());
    }
    else
    {
        printf("Error");
    }
    return 0;
}
