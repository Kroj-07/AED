#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right, *parent;
    Node(int v) : val(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

// ==================== F ====================
Node* insertF(Node* root, int val) {
    Node* newNode = new Node(val);
    if (!root) return newNode;
    Node* cur = root;
    Node* parent = nullptr;
    while (cur) {
        parent = cur;
        if (val < cur->val) cur = cur->left;
        else cur = cur->right;
    }
    newNode->parent = parent;
    if (val < parent->val) parent->left = newNode;
    else parent->right = newNode;
    return root;
}

Node* searchF(Node* root, int val) {
    while (root && root->val != val) {
        if (val < root->val) root = root->left;
        else root = root->right;
    }
    return root;
}

Node* minimumF(Node* node) {
    while (node->left) node = node->left;
    return node;
}

Node* maximumF(Node* node) {
    while (node->right) node = node->right;
    return node;
}

Node* successorF(Node* node) {
    if (node->right) return minimumF(node->right);
    Node* parent = node->parent;
    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

Node* predecessorF(Node* node) {
    if (node->left) return maximumF(node->left);
    Node* parent = node->parent;
    while (parent && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

void solveF() {
    int n;
    cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        root = insertF(root, x);
    }
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        Node* node = searchF(root, x);
        Node* pred = predecessorF(node);
        Node* succ = successorF(node);
        if (pred) cout << pred->val;
        else cout << "NONE";
        cout << ' ';
        if (succ) cout << succ->val;
        else cout << "NONE";
        cout << '\n';
    }
}

// ====================  G ====================
Node* insertG(Node* root, int val) {
    Node* newNode = new Node(val);
    if (!root) return newNode;
    Node* cur = root;
    Node* parent = nullptr;
    while (cur) {
        parent = cur;
        if (val < cur->val) cur = cur->left;
        else cur = cur->right;
    }
    newNode->parent = parent;
    if (val < parent->val) parent->left = newNode;
    else parent->right = newNode;
    return root;
}

Node* searchG(Node* root, int val) {
    while (root && root->val != val) {
        if (val < root->val) root = root->left;
        else root = root->right;
    }
    return root;
}

Node* transplantG(Node* root, Node* u, Node* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
    return root;
}

Node* treeMinimumG(Node* x) {
    while (x->left) x = x->left;
    return x;
}

Node* deleteG(Node* root, Node* z) {
    if (!z->left) {
        root = transplantG(root, z, z->right);
    } else if (!z->right) {
        root = transplantG(root, z, z->left);
    } else {
        Node* y = treeMinimumG(z->right);
        if (y->parent != z) {
            root = transplantG(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        root = transplantG(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    delete z;
    return root;
}

void inorderG(Node* root, vector<int>& res) {
    if (!root) return;
    inorderG(root->left, res);
    res.push_back(root->val);
    inorderG(root->right, res);
}

void solveG() {
    int m;
    cin >> m;
    Node* root = nullptr;
    string op;
    while (m--) {
        cin >> op;
        int x;
        cin >> x;
        if (op == "INSERTAR") {
            root = insertG(root, x);
        } else if (op == "ELIMINAR") {
            Node* z = searchG(root, x);
            if (z) root = deleteG(root, z);
        } else if (op == "EXISTE") {
            Node* z = searchG(root, x);
            cout << (z ? "SI" : "NO") << '\n';
        }
    }
    vector<int> res;
    inorderG(root, res);
    if (res.empty()) {
        cout << "VACIO\n";
    } else {
        for (size_t i = 0; i < res.size(); ++i) {
            if (i) cout << ' ';
            cout << res[i];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solveF();
    
    solveG();
    
    return 0;
}