#include <iostream>
#include <vector>

using namespace std;
void CheckCorresponding(int i, int j);

vector <vector <char>> image;   // 2D vector for the image
vector <char> OrderedPair;      // Ordered pair of each element in the image
vector <vector <int>> result;   // vector for the final result (centres) 
vector <int> center;            // center of the islands
int  rows, columns;             // rows, columns are the dimensions of the image
char TeamID;
int elementsOfIsland, temp;     // temp will be used in sorting

// vectors stores all x-coordinates and y-coordinates of the island will be used to know start and end
vector <int> X_minmax;              
vector <int> Y_minmax;
// Start and end of the island to calculate center
int X_Start, X_End, Y_Start, Y_End; 

int main()
{
    /////////////////////////////////////////////////////////* Input the image *//////////////////////////////////////////////////////
        int i, j, k, MinArea;                   // i, j, k are counters
        char comma, read;
        cin >> rows >> comma >> columns;        // Input the first line
        for(i=0; i<rows; i++)
        {
            for (j=0; j<columns; j++)
            {// Read lines
                cin >> read;
                OrderedPair.push_back(read);
            }
            image.push_back(OrderedPair);       // Push the line into the image
            OrderedPair.clear();                // clear vector for next line
        }
        cin >> TeamID;
        cin >> MinArea;
    //////////////////////////////////////////////////////* Find Players position *///////////////////////////////////////////////////
    for (i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            if(image[i][j] == TeamID)
            {
                elementsOfIsland=1;
                CheckCorresponding(i, j);
                // Put initial value for start and end of the island
                X_Start = X_minmax[0];
                X_End = X_minmax[0];
                Y_Start = Y_minmax[0];
                Y_End = Y_minmax[0];
                for(k=0; k<X_minmax.size(); k++)
                {// Smallest element in minmax vector is the start and Biggest is the end
                    if(X_minmax[k] < X_Start)
                        X_Start = X_minmax[k];
                    if(X_minmax[k] > X_End)
                        X_End = X_minmax[k];
                    if(Y_minmax[k] < Y_Start)
                        Y_Start = Y_minmax[k];
                    if(Y_minmax[k] > Y_End)
                        Y_End = Y_minmax[k];
                }
                // Clear minmax vectors for next island
                X_minmax.clear();
                Y_minmax.clear();
                if(elementsOfIsland*4 >= MinArea)
                {// Check Threshold
                    center.push_back(((2*X_Start+1)+(2*X_End+1))/2);
                    center.push_back(((2*Y_Start+1)+(2*Y_End+1))/2);
                    result.push_back(center);
                    center.clear();
                }
            }
            else
            {
                continue;
            }
        }
    }
    //////////////////////////////////////////////////////* Sorting The Output *//////////////////////////////////////////////////////
    // Bubble Sort
    for(i=0; i<int(result.size()-1); i++)
    {
        for(j=0; j<int(result.size()-1); j++)
        {
        if(result[j][1] > result[j+1][1])
        {
            temp = result[j][0];
            result[j][0] = result [j+1][0];
            result[j+1][0] = temp;
            temp = result[j][1];
            result[j][1] = result [j+1][1];
            result[j+1][1] = temp;
        }
        else if (result[j][1] == result[j+1][1])
        {
            if (result[j][0] > result[j+1][0])
            {
                temp = result[j][0];
                result[j][0] = result [j+1][0];
                result[j+1][0] = temp;
                temp = result[j][1];
                result[j][1] = result [j+1][1];
                result[j+1][1] = temp;
                temp = result[j][0];
                result[j][0] = result [j+1][0];
                result[j+1][0] = temp;
                temp = result[j][1];
                result[j][1] = result [j+1][1];
                result[j+1][1] = temp;
            }
        }
        }
    }
    //////////////////////////////////////////////////////* Printing the Output */////////////////////////////////////////////////////
    cout << "[";
    for(i=0; i<int(result.size()); i++)
    {
        if (i == int(result.size())-1)
        cout << "(" << result[i][1] << ", " << result[i][0] << ")";
        else
        cout << "(" << result[i][1] << ", " << result[i][0] << "), ";
    }
    cout << "]";
    return 0;
}

void CheckCorresponding(int i, int j)
{
    image[i][j] = '0';      // Mark this element as visited element
    X_minmax.push_back(i);
    Y_minmax.push_back(j);

    if( (i<(rows-1)) && (image [i+1][j] == TeamID) )     // Down
    {
        elementsOfIsland++;
        CheckCorresponding(i+1, j);
    }

    if( (i>0) && (image [i-1][j] == TeamID) )            // Up
    {
        elementsOfIsland++;
        CheckCorresponding(i-1, j);
    }

    if( (j<(columns-1)) && (image [i][j+1] == TeamID) )  // Right
    {
        elementsOfIsland++;
        CheckCorresponding(i, j+1);
    }

    if( (j>0) && (image [i][j-1] == TeamID) )            // Left
    {
        elementsOfIsland++;
        CheckCorresponding(i, j-1);
    }
}
