#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
int i; // Counter for loops
vector <int> MoveValue(vector<int> arr, int val);

int main()
{
    stringstream line;
    vector <int> array;
    string input;
    char comma;
    int vector_elements;
    int val;

    getline(cin, input);
    line << input;
    
    while (1)
        {
            line >> comma;
            if(input[1] == ']' || comma == ']') break;
            line >> vector_elements;
            array.push_back(vector_elements);
        }
    cin >> val;
    array = MoveValue(array, val);
    printf("[");
    for(i=0; i<int(array.size()); i++)
        {
            if(i == (int(array.size()-1)))
                printf("%d",array[i]);
            else
                printf("%d, ",array[i]);
        }
    printf("]");
    return 0;
}

vector <int> MoveValue(vector<int> arr, int val)
{
    int cntr = 0;
    char flag;
    for(i=0; i<int(arr.size()); i++)
    {
        flag = 0;
        for(int j=0; j<int(arr.size())-cntr; j++)
        {    
            if(arr[j] == val)
            {
                arr.erase(arr.begin()+j);
                arr.push_back(val);
                cntr++;
                flag = 1;
            }
        }
        if(flag == 0)
        break;
    }
    return arr;
}
