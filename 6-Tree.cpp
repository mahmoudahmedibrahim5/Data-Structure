#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/* This struct represents each element in the tree
    Assuming that:
    - Each element has value which should be >= 0 (Uninitialized = -1)
    - Each element has boolean state
    - Each element can have many children not only 2
 */

typedef struct vertex{
    /* Element data */
    int value;
    bool state;

    /* Linking variables */
    vertex* parent;
    vertex** children;
    int childrenCount;

    /* Constructors*/
    vertex(){
        parent = NULL;
        children = NULL;
        childrenCount = 0;
        value = -1;
    }
    vertex(int _value, bool _state){
        parent = NULL;
        children = NULL;
        childrenCount = 0;
        value = _value;
        state = _state;
    }

}ST_vertex_t;

/* This class implement the most basic utilities for a tree 
   - Add vertices to head
   - Add children vertices to current vertex
   - remove vertex with its children
   - remove vertex and connect its children to its parent
   - print the tree
   - ... More features might be added later
*/
class Tree
{
private:
    ST_vertex_t* head;

public:
    Tree()
    {
        head = new ST_vertex_t;
        head->parent = NULL;
        head->childrenCount = 0;
        head->children = NULL;
        head->value = -1;
    }
    Tree(int value, bool state)
    {
        head = new ST_vertex_t;
        head->parent = NULL;
        head->childrenCount = 0;
        head->children = NULL;
        head->value = value;
        head->state = state;
    }

    void setHeadValue(int value, bool state)
    {
        head->value = value;
        head->state = state;
    }
    void addHeadChild(ST_vertex_t* child)
    {
        // Assign the vertex as the parent for the child
        child->parent = head;

        // Increment the number of children
        head->childrenCount++;

        // Allocate space with the new number of children for the array of children
        ST_vertex_t** copy = new ST_vertex_t*[head->childrenCount];

        // Copy the old children to the new allocated array
        for(int i = 0; i < head->childrenCount - 1; i++)
            copy[i] = head->children[i];
        
        // Delete the old array if it wasn't empty
        if(head->children != NULL)
            delete head->children[head->childrenCount-1];

        // Add the new child
        copy[head->childrenCount - 1] = child;
        
        // Assign the children array to the new allocated array
        head->children = copy;
    }

    void addVertexChild(ST_vertex_t* vertex, ST_vertex_t* child)
    {
        // Assign the vertex as the parent for the child
        child->parent = vertex;

        // Increment the count of children
        vertex->childrenCount++;

        // Allocate space with the new number of children for the array of children
        ST_vertex_t** copy = new ST_vertex_t*[vertex->childrenCount];

        // Copy the old children to the new allocated array
        for(int i = 0; i < vertex->childrenCount - 1; i++)
            copy[i] = vertex->children[i];
        
        // Delete the old array if it wasn't empty
        if(vertex->children != NULL)
            delete vertex->children;

        // Add the new child
        copy[vertex->childrenCount - 1] = child;

        // Assign the children array to the new allocated array
        vertex->children = copy;
    }

    void removeVertexAndItsChildren(ST_vertex_t* vertex)
    {
        ST_vertex_t* parent = vertex->parent;

        // Decrement the count of children
        parent->childrenCount--;

        // Allocate space with the new number of children for the array of children
        ST_vertex_t** copy = new ST_vertex_t*[parent->childrenCount];

        // Copy the old children to the new allocated array without the deleted child
        int index = 0;
        for(int i = 0; i < parent->childrenCount + 1; i++){
            if(parent->children[i] != vertex)
                copy[index++] = parent->children[i];
        }

        // delete the old children array
        delete parent->children;

        // Assign the children array to the new allocated array
        parent->children = copy;
    }

    void removeVertexWithoutRemovingChildren(ST_vertex_t* vertex)
    {
        ST_vertex_t* parent = vertex->parent;
        for(int i = 0; i < vertex->childrenCount; i++)
            addVertexChild(parent, vertex->children[i]);
        removeVertexAndItsChildren(vertex);
    }

    void printChildren(ST_vertex_t* vertex)
    {
        if(vertex->childrenCount == 0)
            return;

        //cout << endl << "Start Child" << endl;
        for(int i = 0; i < vertex->childrenCount; i++){
            //cout << "Branch: " << i << endl; 
            cout << vertex->children[i]->value << endl;
            printChildren(vertex->children[i]);
        }
        //cout << "End Child" << endl << endl;
    }

    void printTree(void)
    {
        if(head->value == -1)
            cout << "Error Head value undefined" << endl;
        else
        {
            cout << "Head value: " << head->value << endl;
            printChildren(head);
        }
    }
};


int main()
{
    Tree t;
    t.setHeadValue(0, 0);
    
    ST_vertex_t v1;
    v1.value = 1;
    v1.state = 1;

    ST_vertex_t v2;
    v2.value = 2;
    v2.state = 0;

    ST_vertex_t v3(3, 1);
    ST_vertex_t v4(4, 0);

    t.addHeadChild(&v1);
    t.addHeadChild(&v2);

    t.addVertexChild(&v1, &v3);
    t.addVertexChild(&v2, &v4);

    t.printTree();
    

    ST_vertex_t v5_9[5];
    for(int i = 0; i < 5; i++){
        v5_9[i].value = i + 6;
        v5_9[i].state = (i + 6) % 2;
        t.addVertexChild(&v3, &v5_9[i]);
    }

    t.printTree();
    
    t.removeVertexAndItsChildren(&v5_9[3]);

    t.printTree();

    t.removeVertexWithoutRemovingChildren(&v1);

    t.printTree();
}
