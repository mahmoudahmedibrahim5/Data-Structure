#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>

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
    virtual void printPolynomial(void) = 0;
};

class DoubleLinkedList :AbstractDoubleLinkedList {
private:
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
            if (Size == 0)
            {
                newNode->next = NULL;
                newNode->previous = NULL;
                Head = newNode;
            }
            else if (index == 0)
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
        DoubleLinkedList sub = DoubleLinkedList(NULL, 0);
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

    void printPolynomial(void) {
        ST_node_t* nxt = Head;
        int cntr = 0;
        int cntr2 = 0;
        for (int i = 0; i < Size; i++)
        {
            if (i < Size - 1)
            {
                if (nxt->data != 0)
                {
                    if (cntr2 == 0)
                    {
                        if (nxt->data == 1 && Size - i - 1 == 1)
                        {
                            printf("x");
                            cntr++;
                        }
                        else if (nxt->data == 1)
                        {
                            printf("x^%d", Size - i - 1);
                            cntr++;
                        }
                        else if (Size - i - 1 == 1)
                        {
                            printf("%dx", nxt->data);
                        }
                        else
                        {
                            printf("%dx^%d", nxt->data, Size - i - 1);
                            cntr++;
                        }
                        cntr2++;
                    }
                    else if (nxt->data == 1 && Size - i - 1 == 1)
                    {
                        printf("+x");
                        cntr++;
                    }
                    else if (Size - i - 1 == 1)
                    {
                        if (nxt->data < 0)
                        {
                            printf("%dx", nxt->data);
                            cntr++;
                        }
                        else
                        {
                            printf("+%dx", nxt->data);
                            cntr++;
                        }
                    }
                    else if (nxt->data == 1)
                    {
                        printf("+x^%d", Size - i - 1);
                        cntr++;
                    }
                    else
                    {
                        if (nxt->data < 0)
                        {
                            printf("%dx^%d", nxt->data, Size - i - 1);
                            cntr++;
                        }
                        else
                        {
                            printf("+%dx^%d", nxt->data, Size - i - 1);
                            cntr++;
                        }
                    }
                }
                nxt = nxt->next;
            }
            else
            {
                if (nxt->data > 0)
                    printf("+%d", nxt->data);
                else if (nxt->data < 0)
                    printf("%d", nxt->data);
                else if (cntr == 0 && nxt->data == 0)
                    printf("0");
            }
        }
        return;
    }
};

DoubleLinkedList addLists(DoubleLinkedList var1, DoubleLinkedList var2);
DoubleLinkedList subLists(DoubleLinkedList var1, DoubleLinkedList var2);
float eval(DoubleLinkedList var1, float value);
DoubleLinkedList mult(DoubleLinkedList var1, DoubleLinkedList var2);

