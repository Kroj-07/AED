#include <bits/stdc++.h>


using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    if (!(cin >> n >> t)) return 0;

    // =========================================================================
    // 1. LECTURA DEL ÁRBOL
    // Como no nos dicen cuál de los dos nodos (u o v) es el jefe y cuál el 
    // subordinado, guardamos las n - 1 aristas como bidireccionales y enraizamos
    // el árbol empezando el recorrido desde el director (nodo 1).
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // =========================================================================
    // 2. BFS DESDE LA RAÍZ (1) PARA RECONSTRUIR EL CAMINO ÚNICO HASTA 't'

    // En un árbol existe un ÚNICO camino simple entre dos nodos cualesquiera.
    // Usamos BFS (o DFS iterativo) desde el nodo 1 para evitar desbordamiento de 
    // pila (Stack Overflow) si el árbol es una línea de 200,000 nodos.
    // Guardamos el arreglo 'padre[v]' para saber quién envió el comunicado a 'v'.
    vector<int> padre(n + 1, -1);
    vector<bool> visitado(n + 1, false);
    queue<int> q;

    q.push(1);
    visitado[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) break; // Ya encontramos al destinatario

        for (int v : adj[u]) {
            if (!visitado[v]) {
                visitado[v] = true;
                padre[v] = u;
                q.push(v);
            }
        }
    }

    // =========================================================================
    // 3. RECONSTRUCCIÓN DEL CAMINO EN REVERSA (De 't' hasta '1')
    vector<int> ruta;
    for (int curr = t; curr != -1; curr = padre[curr]) {
        ruta.push_back(curr);
    }
    reverse(ruta.begin(), ruta.end());

    cout << ruta.size() << "\n";
    for (int i = 0; i < (int)ruta.size(); ++i) {
        cout << ruta[i] << (i + 1 == (int)ruta.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}

/* ============================================================================
 * GUÍA DE REUTILIZACIÓN: ¿Para qué otros ejercicios te sirve este código?
 * ============================================================================
 * 1. Reconstrucción de caminos mínimos en grafos NO ponderados (BFS):
 *    - Cualquier laberinto 2D o grafo sin pesos donde te pidan imprimir la 
 *      secuencia exacta de pasos desde un inicio S hasta un destino T.
 * 2. Consultas de ancestros o jerarquías en árboles:
 *    - El arreglo `padre[]` generado por un BFS desde la raíz define la 
 *      estructura completa del árbol enraizado (profundidades, subárboles, etc.).
 * ============================================================================ */