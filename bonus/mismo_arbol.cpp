#include<bits/stdc++.h>
using namespace std;

struct Node{
    long long val;
    Node* left;
    Node* right;

    Node(long long val): val(val), left (nullptr), right(nullptr) {}
    
};

class BST{
    Node* insertRec(Node* node, int val){
    if(node==nullptr){
        return new Node(val);

    }
    if(val< node-> val){
        node-> left=insertRec(node ->left, val);
    }else if (val> node->val){
        node -> right=insertRec(node->right, val);}
        return node;
    }

    
   public:
   Node* root;

    BST(): root (nullptr){}

    void insert(int val){
        root=insertRec(root, val);
    }

};

bool sonIguales(Node* a, Node* b) {
    if (a ==nullptr && b== nullptr) return true;
    
    if (a== nullptr || b ==nullptr) return false;
    
    if (a->val != b->val) return false;

    return sonIguales(a->left, b->left) && sonIguales(a->right, b->right);
}



int main() {
    cin.tie(0) -> sync_with_stdio(false);

    int n, m;
    cin>>n>>m;
    
    vector<Node*> arbolesUnicos;
    vector<int> grupos;

    for(int i=0; i<m; i++){
        BST arbolActual;
        for (int j=0; j<n; j++){
            int x;
            cin>>x;
            arbolActual.insert(x);

        }

        int grupoEncontrado=-1;

        for (int k=0; k<arbolesUnicos.size(); k++){
            if(sonIguales(arbolActual.root, arbolesUnicos[k])){
                grupoEncontrado=k+1;
                break;
            }
        }

        if(grupoEncontrado==-1){
            arbolesUnicos.push_back(arbolActual.root);
            grupoEncontrado=arbolesUnicos.size();
        }

        grupos.push_back(grupoEncontrado);
    }

    cout<<arbolesUnicos.size()<<endl;
    for(int i=0; i<m; i++){
        cout<<grupos[i]<<(i==m-1 ? "" : " ");
    }

    cout<<endl;

return 0;
}