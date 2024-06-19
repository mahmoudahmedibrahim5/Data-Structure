#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
int i; // Counter for loops
vector <int> reverse(vector <int> arr);

int main()
{
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
            if(input[1] == ']' || comma == ']') b
            line >> vector_elements;
            array.push_back(vector_elements);
        }

    array = reverse(array);
    
    printf("[");
    for(i=0; i<int(array.size()); i++)
        {
            if(i == int(array.size()-1))
                printf("%d",array[i]);
            else
                printf("%d, ",array[i]);
        }
    printf("]");
    return 0;
}

vector <int> reverse(vector <int> arr)
{
    vector <int> reversed_arr;
    int size = int(arr.size());
    for(i=0; i<size; i++)
    {
        reversed_arr.push_back(arr[size-1-i]);
    }
    return reversed_arr;
}
