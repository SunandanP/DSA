#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *left, *right;
    bool leaf;

    Node(int data){
        this->data = data;
        leaf = false;
        left = NULL;
        right = NULL;
    }

    Node(){
        data = -1;
        leaf = false;
        left = NULL;
        right = NULL;
    }
};

class TBT{
    Node *root, *header;
    Node *inorder[20];
    int current;

public:
    TBT(){
        root = NULL;
        header = new Node(0);
        header->left = root;
        header->right = root;
        current = 0;
    }

    void insert(int data){
        Node *node = new Node(data), *p = root, *q = root;
        node->leaf = true;
        bool left = false;

        if(root == NULL){
            node->leaf = true;
            root = node;
        }
        else{
            while(p){
                if(node->data < p->data){
                    left = true;
                    p = p->left;
                    if(p != NULL){
                        q = q->left;
                    }
                }
                else if(node->data > p->data){
                    left = false;
                    p = p->right;
                    if(p != NULL){
                        q = q->right;
                    }
                }
            }
            if(left){
                q->left = node;
                q->leaf = false;
            }
            else{
                q->right = node;
                q->leaf = false;
            }
        }




    }

    void inorderT(){
        inOrder(root);
    }

    void inOrder(Node *node){
        if(node == NULL){
            return;
        }

        inOrder(node->left);
        cout<<node->data<<" ";
        inOrder(node->right);
    }

    void init(){
        calculateInOrder(root);
    }

    void calculateInOrder(Node *node){
        if(node == NULL){
            return;
        }

        calculateInOrder(node->left);
        inorder[current++] = node;
        calculateInOrder(node->right);
    }

    int getIndex(Node *node){
        for(int i = 0; i < 20; i++){
            if(node == inorder[i]){
                return i;
            }
        }
        return -1;
    }

    void threader(){
        thread(root);
    }

    void thread(Node *node){
        if(node == NULL){
            return;
        }

        thread(node->left);
        if(node->left == NULL && node->right == NULL){
            if(getIndex(node) == 0){
                node->left = header;
                node->right = inorder[1];
            }
            else if(getIndex(node) == current-1){
                node->left = inorder[current -1];
                node->right = header;
            }
            else{
                int index = getIndex(node);
                node->left = inorder[index - 1];
                node->right = inorder[index + 1];
            }
        }
        thread(node->right);
    }

    Node* leftMost(Node *node){
        Node *ptr = node;
        while(ptr){
            if(!ptr->leaf)
                ptr = ptr -> left;
            else{
                if(ptr){
                    node = ptr;
                }
                break;
            }
            if(ptr){
                node = ptr;
            }

        }
        return node;
    }

    void TT(){
        threadedTraversal(root);
    }

    void threadedTraversal(Node *node){
        Node *current = leftMost(node);
        while(current != NULL || current != header){
            cout<<current->data<<" ";

            if(current->leaf)
                current = current->right;
            else
                current = leftMost(current->right);
        }
    }
};

int main(){
    TBT e;
    e.insert(55);
    e.insert(23);
    e.insert(42);
    e.insert(60);
    e.insert(58);
    e.insert(72);
    e.init();
    e.inorderT();
    cout<<endl;
    e.threader();
    e.TT();

    return 0;
}