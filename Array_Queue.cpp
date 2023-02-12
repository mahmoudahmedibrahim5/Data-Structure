#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Queue {
private:
    int front, rear;
    int Size, Cap;
	int *arr;
public:
    // Constructor
    Queue(int cap) {
        front = 0 ;
		rear = 0 ;  
        Size = 0;
		Cap = cap;
		arr = new int[cap+1];
    }
    // Methods
	void Fill(int data){
		if(Cap == rear){
			cout << "Error" << endl;
			return;
		}
        else {
            arr[rear] = data;
            rear++;
            Size++;
            return;
        }
	}
    void Enqueue(int data)
    {
		if(Cap+1 == rear){
			cout << "Error" << endl;
			return;
		}
		else{
			if(rear == 0){
				arr[front] = data;
				//cout << arr[front] << endl;
				rear++;
				Size++;
				return;
			}
			else{
			    for(int i = rear; i > 0; i--){
                arr[i] = arr[i-1];
            	//cout << arr[i] << endl;
                }
				arr[front] = data;
			}
			rear++;
		}
        Size++;
		return;
    }
    void Dequeue(void) {
        if(front == rear){
			cout << "Error" << endl;
			return;
		}
		else{
			arr[rear-1] = arr[rear];
			rear--;
		}
		Size--;
		return;
    }
    bool isEmpty(void) {
        if (Size == 0)
            return true;
        else
            return false;
    }
    int size(void) {
        return Size;
    }
	void printQueue(void)
    {
        printf("[");
        for (int i = 0; i < Size; i++)
        {
			if (i < Size - 1)
            {
                printf("%d, ", arr[i]);
            }
            else
            {
                printf("%d", arr[i]);
            }
        }
        printf("]");
    }
};

int main()
{
    // Input List from the user 
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
        if (input[1] == ']' || comma == ']') break;
        line >> vector_elements;
        array.push_back(vector_elements);
    }

    Queue queue = Queue(array.size());

    for (int i = 0; i < int(array.size()); i++)
    {
        queue.Fill(array[i]);
    }
	
    string instruction;
    getline(cin, instruction);

    if (instruction == "enqueue") {
        int data;
        cin >> data;
		queue.Enqueue(data);
		queue.printQueue();
    }
    else if (instruction == "dequeue") {
        if (queue.isEmpty())
        {
            cout << "Error" << endl;
        }
        else {
            queue.Dequeue();
            queue.printQueue();
        }
    }
    else if (instruction == "isEmpty") {
        if (queue.isEmpty() == true)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    else if (instruction == "size")
    {
        cout << queue.size() << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
    return 0;
}