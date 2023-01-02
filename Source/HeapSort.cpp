#include <iostream>
using namespace std;

class Heap{
    int heap[100];
    int size = 0;

public:
    void insert(int data){
        int index = ++size;
        heap[size] = data;

        while(index > 1){
            int parent = index/2;
            if(heap[parent] < heap[index]){
                swap(heap[parent], heap[index]);
            }
            index = parent;
        }
    }

    void display(){
        for(int i = 1; i <= size; i++){
            cout<<heap[i]<<" ";
        }
        cout<<endl;
    }

    int deleteNode(){
        int temp = heap[1];
        heap[1] = heap[size];
        size--;

        int index = 1;
        while(index * 2 + 1 <= size){
            int largerChild = (heap[index * 2] > heap[index * 2 + 1])? index * 2 : index * 2 + 1;
            if(heap[index] < heap[largerChild]){
                swap(heap[index], heap[largerChild]);
                index = largerChild;
            }

        }
        return temp;
    }

    void heapify(int arr[], int size, int index){
        int largest = index;
        int left = index * 2;
        int right = index * 2 + 1;

        if(left < size && arr[left] < arr[largest])
            largest = left;
        if(right < size && arr[right] < arr[largest])
            largest = right;

        if(largest != index){
            swap(arr[largest], arr[index]);
            heapify(arr, size, largest);
        }
    }

    void heapSort(){
        int size = this->size;


    }

    void sort(){
        int last = size, temp[size+1];
        for(int i = 1; i <= last; i++){
            temp[i] = deleteNode();
        }
        for(int i = 1; i <= last; i++)
            insert(temp[i]);
    }
};


int main(){
    Heap heap;
    heap.insert(50);
    heap.insert(51);
    heap.insert(52);
    heap.insert(55);
    heap.insert(70);
    heap.display();
    heap.sort();
    heap.display();
}