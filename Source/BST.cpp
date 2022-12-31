#include <iostream>
using namespace std;

struct tNode{
    int data;
    tNode *left;
    tNode *right;

    tNode(int data){
        this->data = data;
        left = NULL;
        right = NULL;
    }

    tNode() {}
};

struct sNode{
    tNode tnode;
    sNode *next;

    sNode(tNode tnode)  {
        this->tnode = tnode;
        next = NULL;
    }
};

class Stack{
    sNode *top = NULL;

public:
    bool isEmpty(){
        if(top == NULL){
            return true;
        }
        else{
            return false;
        }
    }

    void push(int data){
        sNode *node = new sNode(tNode(data));
        node->next = top;
        top = node;
    }

    tNode pop(){
        tNode temp = NULL;
        if(!isEmpty()){
            temp = top->tnode;
            top = top->next;
        }
        return temp;
    }
};

class BST{
    tNode *root = NULL;

public:
    void insert(int data){
        tNode *node = new tNode(data), *p = root, *q = root;
        bool left = false;

        if(root == NULL)
            root = node;
        else{
            while(p){
                if(p->data >= node->data){
                    p = p->left;
                    if(p)
                        q = q->left;
                    left = true;
                }
                else{
                    p = p->right;
                    if(p)
                        q = q->right;
                    left = false;
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

    void preOrder(){
        traversePre(root);
    }

    void traversePre(tNode *node){
        if(node == NULL){
            return;
        }
        cout<<node->data<<" ";
        traversePre(node->left);
        traversePre(node->right);
    }

    void postOrder(){
        traversePost(root);
    }

    void traversePost(tNode *node){
        if(node == NULL){
            return;
        }
        traversePost(node->left);
        traversePost(node->right);
        cout<<node->data<<" ";
    }

    void inOrder(){
        traverseIn(root);
    }

    void traverseIn(tNode *node){
        if(node == NULL){
            return;
        }
        traverseIn(node->left);
        cout<<node->data<<" ";
        traverseIn(node->right);
    }

    void search(tNode *node, int key){
        if(node == NULL){
            return;
        }
        if(key == node->data){
            cout<<"found!"<<endl;
            return;
        }
        if(key < node->data)
            search(node->left, key);
        else
            search(node->right, key);
    }

    tNode* findSuccessor(tNode* node){
        tNode *temp = node;
        while(temp && temp->left){
            temp = temp->left;
        }
        return temp;
    }

    tNode* inorderSuccessor(tNode* node){

    }

    tNode* deleteKey(tNode *node, int key){
        if(node == NULL) return NULL;

        if(key == node->data){
            tNode *temp;
            if(node->left == NULL && node->right == NULL){
                temp = node;
                free(temp);
                return NULL;
            }

            else if (node->left == NULL){
                temp = node;
                node = node->right;
                free(temp);
                return node;
            }

            else if(node->right == NULL){
                temp = node;
                node = node->left;
                free(temp);
                return node;
            }

            else{
                temp = findSuccessor(node);
                node->data = temp->data;
                node->right = deleteKey(root->right, temp->data);
            }

            return node;

        }
        if(key < node->data)
            node->left = deleteKey(node->left, key);
        else
            node->right = deleteKey(node->right, key);
    }

    void runApp(){
        int input = -1, temp;
        while(input != 0){
            cout<<"1. Insert"<<endl;
            cout<<"2. Display"<<endl;
            cout<<"3. Search"<<endl;
            cout<<"4. Print leaf Nodes"<<endl;
            cout<<"5. Print Parents with Children"<<endl;
            cout<<"6. Depth"<<endl;
            cout<<"7. Level Order Traversal"<<endl;
            cout<<"8. Delete"<<endl;
            cin>>input;
            switch(input){
                case 1:
                    cout<<"Enter the number to be inserted :";
                    cin>>temp;
                    insert(temp);
                    break;
                case 2:
                    cout<<"1. Inorder"<<endl;
                    cout<<"2. Preorder"<<endl;
                    cout<<"3. Postorder"<<endl;
                    cin>>temp;
                    switch(temp){
                        case 1:
                            inOrder();
                            break;
                        case 2:
                            preOrder();
                            break;
                        case 3:
                            postOrder();
                            break;
                    }
                    cout<<endl;
                    break;
                case 3:
                    cout<<"Enter the element to be searched :";
                    cin>>temp;
                    search(root, temp);
                    break;
                case 4:
                    printLeaves(root);
                    cout<<endl;
                    break;
                case 5:
                    parentAndSons(root);
                    cout<<endl;
                    break;
                case 6:
                    cout<<height(root);
                    break;
                case 7:
                    levelOrder();
                    break;
                case 8:
                    cout<<"Enter the number to be deleted :";
                    cin>>temp;
                    deleteKey(root,temp);
                    break;
            }
        }
    }

    void printLeaves(tNode *node){
        if(node == NULL)
            return;

        if(node->left == NULL && node->right == NULL){
            cout<<node->data<<" ";
        }

        printLeaves(node->left);
        printLeaves(node->right);
    }

    void parentAndSons(tNode *node){
        if(node == NULL)
            return;
        cout<<"Parent : "<<node->data<<endl;
        cout<<"Children :";
        if(node->left)
            cout<<node->left->data<<" ";
        if(node->right)
            cout<<node->right->data<<" ";
        cout<<endl;
        parentAndSons(node->left);
        parentAndSons(node->right);
    }

    int height(tNode *node){
        if(node == NULL)
            return 0;

        if(node->left == NULL && node->right==NULL)
            return 0;

        return (1 + ((height(node->left) > height(node->right)) ? (height(node->left)):(height(node->right))));
    }

    void nodesAtDistance(int distance, tNode *node){
        if(node == NULL)
            return;

        if(distance == 0){
            cout<<node->data<<" ";
            return;
        }

        nodesAtDistance(distance - 1,node->left);
        nodesAtDistance(distance - 1,node->right);
    }

    void levelOrder(){
        for(int i = 0; i <= height(root); i++){
            nodesAtDistance(i, root);
            cout<<endl;
        }
    }
};

int main(){
    BST e;
    e.runApp();
    return 0;
}