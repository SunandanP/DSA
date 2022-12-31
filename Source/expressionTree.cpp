#include <iostream>
using namespace std;

struct Node{
    char data;
    Node *left, *right;

    Node(char data){
        this->data = data;
        left = right = NULL;
    }

    Node(){}
};

struct Block{
    Node node;
    Block *next;

    Block(Node node){
        this->node = node;
        next = NULL;
    }

    Block(){}
};


class Stack{
    Block *top = NULL;

public:

    void push(Node node){
        Block *block = new Block(node);
        block->next = top;
        top = block;
    }

    bool isEmpty(){
        if(top == NULL)
            return true;
        else
            return false;
    }

    Node pop(){
        if(!isEmpty()){
            Node node = top->node;
            top = top->next;
            return node;
        }
        return NULL;
    }
};


class ExpTree{
    Node *root = NULL;

public:
    bool isEmpty(){
        if(root == NULL)
            return true;
        else
            return false;
    }

    void build(string s){
        Stack stack;
        Node *temp, *op1, *op2;
        for(int i = 0; i < s.length(); i++){
            if(isalnum(s[i])){
                temp = new Node(s[i]);
                stack.push(*temp);
            }
            else{
                op1 = new Node(stack.pop());
                op2 = new Node(stack.pop());
                temp = new Node(s[i]);

                temp->left = op2;
                temp->right = op1;

                root = temp;
                stack.push(*temp);
            }
        }
    }

    void traverseIn(Node *ptr){
        if(ptr == NULL)
            return;
        traverseIn(ptr->left);
        cout<<ptr->data;
        traverseIn(ptr->right);

    }

    void traversePre(Node *ptr){
        if(ptr == NULL)
            return;
        cout<<ptr->data;
        traversePre(ptr->left);
        traversePre(ptr->right);

    }

    void traversePost(Node *ptr){
        if(ptr == NULL)
            return;
        traversePost(ptr->left);
        traversePost(ptr->right);
        cout<<ptr->data;
    }

    void postOrder(){
        traversePost(root);
        cout<<endl;
    }

    void inOrder(){
        traverseIn(root);
        cout<<endl;
    }

    void preOrder(){
        traversePre(root);
        cout<<endl;
    }

    void preOrderNR(){
        Stack s;
        Node temp;
        if(isEmpty())
            cout<<"Tree is empty!"<<endl;
        else{
            s.push(*root);
            while(!s.isEmpty()){
                temp = s.pop();
                cout<<temp.data;
                if(temp.right)
                    s.push(*temp.right);
                if(temp.left)
                    s.push(*temp.left);
            }
            cout<<endl;
        }

    }

    void inOrderNR(){
        Stack s;
        Node *temp;

        if(root == NULL)
            cout<<"Tree is empty"<<endl;
        else{
            temp = root;
            while(temp || !s.isEmpty()){
                while(temp){
                    s.push(*temp);
                    temp = temp->left;
                }
                temp = new Node();
                *temp = s.pop();
                cout<<temp->data;
                temp = temp->right;
            }
            cout<<endl;
        }
    }

    void postOrderNR(){
        string s;
        Node *temp = root;
        Stack s1,s2;
        s1.push(*temp);
        s2.push(*temp);
        while(!s1.isEmpty()){
            *temp = s1.pop();
            if(temp->right){
                s1.push(*temp->right);
                s2.push(*temp->right);
            }
            if(temp->left){
                s1.push(*temp->left);
                s2.push(*temp->left);
            }
        }
        while(!s2.isEmpty()){
            s += s2.pop().data;
        }

        cout<<s<<endl;
        build(s);
    }
};

int main(){
    ExpTree e;
    e.build("ab+c*");
    e.postOrder();
    e.postOrderNR();
    e.inOrder();
    e.inOrderNR();
    e.preOrder();
    e.preOrderNR();

}

//
// +
//a  b