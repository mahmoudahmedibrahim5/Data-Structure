#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <math.h>
using namespace std;

typedef enum validation { VALID, NOT_VALID } EN_Validation_t;

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
            printf("%d%c ", nxt->data, (i == Size - 1) ? ']' : ',');
            nxt = nxt->next;
        }
        if (Size == 0)
            printf("]");
    }
};

class Stack : public DoubleLinkedList {
    ST_node_t* stackPtr;
public:
    Stack(ST_node_t* head, int size) :DoubleLinkedList(head, size) {
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
        if (Size != 0)
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
    void printOperation(void)
    {
        ST_node_t* nxt = Head;
        for (int i = 0; i < Size; i++)
        {
            if (nxt->data == '+' || nxt->data == '-' || nxt->data == '*' || nxt->data == '/' || nxt->data == '(' || nxt->data == ')' || nxt->data == '^' || nxt->data == 'a' || nxt->data == 'b' || nxt->data == 'c')
                printf("%c", nxt->data);
            else
                printf("%d", nxt->data);
            nxt = nxt->next;
        }
        printf("\n");
    }
    Stack reverse(void)
    {
        Stack newStack = Stack(NULL, 0);
        int size = Size;
        ST_node_t* nxt = stackPtr;
        for (int i = 0; i < size; i++)
        {
            newStack.push(nxt->data);
            nxt = nxt->previous;
        }
        return newStack;
    }
};

int inputVariable(string line);
Stack stringToOperation(string input);
EN_Validation_t check(Stack cpy);
Stack infixToPostfix(Stack operation);
int precedence(char op);
int evaluate(Stack postfix, int a, int b, int c);

int main()
{
    Stack operation = Stack(NULL, 0);
    Stack postfix = Stack(NULL, 0);

    /* Take the input from the user */
    string input, aline, bline, cline;
    getline(cin, input);
    getline(cin, aline);
    getline(cin, bline);
    getline(cin, cline);
    
    int a, b, c;
    a = inputVariable(aline);
    b = inputVariable(bline);
    c = inputVariable(cline);

    /* Take the input string and put it in stack operation*/
    operation = stringToOperation(input);
    Stack cpy = operation.reverse().reverse();

    /* Check validity of expression */
    if (check(cpy) == NOT_VALID)
        printf("Error");
    else{
        /* Turn infix to postfix */
        postfix = infixToPostfix(operation);
        postfix.printOperation();

        /* Evaluate postfix */
        printf("%d", evaluate(postfix, a, b, c));
    }
    return 0;
}

int inputVariable(string line)
{
    int res;
    char tmp;
    stringstream ss;
    ss << line;
    ss >> tmp;
    ss >> tmp;
    ss >> res;
    return res;
}

Stack stringToOperation(string input)
{
    Stack operation = Stack(NULL, 0);
    for (int i = 0; i < int(input.length()); i++)
    {
        if (input[i] == '\0')
            break;
        else if ((input[i] >= '0' && input[i] <= '9') || input[i] == 'a' || input[i] == 'b' || input[i] == 'c')
        {
            if (input[i + 1] >= '0' && input[i + 1] <= '9') {
                operation.push((input[i] - '0') * 10 + (input[i + 1] - '0'));
                i++;
            }
            else if (input[i] == 'a' || input[i] == 'b' || input[i] == 'c')
                operation.push(input[i]);
            else
                operation.push(input[i] - '0');
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '(' || input[i] == ')' || input[i] == '^')
        {
            operation.push(input[i]);
        }
    }
    operation = operation.reverse();
    return operation;
}

EN_Validation_t check(Stack cpy)
{
    int operationLength = cpy.size();
    int brackets = 0;
    int previousOperation = 0;
    try {
        for (int i = 0; i < operationLength; i++)
        {
            if (cpy.peek() == '+' || cpy.peek() == '-' || cpy.peek() == '*' || cpy.peek() == '/' || cpy.peek() == '^') {
                if (i == 0 && cpy.peek() != '-' && cpy.peek() != '(')
                    return NOT_VALID;
                if (i == operationLength - 1)
                    return NOT_VALID;
                previousOperation = cpy.pop();
                if (cpy.peek() == '+' || cpy.peek() == '*' || cpy.peek() == '/' || cpy.peek() == '^')
                    return NOT_VALID;
                else if (cpy.peek() == '-' && previousOperation != '-')
                {
                    cpy.pop();
                    if (cpy.peek() != '-') {
                        return NOT_VALID;
                    }
                    else {
                        i++;
                        cpy.pop();
                        i++;
                    }
                }
            }
            else if (cpy.peek() == ')') {
                if (brackets == 0 || previousOperation == '(' || previousOperation == '+' || previousOperation == '-' || previousOperation == '*' || previousOperation == '/' || previousOperation == '^')
                    return NOT_VALID;
                else {
                    brackets--;
                    previousOperation = cpy.pop();
                }
            }
            else if (cpy.peek() == '(') {
                if (previousOperation == '+' || previousOperation == '-' || previousOperation == '*' || previousOperation == '/' || previousOperation == '^' || previousOperation == '(' || previousOperation == 0) {
                    brackets++;
                    previousOperation = cpy.pop();
                    if (cpy.peek() == '+' || cpy.peek() == '-' || cpy.peek() == '*' || cpy.peek() == '/' || cpy.peek() == '^')
                        return NOT_VALID;
                }
                else
                    return NOT_VALID;
            }
            else if (cpy.peek() == 'a' || cpy.peek() == 'b' || cpy.peek() == 'c') {
                if (previousOperation != '+' && previousOperation != '-' && previousOperation != '*' && previousOperation != '/' && previousOperation != '^' && previousOperation != '(' && previousOperation != 0)
                    return NOT_VALID;
                previousOperation = cpy.pop();
                if (cpy.peek() != '+' && cpy.peek() != '-' && cpy.peek() != '*' && cpy.peek() != '/' && cpy.peek() != '^' && cpy.peek() != ')')
                    return NOT_VALID;
            }
            else
                previousOperation = cpy.pop();
        }
    }
    catch (int size){}
    
    if (brackets == 0)
        return VALID;
    else
        return NOT_VALID;
}

Stack infixToPostfix(Stack operation)
{
    Stack postfix = Stack(NULL, 0);
    int operationLength = operation.size();
    Stack ordered = Stack(NULL, 0);
    char currentOperation;
    for (int i = 0; i < operationLength; i++)
    {
        try {
            if (operation.peek() == '(')
            {
                ordered.push(operation.pop());
            }
            else if (operation.peek() == ')')
            {
                while (ordered.peek() != '(')
                    postfix.push(ordered.pop());
                ordered.pop();
                operation.pop();
            }
            else if (operation.peek() == '+' || operation.peek() == '-' || operation.peek() == '*' || operation.peek() == '/' || operation.peek() == '^')
            {
                currentOperation = operation.pop();
                if (currentOperation == '-' && operation.peek() == '-')
                {
                    i++;
                    operation.pop();
                    if (i == 1) {
                        continue;
                    }
                    else if (i != 1)
                    {
                         currentOperation = '+';
                    }   
                }
                if (operation.peek() == '-' && currentOperation != '-')
                {
                    operation.pop();
                    i++;
                    operation.pop();
                    i++;
                }
                if (ordered.size() == 0)
                    ordered.push(currentOperation);
                else {
                    while (ordered.size() != 0) {
                        if (precedence(currentOperation) <= precedence(ordered.peek())) {
                            //printf("ah\n");
                            postfix.push(ordered.pop());
                        }
                        else {
                            ordered.push(currentOperation);
                            break;
                        }
                    }
                    if (ordered.size() == 0 || ordered.peek() != currentOperation)
                        ordered.push(currentOperation);
                }
            }
            else
            {
                postfix.push(operation.pop());
            }
        }
        catch(int num){}
    }
    while (ordered.size() != 0)
        postfix.push(ordered.pop());
    return postfix;
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 0;
    else if (op == '*' || op == '/')
        return 1;
    else if (op == '^')
        return 2;
    else
        return -1;
}

int evaluate(Stack postfix, int a, int b, int c)
{
    postfix = postfix.reverse();
        Stack result = Stack(NULL, 0);
        int  postfixlength = postfix.size();
        int postfixElement, var1, var2;
        for (int i = 0; i < postfixlength; i++)
        {
            postfixElement = postfix.pop();
            if (postfixElement == '+') {
                var1 = result.pop();
                var2 = result.pop();
                result.push(var1 + var2);
            }
            else if (postfixElement == '-') {
                var1 = result.pop();
                if (result.size() == 0)
                    result.push(-var1);
                else {
                    var2 = result.pop();
                    result.push(var2 - var1);
                }
            }
            else if (postfixElement == '*') {
                var1 = result.pop();
                var2 = result.pop();
                result.push(var1 * var2);
            }
            else if (postfixElement == '/')
            {
                var1 = result.pop();
                var2 = result.pop();
                result.push(var2 / var1);
            }
            else if (postfixElement == '^')
            {
                var1 = result.pop();
                var2 = result.pop();
                result.push(pow(var2, var1));
            }
            else if (postfixElement == 'a')
                result.push(a);
            else if (postfixElement == 'b')
                result.push(b);
            else if (postfixElement == 'c')
                result.push(c);
            else
                result.push(postfixElement);
        }
        return result.pop();
}
