#include <iostream>
#include <stack>
#include <vector>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class Solution {
    public:
        TreeNode* convertBST(TreeNode* root) {
            std::stack<TreeNode*> st;
            TreeNode* curr = root;
            int sum = 0;
            while (curr || !st.empty()) {
                while (curr) {
                    st.push(curr);
                    curr = curr->right;
                }
                curr = st.top();
                st.pop();
                sum += curr->val;
                curr->val = sum;
                curr = curr->left;
            }
            return root;
        }
};

TreeNode* insertarBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        if (val < root->val) root->left = insertarBST(root->left, val);
        else root->right = insertarBST(root->right, val);
        return root;
    }
    void inOrder(TreeNode* root) {
        if (!root) return;
        inOrder(root->left);
        std::cout << root->val << " ";
        inOrder(root->right);
    }
    int main() {
    std::vector<int> datos = {4,1,6,0,2,5,7,3,8};
    TreeNode* raiz = nullptr;
    for (int x : datos) raiz = insertarBST(raiz, x);
    std::cout << "In-order original: ";
    inOrder(raiz);
    std::cout << '\n';
    Solution sol;
    sol.convertBST(raiz);
    std::cout << "In-order convertido: ";
    inOrder(raiz);
    std::cout << '\n';
    return 0;
}
