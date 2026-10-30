#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

// (2^p) % MOD 
long long power2(int p) {
    long long res = 1;
    long long base = 2;
    while (p > 0) {
        if (p & 1) {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        p >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> color(n + 1, -1);
    int componentes = 0;

    for (int i = 1; i <= n; ++i) {
        if (color[i] == -1) {
            componentes++;
            color[i] = 0;
            queue<int> q;
            q.push(i);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        // Conflicto: Se detectó un ciclo impar
                        cout << "NO\n";
                        return 0;
                    }
                }
            }
        }
    }

    long long ans = power2(componentes);
    cout << "SI " << ans << "\n";

    return 0;
}