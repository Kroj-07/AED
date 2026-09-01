#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

string bfs(TreeNode* root){
    if (root == nullptr){
        return "Arbol vacio";
    } else {
        stringstream ss;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()){
            TreeNode *node = q.front();
            q.pop();
            ss << node->val << " ";
            if (node->left != nullptr) q.push(node->left); 
            if (node->right != nullptr) q.push(node->right);
        }
        return ss.str();
    }
}

#define MAX_STACK_SIZE 1000
struct Stack {
    TreeNode* stack1[MAX_STACK_SIZE];
    TreeNode* stack2[MAX_STACK_SIZE];
    int top;

    Stack(){ 
        top = -1; }

    bool isEmpty(){
        return top == -1;}

    bool isFull(){
        return top == MAX_STACK_SIZE - 1;
        }

    void push(TreeNode* p, TreeNode* q) {
        if(!isFull()) {
            stack1[++top]= p;
            stack2[top]= q;
        }
    }

    void pop(TreeNode*& p, TreeNode*& q) {
        if(!isEmpty()){
            p=stack1[top];
            q = stack2[top];
            top--;
        } else {
            p = nullptr;
            q = nullptr;
        }
    }
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        Stack stack;
        stack.push(p, q);
        while (!stack.isEmpty()) {
            TreeNode* node1;
            TreeNode* node2;
            stack.pop(node1, node2);

            if (!node1 && !node2){
                continue;}
            if (!node1 || !node2) {
                return false;}
            if (node1->val != node2->val){
                return false;}

            stack.push(node1->right,node2->right);
            stack.push(node1->left, node2->left);
        }
        return true;
    }
};

int main() {
    Solution sol;
    // arboles iguales
    TreeNode* a1 = new TreeNode(1,new TreeNode(2),new TreeNode(3));
    TreeNode* b1 = new TreeNode(1, new TreeNode(2), new TreeNode(3));

    cout<<"arbol A: "<< bfs(a1) << endl;
    cout<< "arbol B: "<< bfs(b1) << endl;
    cout<<"resultado: ";
    if(sol.isSameTree(a1, b1)) cout<< "son iguales"<< endl;
    else cout << "son diferentes"<< endl;
    cout << endl;

    //arboles con diferente estructura
    TreeNode* a2 = new TreeNode(1,new TreeNode(2),nullptr);
    TreeNode* b2 = new TreeNode(1,nullptr,new TreeNode(2));
    cout<<"arbol A: " <<bfs(a2)<< endl;
    cout<< "arbol B: " << bfs(b2)<< endl;   
    cout<<"resultado: ";
    if (sol.isSameTree(a2, b2)) cout << "son iguales" << endl;
    else cout << "son diferentes" << endl;
    cout << endl;

    //aboles con los mismos nodos y valores diferentes
    TreeNode* a3= new TreeNode(1,new TreeNode(2),new TreeNode(1));
    TreeNode* b3 =new TreeNode(1,new TreeNode(2),new TreeNode(3));
    cout<<"arbol A: " << bfs(a3) << endl;
    cout<< "arbol B: " << bfs(b3) << endl;
    cout<<"resultado: ";
    if (sol.isSameTree(a3, b3))cout << "son iguales" << endl;
    else cout << "son diferentes" << endl;
    return 0;
}
