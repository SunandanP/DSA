#include <iostream>
using namespace std;

struct Node{
    string data;
    Node *next;

    Node(string name){
        this->data = name;
        next = NULL;
    }
};

class Stack{
    Node *top = NULL;

public:

    bool empty(){
        return (top == NULL);
    }

    void push(string data){
        Node *node = new Node(data);
        node->next = top;
        top = node;
    }

    string pop(){
        string temp;
        if(!empty()){
             temp = top->data;
             top = top->next;
        }
        return temp;
    }
};

class Dijkstras{

    static const int size = 5;
    string cities[size] = {"Mumbai", "Pune", "Akola", "Patna", "PCMC"};
    int distances[size][size] = {
            {0,6,0,1,0},
            {6,0,5,2,2},
            {0,5,0,0,5},
            {1,2,0,0,1},
            {0,2,5,1,0},
    };

public:

    int getNextVertex(bool visited[], int cost[size]){
        int min = INT_MAX, nextVertex;
        for(int i = 0; i < size; i++){
            if(!visited[i]){
                if(min > cost[i]){
                    min = cost[i];
                    nextVertex = i;
                }
            }
        }

        return nextVertex;
    }

    void dijkstras(int start, int end){
        bool visited[size];
        int visitedCount = 0, cost[size], prev[size];


        for(int i = 0; i < size; i++){
            cost[i] = INT_MAX;
            visited[i] = false;
        }

        cost[start] = 0;
        prev[start] = -1;

        while(visitedCount != size){
            int current = getNextVertex(visited,cost);

            visited[current] = true;

            for(int i = 0; i < size; i++){
                if(distances[current][i] != 0 && !visited[i]){
                    if(distances[current][i] + cost[current] < cost[i]){
                        cost[i] = distances[current][i] + cost[current];
                        prev[i] = current;
                    }
                }
            }

            visitedCount++;
        }
        display(end, cost, prev);
    }

    void display(int end, int cost[], int prev[]){
        Stack s;
        string path;
        int current = end;
        while(current != -1){
            s.push(cities[current]);
            current = prev[current];
        }

        while(!s.empty()){
            path += s.pop();
            if(!s.empty())
                path += " -> ";
        }

        cout<<path<<endl;
        cout<<"Total distance : "<<cost[end];
    }

    void init(){
        int temp;
        string name;

        for(int i = 0; i < size; i++){
            cout<<"Enter the name for City No. "<<(i+1)<<" :";
            cin>>name;
            cities[i] = name;
            cout<<endl;

        }
        for(int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                cout<<"Distance between "<<cities[i]<<" and "<<cities[j]<<" :";
                cin>>temp;
                cout<<endl;
                distances[i][j] = temp;
            }
        }
    }

    void runApp(){
        int input = -1;
        while(input != 0){
            cout<<"1. Set Names and Data of Map"<<endl;
            cout<<"2. Calculate Shortest path"<<endl;
            cin>>input;
            switch(input){
                case 1:
                    init();
                    break;
                case 2:
                    int start, end;
                    cout<<"Choose the starting point from the table"<<endl;
                    for(int i = 0; i < size; i++){
                        cout<<(i+1)<<" "<<cities[i]<<endl;
                    }
                    cout<<"Start :";
                    cin>>start;
                    cout<<"End :";
                    cin>>end;
                    dijkstras(start-1, end-1);
                    cout<<endl;
                    break;
            }
        }
    }
};

int main(){
    Dijkstras e;
    e.runApp();
}