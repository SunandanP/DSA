#include <iostream>
using namespace std;

class CircularQueue{
    static const int size = 6;
    int queue[size];
    int count = 0;
    int front = 0, rear = 0;

public:
    void display(){
        for(int i = 0; i < size; i++ )
            cout<<" "<<queue[i];
        cout<<endl;
    }


    void init(){
        for(int i = 0; i < size; i++)
            queue[i] = -1;
    }

    void enqueue(int data){
        if(count == size){
            cout<<"Queue is full";
        }
        else{
            queue[rear] = data;
            rear = (rear + 1) % size;
            count++;
        }
    }

    void dequeue(){
        int temp = -1;
        if(count != 0){
            temp = queue[front];
            queue[front] = -1;
            front = (front + 1) % size;
            count--;
        }
        if(temp != -1)
            cout<<temp<<" dequeued!"<<endl;
        else
            cout<<"Queue is empty!"<<endl;
    }

    void runApp(){
        int input = -1, temp;
        init();
        while(input != 0){
            cout<<"1. Display"<<endl;
            cout<<"2. Enqueue"<<endl;
            cout<<"3. Dequeue"<<endl;
            cin>>input;
            switch(input){
                case 1:
                    display();
                    break;
                case 2:
                    cout<<"Enter the element to be enqueued :";
                    cin>>temp;
                    enqueue(temp);
                    break;
                case 3:
                    dequeue();
                    break;
                default:
                    break;
            }
        }
    }
};

int main(){
    CircularQueue cq;
    cq.runApp();
}