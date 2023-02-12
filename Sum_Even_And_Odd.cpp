#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
int i; // Counter for loops
vector <int> EvenAndOddSum(vector<int> arr);

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
            if(input[1] == ']' || comma == ']') break;
            line >> vector_elements;
            array.push_back(vector_elements);
        }
    vector <int> sum = EvenAndOddSum(array);
    printf("[%d, %d]\n", sum[0], sum[1]);
    return 0;
}

vector <int> EvenAndOddSum(vector<int> arr)
{
    vector <int> sum{0,0};
    for(i=0; i<int(arr.size()); i++)
    {
        if(arr[i]%2 == 0)
            sum[0] += arr[i];
        else
            sum[1] += arr[i];
    }
    return sum;
}
