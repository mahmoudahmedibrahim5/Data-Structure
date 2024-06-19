#include <iostream>

using namespace std;
int fibonnaci(int n);

int main()
{
    int n;
    cin >> n;
    cout << fibonnaci(n);
    return 0;
}

int fibonnaci(int n)
{
    int result = 0;
    int temp = 1;
    for(int i=1; i<n; i++)
    {
        result = result + temp;
        temp = result - temp;
    }
    return result;
}
/*
int fibonnaci(int n)
{
    int next_val = 1;
    int current_val = 1;
    int prev_val = 0;
    if (n==1) return prev_val;
    else if (n==2) return current_val;
    else{
    for(int i=1; i<n; i++)
    {
        next_val = current_val + prev_val;
        prev_val = current_val;
        current_val = next_val;
    }
    return prev_val;
    }
}
*/