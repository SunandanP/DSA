#include <iostream>

using namespace std;

struct tNode{
    int data;
    tNode *left;
    tNode *right;
    bool self;


    tNode(int data){
        this->data = data;
        left = NULL;
        right = NULL;
        self = false;
    }

    tNode(){
        left = NULL;
        right = NULL;
        self = false;
    };
};

struct sNode{
    tNode data;
    sNode *next;

    sNode(tNode data){
        this->data = data;
        next = NULL;
    }
};

class Stack{
    sNode *top = NULL;

public:
    bool isEmpty(){
        return (top == NULL);
    }

    void push(tNode data){
        sNode *node = new sNode(tNode(data));
        node->next = top;
        top = node;
    }

    tNode pop(){
        if(top != NULL){
            tNode temp = top->data;
            top = top->next;
            return temp;
        }
        return NULL;
    }
};

class TBT{
    static const int size = 20;
    tNode* inorder[size];
    int current = 0;
    tNode *header;
    tNode *root = NULL;

public:
    TBT(){
        header = new tNode;
        header->left = root;
        header->right = root;
    }
    void initInorder(tNode *node){
        if(node == NULL){
            return;
        }

        initInorder(node->left);
        inorder[current++] = node;
        initInorder(node->right);
    }

    void insert(int data){
        tNode *node = new tNode(data), *p = root, *q = root;
        bool left = false;
        if(root == NULL)
            root = node;

        else{
            while(p){
                if(p->data > node->data){
                    p = p->left;
                    left = true;
                    if(p){
                        q = q->left;
                    }
                }
                else{
                    p = p->right;
                    left = false;
                    if(p)
                        q = q->right;
                }
            }
            if(left){
                q->left = node;
            }
            else{
                q->right = node;
            }
        }
    }

    int getIndex(tNode *node){
        for(int i =0; i < size; i++){
            if(node == inorder[i]){
                return i;
            }
        }
        return -1;
    }

    void thread(tNode *node){
        bool threaded = false;
        if(node == NULL || node == header)
            return;

        if(node->left == NULL && node->right == NULL){
            int index = getIndex(node);
            if(index+1 < current){
                node->right = inorder[index+1];
                inorder[index+1]->self = true;
            }
            else
                node->right = header;
            threaded = true;
        }
        if(!threaded){
            if(node->self == false)
                thread(node->left);
        }
        thread(node->right);


    }

    void inorderThreaded(tNode *node){
        if(node == NULL || node == header)
            return;
        if(node->right)
            if(node->right->self == true){
                cout<<node->data<<" ";
                return;
            }
        inorderThreaded(node->left);
        cout<<node->data<<" ";
        inorderThreaded(node->right);
    }

    void preThreaded(tNode *node){
        if(node == NULL || node == header)
            return;
        if(node->right)
            if(node->right->self == true){
                cout<<node->data<<" ";
                return;
            }
        cout<<node->data<<" ";
        preThreaded(node->left);
        preThreaded(node->right);
    }

    tNode* leftMost(tNode *node){
        if(node == NULL){
            return NULL;
        }
        while(node->left){
            node = node->left;
        }
        return node;
    }

    void preorderT(tNode *node){
        if(node == NULL){
            return;
        }
        cout<<node->data<<" ";
        preorderT(node->left);
        preorderT(node->right);
    }

    void inorderT(tNode *node){
        if(node == NULL){
            return;
        }

        inorderT(node->left);
        cout<<node->data<<" ";
        inorderT(node->right);
    }

    void runApp(){
        int input = -1, temp;
        bool threaded = false;

        while(input != 0){
            cout<<"1. Insert"<<endl;
            cout<<"2. Display Inorder"<<endl;
            cout<<"3. Thread"<<endl;
            cin>>input;
            switch(input){
                case 1:
                    cout<<"Enter the number to be inserted :";
                    cin>>temp;
                    insert(temp);
                    break;
                case 2:
                    if(!threaded){
                        cout<<"Inorder : ";
                        inorderT(root);
                        cout<<endl;
                        cout<<"Preorder : ";
                        preorderT(root);
                    }
                    else{
                        cout<<"Inorder : ";
                        inorderThreaded(root);
                        cout<<endl;
                        cout<<"Preorder : ";
                        preThreaded(root);
                    }
                    cout<<endl;
                    break;
                case 3:
                    initInorder(root);
                    thread(root);
                    threaded = true;
                    break;
            }
        }
    }
};


int main(){
    TBT e;
    e.runApp();
    return 0;
}