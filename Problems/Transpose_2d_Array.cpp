#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;
int i, j;

int main()
{
    string input;
    stringstream line;
    getline(cin, input);
    line << input;
    int size = int( (-2+sqrt(12*input.length()+4))/6 );
    int array[size][size];
    char comma;
    line >> comma;

    for(i=0; i<size; i++)
    {
        line >> comma;
        for(j=0; j<size; j++)
        {
            line >> array[i][j];
            line >> comma;
        }
        line >> comma;
    }
    
    int newarray[size][size];
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            newarray[i][j] = array[j][i];
        }
    }

    printf("[");
    if (size == 0)
        printf("[]");
    for(i=0; i<size; i++)
    {
        printf("[");
        for(j=0; j<size; j++)
        {
            if(j == size-1)
                printf("%d", newarray[i][j]);
            else
                printf("%d, ", newarray[i][j]);
        }
        if(i == size-1)
            printf("]");
        else
            printf("], ");
    }
    printf("]");
    return 0;
}