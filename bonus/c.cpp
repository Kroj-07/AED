#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> pre, post;
vector<int> post_pos;
vector<int> inorder_result;
bool posible = true;

void buildInorder(int pre_l, int pre_r, int post_l, int post_r) {
    if (!posible) return;

    if (pre_l > pre_r) return;

    if (pre_l == pre_r) {
        if (pre[pre_l] != post[post_l]) {
            posible = false;
            return;
        }
        inorder_result.push_back(pre[pre_l]);
        return;
    }

    if (pre[pre_l] != post[post_r]) {
        posible = false;
        return;
    }

    int izq_root = pre[pre_l + 1];
    int idx_post_izq = post_pos[izq_root];

    if (idx_post_izq < post_l || idx_post_izq >= post_r) {
        posible = false;
        return;
    }

    int izq_size = idx_post_izq - post_l + 1;
    
    if (pre_l + izq_size == pre_r) {
        posible = false;
        return;
    }

    buildInorder(pre_l + 1, pre_l + izq_size, post_l, idx_post_izq);
    inorder_result.push_back(pre[pre_l]);
    buildInorder(pre_l + izq_size + 1, pre_r, idx_post_izq + 1, post_r - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;

    pre.resize(n);
    post.resize(n);
    post_pos.assign(n + 1, -1);

    for (int i=0; i<n; i++) cin >> pre[i];
    for (int i=0; i<n; i++) {
        cin >> post[i];
        post_pos[post[i]] = i;
    }

    if (n % 2 == 0) {
        cout << "IMPOSIBLE\n";
        return 0;
    }

    buildInorder(0, n - 1, 0, n - 1);

    if (!posible || (int)inorder_result.size() != n) {
        cout << "IMPOSIBLE"<<endl;
    } else {
        for (int i = 0; i < n; ++i) {
            cout <<inorder_result[i]<< (i == n - 1 ? "" : " ");
        }
        cout <<endl;
    }

    return 0;
}