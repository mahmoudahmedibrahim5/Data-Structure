#include <iostream>

using namespace std;

class ICalculator
{
    float add(float x, float y);
    float divide (float x, float y);
    float multiply (float x, float y);
    void b(void);
};

class Calculator:ICalculator
{
public:
    float add(float x, float y)
    {
        return (x+y);
    }    
    float divide (float x, float y)
    {
        return (x/y);
    }
};

int main()
{
    Calculator cal;
    cout << "Enter the line" << endl;
    float x,y;
    char op;
    cin >> x >> op >> y;

    if (op == '+')
    {
    cout << cal.add(x,y);
    }
    else if (op == '/')
    {   
        if (y != 0)
        cout << cal.divide(x,y);
        else
        cout << "Error";
    }

    return 0;
}