#include <vector>
using namespace std;

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
    void inOrder(TreeNode* root, vector<int>& valores) {
        if (!root) return;
        inOrder(root->left, valores);
        valores.push_back(root->val);
        inOrder(root->right, valores);
    }

    bool findTarget(TreeNode* root, int k) {
        vector<int> valores;
        inOrder(root, valores);
        int i = 0, j = valores.size() - 1;
        while (i < j) {
            int suma = valores[i] + valores[j];
            if (suma == k) return true;
            else if (suma < k) ++i;
            else --j;
        }
        return false;
    }
};


