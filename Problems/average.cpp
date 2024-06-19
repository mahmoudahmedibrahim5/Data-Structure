#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{   
    /* Declaring variables */
    vector <int> array;
    string input;
    stringstream line;
    char comma;
    int vector_element;
    
    /* Read the input array from the user*/
    getline(cin, input);
    line << input;

    /* Convert the input string to integer vector */    
    while(1)
    {
        line >> comma;
        if(comma == ']' || input == "[]") break;
        line >> vector_element;
        array.push_back(vector_element);
    }

    /* Calculate average value */
    double average, sum=0;
    for(int i=0; i<int(array.size()); i++)
    {
        sum += array[i];
    }
    if (int(array.size()) == 0) average = 0;
    else average = sum/double(array.size());
    if(average == int(average))
        printf("%.1lf", average);
    else
        cout << average;
    return 0;
}