int main()
{
    DoubleLinkedList A = DoubleLinkedList(NULL, 0);
    DoubleLinkedList B = DoubleLinkedList(NULL, 0);
    DoubleLinkedList C = DoubleLinkedList(NULL, 0);
    DoubleLinkedList R = DoubleLinkedList(NULL, 0);
    string instruction;
    string var1;
    string var2;
    int printCntr = 0;
    int setCntr = 0;
    int flagA = 0;
    int flagB = 0;
    int flagC = 0;
    while (1)
    {
        getline(cin, instruction);
        if (instruction == "set")
        {
            if (setCntr == 3)
            {
                cout << "Error" << endl;
                break;
            }
            getline(cin, var1);
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
            if (array.size() == 0)
            {
                cout << "Error" << endl;
                break;
            }
            if (var1 == "A" && flagA == 0) {

                for (int i = 0; i < int(array.size()); i++)
                {
                    A.Add(array[i]);
                }
                flagA = 1;
            }
            else if (var1 == "B" && flagB == 0) {

                for (int i = 0; i < int(array.size()); i++)
                {
                    B.Add(array[i]);
                }
                flagB = 1;
            }
            else if (var1 == "C" && flagC == 0) {

                for (int i = 0; i < int(array.size()); i++)
                {
                    C.Add(array[i]);
                }
                flagC = 1;
            }
            else
            {
                cout << "Error" << endl;
            }
            setCntr++;
        }
        else if (instruction == "print")
        {
            getline(cin, var1);
            if (var1 == "A") {
                if (A.size() == 0)
                    cout << "Error" << endl;
                else
                    A.printPolynomial();
            }
            else if (var1 == "B") {
                if (B.size() == 0)
                    cout << "Error" << endl;
                else
                    B.printPolynomial();
            }
            else if (var1 == "C") {
                if (C.size() == 0)
                    cout << "Error" << endl;
                else
                    C.printPolynomial();
            }
            else  cout << "Error" << endl;
            cout << endl;
            printCntr++;
        }
        else if (instruction == "add")
        {
            getline(cin, var1);
            getline(cin, var2);
            if (var1 == "A" && var2 == "A" && flagA == 1)R = addLists(A, A);
            else if ((var1 == "A" && flagA == 1) && (var2 == "B" && flagB == 1))R = addLists(A, B);
            else if ((var1 == "A" && flagA == 1) && (var2 == "C" && flagC == 1))R = addLists(A, C);
            else if ((var1 == "B" && flagB == 1) && (var2 == "A" && flagA == 1))R = addLists(B, A);
            else if (var1 == "B" && var2 == "B" && flagB == 1)R = addLists(B, B);
            else if ((var1 == "B" && flagB == 1) && (var2 == "C" && flagC == 1))R = addLists(B, C);
            else if ((var1 == "C" && flagC == 1) && (var2 == "A" && flagA == 1))R = addLists(C, A);
            else if ((var1 == "C" && flagC == 1) && (var2 == "B" && flagB == 1))R = addLists(C, B);
            else if (var1 == "C" && var2 == "C" && flagC == 1)R = addLists(C, C);
            else  cout << "Error" << endl;
            R.printPolynomial();
            break;
        }
        else if (instruction == "sub")
        {
            getline(cin, var1);
            getline(cin, var2);
            if (var1 == "A" && var2 == "A" && flagA == 1)R = subLists(A, A);
            else if (var1 == "A" && var2 == "B" && flagA == 1 && flagB == 1)R = subLists(A, B);
            else if (var1 == "A" && var2 == "C" && flagA == 1 && flagC == 1)R = subLists(A, C);
            else if (var1 == "B" && var2 == "A" && flagA == 1 && flagB == 1)R = subLists(B, A);
            else if (var1 == "B" && var2 == "B" && flagB == 1)R = subLists(B, B);
            else if (var1 == "B" && var2 == "C" && flagC == 1 && flagB == 1)R = subLists(B, C);
            else if (var1 == "C" && var2 == "A" && flagC == 1 && flagA == 1)R = subLists(C, A);
            else if (var1 == "C" && var2 == "B" && flagC == 1 && flagB == 1)R = subLists(C, B);
            else if (var1 == "C" && var2 == "C" && flagC == 1)R = subLists(C, C);
            else  cout << "Error" << endl;
            R.printPolynomial();
            break;
        }
        else if (instruction == "eval")
        {
            cin >> var1;
            float value;
            cin >> value;
            if (var1 == "A") {
                if (A.size() == 0)
                    cout << "Error" << endl;
                else
                    cout << eval(A, value) << endl;
            }
            else if (var1 == "B") {
                if (B.size() == 0)
                    cout << "Error" << endl;
                else
                    cout << eval(B, value) << endl;
            }
            else if (var1 == "C") {
                if (C.size() == 0)
                    cout << "Error" << endl;
                else
                    cout << eval(C, value) << endl;
            }
            else  cout << "Error" << endl;
            break;
        }
        else if (instruction == "mult")
        {
            cin >> var1;
            cin >> var2;
            if (var1 == "A" && var2 == "A" && flagA == 1)R = mult(A, A);
            else if ((var1 == "A" && flagA == 1) && (var2 == "B" && flagB == 1))R = mult(A, B);
            else if ((var1 == "A" && flagA == 1) && (var2 == "C" && flagC == 1))R = mult(A, C);
            else if ((var1 == "B" && flagB == 1) && (var2 == "A" && flagA == 1))R = mult(B, A);
            else if (var1 == "B" && var2 == "B" && flagB == 1)R = mult(B, B);
            else if ((var1 == "B" && flagB == 1) && (var2 == "C" && flagC == 1))R = mult(B, C);
            else if ((var1 == "C" && flagC == 1) && (var2 == "A" && flagA == 1))R = mult(C, A);
            else if ((var1 == "C" && flagC == 1) && (var2 == "B" && flagB == 1))R = mult(C, B);
            else if (var1 == "C" && var2 == "C" && flagC == 1)R = mult(C, C);
            else { cout << "Error" << endl; }
            R.printPolynomial();
            break;
        }
        else if (instruction == "clear")
        {
            cin >> var1;
            if (var1 == "A")
            {
                if (A.size() == 0)
                    cout << "Error" << endl;
                else
                {
                    A.clear();
                    A.printList();
                }
            }
            else if (var1 == "B") {
                if (B.size() == 0)
                    cout << "Error" << endl;
                else
                {
                    B.clear();
                    B.printList();
                }
            }
            else if (var1 == "C") {
                if (C.size() == 0)
                    cout << "Error" << endl;
                else
                {
                    C.clear();
                    C.printList();
                }
            }
            else
                cout << "Error" << endl;
            break;
        }
        else
        {
            cout << "Error" << endl;
            break;
        }
        if (printCntr == 3) break;
    }
    return 0;
}

