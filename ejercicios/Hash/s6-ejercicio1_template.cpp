#include<iostream>
#include<sstream>
#include<queue>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    public:
        TreeNode* invertTree(TreeNode* root){
            if (root != nullptr){
            TreeNode *temp = root->left;
            root->left = root->right;
            root->right =temp;
            if (root->left != nullptr ){
            invertTree(root->left);
            }
            if (root->right != nullptr){
                invertTree(root->right);
            }
        }
        return root;
    }
};

string bfs(TreeNode* root){
    if (root == nullptr){
        return "Arbol vacio";
    }else{
        stringstream ss;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()){
            TreeNode *node = q.front();
            q.pop();
            ss<<node->val;
            if (node->left != nullptr) q.push(node->left); 
            if (node->right != nullptr) q.push(node->right);
        }
        return ss.str();
    }
}

//https://leetcode.com/problems/invert-binary-tree/description/

int main(){
    //implementar
    //Input: root = [2,1,3]
    //Output: [2,3,1]

    return 0;
}