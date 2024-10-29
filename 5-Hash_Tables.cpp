#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

#define MAX_NAME_SIZE   50

typedef struct{
    char name[MAX_NAME_SIZE];
    unsigned int age;
    // more data .....
} element;

class HashTable
{
private:
    int maxSize;
    element** table;
    unsigned int hash(char* name);

public:
    HashTable();
    HashTable(int size);
    
    bool insertElement(element* e);
    void deleteElement(element* e);
    element* findElement(char* name);
    
    void printTable(void);
    int getMaxSize(void);
};

HashTable::HashTable()
{
    maxSize = 10;
    table = new element*[maxSize];
    for(int i = 0; i < maxSize; i++)
        table[i] = NULL;
}
HashTable::HashTable(int size)
{
    maxSize = size;
    table = new element*[maxSize];
    for(int i = 0; i < maxSize; i++)
        table[i] = NULL;
}

unsigned int HashTable::hash(char* name)
{
    unsigned int value = 0;
    for(int i = 0; i < strnlen(name, MAX_NAME_SIZE); i++){
        value += name[i];
    }
    return value % maxSize; 
}
bool HashTable::insertElement(element* e)
{
    unsigned int rank = hash(e->name);
    if(table[rank] != NULL)
        return false;
    table[rank] = e;
    //printf("Insert %s at %i\n", e->name, rank);
    return true;
}
void HashTable::deleteElement(element* e)
{
    unsigned int rank = hash(e->name);
    table[rank] = NULL;
}
element* HashTable::findElement(char* name)
{
    int value = hash(name);
    return table[value];
}

void HashTable::printTable(void)
{
    cout << "###################### Hash Table ######################" << endl;
    for(int i = 0; i < maxSize; i++)
    {
        if(table[i] == NULL)
            printf("%i\t----\n", i);
        else
            printf("%i\t%s\n", i, table[i]->name);
    }
    cout << "############################################" << endl;
}
int HashTable::getMaxSize(void)
{
    return maxSize;
}


int main()
{
    HashTable t1(10);
    element e[5];
    e[0] = {.name = "Mahmoud", .age = 23};
    e[1] = {.name = "Tom", .age = 32};
    e[2] = {.name = "Miles", .age = 50};
    e[3] = {.name = "Dana", .age = 15};
    e[4] = {.name = "Mary", .age = 78};

    for(int i = 0; i < 5; i++)
        t1.insertElement(&e[i]);

    t1.printTable();
    
}