DoubleLinkedList addLists(DoubleLinkedList var1, DoubleLinkedList var2)
{
    DoubleLinkedList R = DoubleLinkedList{ NULL, 0 };
    int flag, data, i;
    int size1 = var1.size();
    int size2 = var2.size();
    int size;
    if (size1 > size2) {
        size = size1 - size2;
        flag = 0;
    }
    else {
        size = size2 - size1;
        flag = 1;
    }
    for (i = 0; i < size; i++)
    {
        if (flag == 0) {
            data = var1.get(i);
            R.Add(data);
        }
        else {
            data = var2.get(i);
            R.Add(data);
        }
    }
    if (flag == 0)
    {
        for (i = 0; i < size1 - size; i++)
        {
            data = var1.get(i + size) + var2.get(i);
            R.Add(data);
        }
    }
    else
    {
        for (i = 0; i < size2 - size; i++)
        {
            data = var1.get(i) + var2.get(i + size);
            R.Add(data);
        }
    }
    return R;
}

DoubleLinkedList subLists(DoubleLinkedList var1, DoubleLinkedList var2)
{
    DoubleLinkedList R = DoubleLinkedList{ NULL, 0 };
    int flag, data, i;
    int size1 = var1.size();
    int size2 = var2.size();
    int size;
    if (size1 > size2) {
        size = size1 - size2;
        flag = 0;
    }
    else {
        size = size2 - size1;
        flag = 1;
    }
    for (i = 0; i < size; i++)
    {
        if (flag == 0) {
            data = var1.get(i);
            R.Add(data);
        }
        else {
            data = -var2.get(i);
            R.Add(data);
        }
    }
    if (flag == 0)
    {
        for (i = 0; i < size1 - size; i++)
        {
            data = var1.get(i + size) - var2.get(i);
            R.Add(data);
        }
    }
    else
    {
        for (i = 0; i < size2 - size; i++)
        {
            data = var1.get(i) - var2.get(i + size);
            R.Add(data);
        }
    }
    return R;
}

float eval(DoubleLinkedList var1, float value)
{
    float sum = 0;
    ST_node_t* ptr = var1.getHead();
    for (int i = 0; i < var1.size(); i++)
    {
        sum += ptr->data * pow(value, var1.size() - i - 1);
        ptr = ptr->next;
    }
    return sum;
}

DoubleLinkedList mult(DoubleLinkedList var1, DoubleLinkedList var2)
{
    DoubleLinkedList R = DoubleLinkedList{ NULL, 0 };
    int result, i, j, k;
    for (i = 0; i < var1.size() + var2.size() - 1; i++)
    {
        result = 0;
        for (j = 0; j < var1.size(); j++)
        {
            for (k = 0; k < var2.size(); k++)
            {
                if (i == j + k)
                {
                    result += (var1.get(j) * var2.get(k));
                }
            }
        }
        R.Add(result);
    }
    return R;
}