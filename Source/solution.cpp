#include <iostream>
using namespace std;

class Solution{
    bool doors[101];

public:
    void initially(){
        for(int i = 0; i <= 100; i++){
            doors[i] = false;
        }
    }

    void toggle(int index){
        if(doors[index]){
            doors[index] = false;
        }
        else{
            doors[index] = true;
        }
    }

    void calculate(){
        print();
        for(int man = 1; man <= 100; man++){
            for(int door = 1; door <= 100; door++){
                if(door % man == 0){
                    toggle(door);
                }
            }
        }

        int count;
        for(int i = 1; i <= 100; i++){
            if(doors[i]){
                cout<<i<<endl;
                count++;
            }
        }
        cout<<count;
        print();
    }

    void print(){
        for(int i = 1; i < 101; i++ )
            cout << i <<" "<<(doors[i]? "Open": "Close") << endl;
        cout<<endl;
    }
};

int main(){
    Solution s;
    s.initially();
    s.calculate();

}

/* 4,8
 * 5,9
 * 1,10
 * 2,6
 * 3,7
 *
 * */