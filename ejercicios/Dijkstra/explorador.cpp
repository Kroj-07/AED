#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

// ============================================================================
//DFS Recursivo + Lista de adyacencia con vector ordenado
// Complejidad: Tiempo O(n + m log m) | Espacio O(n + m)

void dfs_rec_vec_helper(int u, const vector<vector<int>>& adj, vector<bool>& vis, vector<int>& ans) {
    vis[u] = true;          // 1. Marcar cueva como visitada al entrar
    ans.push_back(u);       // 2. Registrar orden de primera visita

    for (int v : adj[u]) {  // 3. Como adj[u] ya está ordenado, recorre de menor a mayor
        if (!vis[v]) {
            dfs_rec_vec_helper(v, adj, vis, ans);
        }
    }
}

vector<int> dfs_recursivo_vector(int n, const vector<pair<int, int>>& aristas) {
    vector<vector<int>> adj(n + 1);
    for (auto [u, v] : aristas) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Ordenamos los vecinos de cada cueva de menor a mayor
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<bool> vis(n + 1, false);
    vector<int> ans;
    dfs_rec_vec_helper(1, adj, vis, ans);
    return ans;
}

// ============================================================================
// VARIANTE 2: DFS Recursivo + Lista de adyacencia con Min-Heap
// Complejidad: Tiempo O(n + m log m) | Espacio O(n + m)

using MinHeap = priority_queue<int, vector<int>, greater<int>>;

void dfs_rec_heap_helper(int u, vector<MinHeap>& adj, vector<bool>& vis, vector<int>& ans) {
    vis[u] = true;
    ans.push_back(u);

    // Extraemos los vecinos del heap (siempre entrega el menor disponible)
    while (!adj[u].empty()) {
        int v = adj[u].top();
        adj[u].pop();

        // Aunque lo saquemos de adj[u], otro nodo pudo haberlo visitado antes
        if (!vis[v]) {
            dfs_rec_heap_helper(v, adj, vis, ans);
        }
    }
}

vector<int> dfs_recursivo_heap(int n, const vector<pair<int, int>>& aristas) {
    vector<MinHeap> adj(n + 1);
    for (auto [u, v] : aristas) {
        adj[u].push(v);
        adj[v].push(u);
    }

    vector<bool> vis(n + 1, false);
    vector<int> ans;
    dfs_rec_heap_helper(1, adj, vis, ans);
    return ans;
}

// ============================================================================
// DFS Iterativo (Pila) + Lista de adyacencia con vector ordenado
// Complejidad: Tiempo O(n + m log m) | Espacio O(n + m)

vector<int> dfs_iterativo_vector(int n, const vector<pair<int, int>>& aristas) {
    vector<vector<int>> adj(n + 1);
    for (auto [u, v] : aristas) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Ordenamos de MAYOR a MENOR (rbegin/rend) porque la pila es LIFO:
    // al meter primero los mayores, los menores quedan arriba y salen primero.
    for (int i = 1; i <= n; i++) {
        sort(adj[i].rbegin(), adj[i].rend());
    }

    vector<bool> vis(n + 1, false);
    vector<int> ans;
    stack<int> st;

    st.push(1);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        // Regla de oro del DFS iterativo: marcar al SACAR de la pila, no al meter
        if (vis[u]) continue;
        vis[u] = true;
        ans.push_back(u);

        for (int v : adj[u]) {
            if (!vis[v]) {
                st.push(v);
            }
        }
    }

    return ans;
}

// ============================================================================
// DFS Iterativo (Pila) + Lista de adyacencia con Max-Heap
// Complejidad: Tiempo O(n + m log m) | Espacio O(n + m)
// ============================================================================
vector<int> dfs_iterativo_heap(int n, const vector<pair<int, int>>& aristas) {
    // Usamos priority_queue normal (Max-Heap) por el mismo principio LIFO:
    // sacamos primero los vecinos más grandes para apilarlos al fondo,
    // dejando el vecino más pequeño en la cima de la pila 'st'.
    vector<priority_queue<int>> adj(n + 1);
    for (auto [u, v] : aristas) {
        adj[u].push(v);
        adj[v].push(u);
    }

    vector<bool> vis(n + 1, false);
    vector<int> ans;
    stack<int> st;

    st.push(1);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (vis[u]) continue;
        vis[u] = true;
        ans.push_back(u);

        while (!adj[u].empty()) {
            int v = adj[u].top();
            adj[u].pop();

            if (!vis[v]) {
                st.push(v);
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<pair<int, int>> aristas(m);
    for (int i = 0; i < m; i++) {
        cin >> aristas[i].first >> aristas[i].second;
    }

    // vector<int> ans = dfs_recursivo_vector(n, aristas);
    // vector<int> ans = dfs_recursivo_heap(n, aristas);
    vector<int> ans = dfs_iterativo_vector(n, aristas);
    // vector<int> ans = dfs_iterativo_heap(n, aristas);

    cout << ans.size() << "\n";
    for (int x : ans) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}