#include <iostream>
using namespace std;

struct Edge{
    int v1, v2, w;

    Edge(int v1, int v2, int w){
        this->v1 = v1;
        this->v2 = v2;
        this->w = w;
    }

    Edge(){
        v1 = -1;
        v2 = -1;
        w = -1;
    }
};

class Solution{
    static const int size = 5;
    int parent[size];
    int rank[size], current = 0;
    Edge edges[20];
public:
    void init(){
        for(int i = 0; i < size; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int getParent(int index){
        if(index == parent[index])
            return index;
        return parent[index] = getParent(parent[index]);
    }

    void createSet(int a, int b){
        a = getParent(a);
        b = getParent(b);

        if(rank[a] < rank[b])
            parent[a] = b;
        else if(rank[b] < rank[a])
            parent[b] = a;
        else{
            parent[b] = a;
            rank[a]++;
        }
    }

    void getEdges(){
        int i;
        int i1,i2,w;
        while(true){
            cout<<"1. Add edges"<<endl;
            cout<<"2. exit"<<endl;
            cin>>i;
            if(i == 1){
                cout<<"Enter the first vertex number :";
                cin>>i1;
                cout<<"Enter the second vertex number :";
                cin>>i2;
                cout<<"Enter the weight of the edge :";
                cin>>w;
                edges[current++] = Edge(i1,i2,w);
            }
            else{
                break;
            }
        }
    }

    void sort(){
        for(int i = 0; i < current; i++){
            for(int j = 0; j < current; j++){
                if(edges[j].w > edges[j+1].w){
                    Edge temp = edges[j];
                    edges[j] = edges[j+1];
                    edges[j+1] = temp;
                }

            }
        }
    }

    void kruskal(){
        sort();
        init();
        int minWeight = 0 ;
        for(int i = 0; i < current; i++){
            int v1 = getParent(edges[i].v1);
            int v2 = getParent(edges[i].v2);
            int weight = edges[i].w;


            if(v1 != v2){
                minWeight += weight;
                createSet(v1, v2);
                cout<<v1<<" -> "<<v2<<endl;
            }
        }
        cout<<"Weight : "<<minWeight;
    }

    void runApp(){
        int i = -1;
        while(i != 0){
            cout<<"1. Enter edges"<<endl;
            cout<<"2. Min Spanning tree"<<endl;
            cin>>i;
            switch(i){
                case 1:
                    getEdges();
                    break;

                case 2:
                    kruskal();
                    cout<<endl;
                    break;
            }
        }
    }

};

/* 4 4 0
 * 1 2 6
 * 2 3 2
 * 1 3 2
 * 1 0 2
 *
 * */

int main(){
    Solution s;
    s.runApp();
    return 0;
}