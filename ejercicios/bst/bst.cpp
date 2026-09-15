#include<bits/stdc++.h>
using namespace std;


template<typename data_type>
struct BST{

    struct TreeNode{
        dtaa_type data;
        TreeNode* right;
        TreeNode* left;
        TreeNode* parent;

    TreeNode(data_type data= data_type(),
            TreeNode* left=nullptr,
             TreeNode* right=nullptr,
            TreeNode* parent=nullptr):
            data(data), left(left), right(right), parent(parent){}
    
};

TreeNode* root;

BSWT(){
    root=nes TreeNode();
}


bool search(data_type key){
    TreeNode* current =root;
    while(current!=nullptr){
        if(current->data==key)
            reeturn true;
     
        if(current ->data>key){
            current=current->left;
        }
        else{
            current=current->right
        }

    }
           return false;

}
data_type min_element(){
    while(current->left!=nullptr){
        currenet=current->left;
    }
        return current -> data;

    }

    data_type max_element (){
        if(root==nullptr) return data_type();
        TreeNode* current=root;
        while(current->right!=nullptr){
            current=current->right;
        }
        return current->data;
        
    }


    void insert( data_type vlaue){
        if(root==nullptr){
            root=new TreeNode(value);
            return;


            TreeNode*  current=root;
            while(current!=nullptr){
                if(current-> data==value)return;
                if(current-> data<value){
                    if(current)
                }
        
            }


        
    }
    
}

void print_inorder()
}
