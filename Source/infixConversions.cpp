#include <iostream>
#include <math.h>
using namespace std;

string infixPostfix(string);

struct Element{
    int element;
    Element *next;

    Element(int element){
        this->element = element;
        next = NULL;
    }
};

struct CharElement{
    char element;
    Element *next;

    CharElement(char element){
        this->element = element;
        next = NULL;
    }
};

class Stack{
    Element *top;

public:
    Stack(){
        top = NULL;
    }

    void push(int data){
        Element *node = new Element(data);
        node->next = top;
        top = node;
    }

    int pop(){
        int temp = -1;
        if (top != NULL){
            temp = top->element;
            top = top->next;
        }
        return temp;
    }

    bool isEmpty(){
        if (!top){
            return false;
        }
        return true;
    }

};

class StackChar{
    Element *top;

public:
    StackChar(){
        top = NULL;
    }

    void push(char data){
        Element *node = new Element(data);
        node->next = top;
        top = node;
    }

    char pop(){
        if(top != NULL){
            int temp = -1;
            if (top != NULL){
                temp = top->element;
                top = top->next;
            }
            return temp;
        }
        else{
            return -1;
        }

    }

    bool isEmpty(){
        if (top == NULL){
            return false;
        }
        return true;
    }

    char getTop(){
        return top->element;
    }
};

int postfixEval(string s){
    Stack stack;
    int op1, op2;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9'){
            stack.push(s[i] - '0');
        } else{
            op1 = stack.pop();
            op2 = stack.pop();

            switch (s[i]) {
                case '+':
                    stack.push(op1+op2);
                    break;
                case '-':
                    stack.push(op1-op2);
                    break;
                case '*':
                    stack.push(op1*op2);
                    break;
                case '/':
                    stack.push(op1/op2);
                    break;
                case '^':
                    stack.push(pow(op1,op2));
                    break;
                default:
                    break;
            }
        }
    }
    return stack.pop();
}

int prefixEval(string s){
    Stack stack;
    char op1, op2;
    for (int i = s.length()-1; i >= 0; i--) {
        if (s[i] >= '0' && s[i] <= '9'){
            stack.push(s[i]-'0');
        }
        else{
            op1 = stack.pop();
            op2 = stack.pop();

            switch (s[i]) {
                case '+':
                    stack.push(op1+op2);
                    break;
                case '-':
                    stack.push(op1-op2);
                    break;
                case '*':
                    stack.push(op1*op2);
                    break;
                case '/':
                    stack.push(op1/op2);
                    break;
                case '^':
                    stack.push(pow(op1,op2));
                    break;
                default:
                    break;
            }
        }
    }

    return stack.pop();
}

int prec(char c){
    switch (c) {
        case '^':
            return 3;
        case '+' :
            return 1;
        case '-' :
            return 1;
        case '/' :
            return 2;
        case '*':
            return 2;
        default:
            return -1;
    }
}

string infixPrefix(string s){
    StackChar stack;
    string result;
    for (int i = 0; i < s.length(); i++) {
        stack.push(s[i]);
    }
    result = "";
    for (int i = 0; i < s.length(); i++) {
         result += stack.pop();
    }
    s = result;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '('){
            s[i] = ')';
        } else if(s[i] == ')'){
            s[i] = '(';
        }
    }

    s = infixPostfix(s);

    for (int i = 0; i < s.length(); i++) {
        stack.push(s[i]);
    }
    result = "";
    for (int i = 0; i < s.length(); i++) {
        result += stack.pop();
    }
    return result;
}

string infixPostfix(string s){
    StackChar stack;
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])){
            result += s[i];
        } else if (s[i] == '('){
            stack.push(s[i]);
        }
        else if(s[i] == ')'){
            while (stack.getTop() != '(') {
                result += stack.pop();
            }

            if (!stack.isEmpty()){
                stack.pop();
            }

        } else{
            if ((!stack.isEmpty()) && prec(stack.getTop()) > prec(s[i])){
                result += stack.pop();
            }
            stack.push(s[i]);
        }
    }

    while (!stack.isEmpty()){
        result += stack.pop();
    }

    return result;
}

void runApp(){
    int input = -1;
    string temp;
    while(input != 0){
        cout<<"1. Infix to Postfix Expression"<<endl;
        cout<<"2. Prefix Evaluation Expression"<<endl;
        cout<<"3. Postfix Evaluation Expression"<<endl;
        cin>>input;
        switch (input) {
            case 1:
                cout<<"Enter the Infix Expression"<<endl;
                cin>>temp;
                cout<<infixPostfix(temp)<<endl;
                break;
            case 2:
                cout<<"Enter the Prefix Expression"<<endl;
                cin>>temp;
                cout<<prefixEval(temp)<<endl;
                break;
            case 3:
                cout<<"Enter the Postfix Expression"<<endl;
                cin>>temp;
                cout<<postfixEval(temp)<<endl;
                break;
        }
    }
}

int main() {
//    prefixEval : -+7*45+20 = 25;
//    postfixEval : 42*3+ = 11;
//    infixPostfix : ((a*b)+c) = ab*c+;
    cout<<infixPostfix("(c+(b*a))")<<endl;
    cout<<infixPrefix("((a*b)+c)");
//    runApp();
    return 0;
}
