#include <iostream>
#include <math.h>
using namespace std;

class Heap{
    static const int size = 11;
    int heap[size], current = 0;

    int getChildL(int parent){
        return ((parent * 2) + 1);
    }

    int getChildR(int parent) {
        return ((parent * 2) + 2);
    }

    int getParent(int child){
        return (child-1)/2;
    }

public:
    Heap(){
        for(int i = 0; i < size; i++){
            heap[i] = -1;
        }
    }

    void display(){
        for(int i = 0; i < size; i++) {
            cout<<heap[i]<< " ";
        }
        cout<<endl;
    }

    void insert(int data){
        if(current < size){
            heap[current++] = data;
            bubbleUp();
        }
        else{
            cout<<"Heap is full!";
        }

    }

    int remove(){
        int temp = -1, index = 0;
        if(current >= 0){

        }
        else{
            cout<<"Heap is empty!";
        }

        return temp;
    }



    void bubbleDown(){
        int index = 0, child1, child2;

        while(index <= size-1){}

    }

    void swap(int first, int second){
        int temp = heap[first];
        heap[first] = heap[second];
        heap[second] = temp;
    }

    void bubbleUp(){
        int index = current - 1;
        while(index > 0 && heap[index] > heap[getParent(index)]){
            swap(index, getParent(index));
            index = getParent(index);
        }
    }

    void runApp(){
        int input = -1;
        int temp;
        while(input != 0){
            cout<<"1. Insert"<<endl;
            cout<<"2. display"<<endl;
            cout<<"3. Heap Sort"<<endl;
            cin>>input;
            switch(input){
                case 1:
                    cout<<"Enter the number to be inserted :";
                    cin>>temp;
                    insert(temp);
                    break;
                case 2:
                    display();
                    break;
                case 3:
                    heapSort();
                    break;
            }
        }
    }

    void heapSort(){
        int temp;
        for(int i = 0; i <= current; i++){
            temp = remove();
            if(temp != -1)
                cout<<temp<<" ";
        }

        cout<<endl;
        current = 0;
    }

};


int main(){
    Heap heap;
    heap.runApp();
}