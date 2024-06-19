#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

typedef struct node
{
    int data;
    struct node* next;
}ST_node_t;

class AbstractSingleLinkedList {
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

class SingleLinkedList :AbstractSingleLinkedList {
private:
    ST_node_t* Head;
    int Size;
public:
    // Constructor
    SingleLinkedList(ST_node_t* head, int size) {
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
            Head = newNode;
        }
        else
        {
            for (int i = 0; i < Size - 1; i++)
            {
                ptr = ptr->next;
            }
            newNode->next = ptr->next;
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
                newNode->next = Head;
                Head = newNode;
            }
            else
            {
                for (int i = 0; i < index - 1; i++)
                {
                    ptr = ptr->next;
                }
                newNode->next = ptr->next;
                ptr->next = newNode;
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
            for (int i = 0; i < index ; i++)
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
        if (Size == 0)
            return true;
        else
            return false;
    }

    void remove(int index) {
        if (index < Size)
        {
            ST_node_t* ptr = Head;
            ST_node_t* temp = ptr;
            if (index == 0)
            {
                Head = ptr->next;
                ptr->next = NULL;
                free(ptr);
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
                temp->next = NULL;
                free(temp);
            }
            Size--;
        }
        else {
            printf("Error");
        }
    }

    int size() {
        return Size;
    }

    SingleLinkedList sublist(int fromIndex, int toIndex)
    {
        SingleLinkedList sub = SingleLinkedList(0, NULL);
        if (fromIndex >= 0 && toIndex < Size)
        {
            ST_node_t* ptrSub;
            ST_node_t* ptr = Head;
            for (int i = 0; i < fromIndex; i++)
            {
                ptr = ptr->next;
            }
            sub.setHead(ptr);
            ptrSub = ptr;
            for (int j = fromIndex; j < toIndex; j++)
            {
                sub.Add(ptrSub->data);
                ptrSub = ptrSub->next;
            }
            sub.Add(ptrSub->data);
            ptrSub->next = NULL;

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
            if (i < Size - 1)
            {
                printf("%d, ", nxt->data);
                nxt = nxt->next;
            }
            else
            {
                printf("%d", nxt->data);
            }
        }
        printf("]");
    }
};

int main()
{
    // Input List from the user 
    stringstream line;
    vector <int> array;
    string input;
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

    SingleLinkedList list = SingleLinkedList(NULL, 0);

    for (int i = 0; i < int(array.size()); i++)
    {
        list.Add(array[i]);
    }
    string instruction;
    getline(cin, instruction);

    if (instruction == "add") {
        int x;
        cin >> x;
        list.Add(x);
        list.printList();
    }
    else if (instruction == "addToIndex") {
        int index, data;
        cin >> index;
        cin >> data;
        if (index < list.getSize() && index >= 0)
        {
            list.addToIndex(index, data);
            list.printList();
        }
        else
        {
            cout << "Error" << endl;
        }
    }
    else if (instruction == "get") {
        int index;
        cin >> index;
        if (index < list.getSize() && index >= 0)
        {
            cout << list.get(index) << endl;
        }
        else
        {
            cout << "Error" << endl;
        }
    }
    else if (instruction == "set") {
        int index, data;
        cin >> index;
        cin >> data;
        if (index < list.getSize() && index >= 0)
        {
            list.set(index, data);
            list.printList();
        }
        else
        {
            cout << "Error" << endl;
        }
    }
    else if (instruction == "clear") {
        list.clear();
        list.printList();
    }
    else if (instruction == "isEmpty") {
        if (list.isEmpty() == true)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    else if (instruction == "remove") {
        int index;
        cin >> index;
        if (index < list.getSize() && index >= 0)
        {
            list.remove(index);
            list.printList();
        }
        else
        {
            cout << "Error" << endl;
        }
    }
    else if (instruction == "sublist") {
        int fromIndex, toIndex;
        cin >> fromIndex;
        cin >> toIndex;
        if (fromIndex >= 0 && toIndex < list.getSize() && toIndex >= 0 && toIndex >= fromIndex)
        {
            SingleLinkedList sub = list.sublist(fromIndex, toIndex);
            sub.printList();
        }
        else
        {
            cout << "Error" << endl;
        }
    }
    else if (instruction == "size")
    {
        cout << list.size() << endl;
    }
    else if (instruction == "contains")
    {
        int data;
        cin >> data;
        if (list.contain(data) == true)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
    return 0;
}
