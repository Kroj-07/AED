#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;

vector<long long> dijkstra(int inicio, int n, const vector<vector<pair<int, long long>>>& adj) {
    vector<long long> dist(n + 1, INF);
    dist[inicio] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, inicio});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& arista : adj[u]) {
            int v = arista.first;
            long long peso = arista.second;
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // =========================================================================
    // 1. GRAFO NORMAL Y GRAFO INVERTIDO (TRANSPUESTO)

    // Necesitamos el camino mínimo de 1 -> v (ida) y de v -> 1 (regreso) en un
    // grafo DIRIGIDO.
    // - La ida (1 -> v) la resuelve un Dijkstra desde 1 en el grafo original.
    // - El regreso (v -> 1 para todo v) se resuelve con UN SOLO Dijkstra desde 1
    //   en el GRAFO INVERTIDO (invirtiendo cada arista u -> v en v -> u).
    // Esto reduce N ejecuciones de Dijkstra a solo 2 ejecuciones: O(m log n).
    vector<vector<pair<int, long long>>> adj_ida(n + 1);
    vector<vector<pair<int, long long>>> adj_regreso(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj_ida[u].push_back({v, w});      // Arista original: u -> v
        adj_regreso[v].push_back({u, w});  // Arista invertida: v -> u
    }

    vector<long long> dist_ida = dijkstra(1, n, adj_ida);
    vector<long long> dist_regreso = dijkstra(1, n, adj_regreso);

    // =========================================================================
    // 2. CONTEO Y SUMA TOTAL DE CIUDADES ATENDIDAS
    int atendidas = 0;
    long long suma_total = 0;

    for (int v = 1; v <= n; ++v) {
        // Solo se atiende si tanto la ida como el regreso son posibles
        if (dist_ida[v] != INF && dist_regreso[v] != INF) {
            atendidas++;
            suma_total += dist_ida[v] + dist_regreso[v];
        }
    }

    cout << atendidas << " " << suma_total << "\n";

    return 0;
}

/* ============================================================================
 * GUÍA DE REUTILIZACIÓN: ¿Para qué otros ejercicios te sirve este código?
 * ============================================================================
 * 1. "Todos hacia un destino T" en grafos dirigidos (Single-Destination Shortest Path):
 *    - Siempre que un grafo sea DIRIGIDO y te pidan distancias mínimas DESDE 
 *      múltiples orígenes HACIA un único destino T, invierte las aristas y corre
 *      un solo Dijkstra (o BFS) desde T.
 * 2. Problemas clásicos de "Invitation Cards" / "Cow Party":
 *    - Exactamente este patrón: ida desde un hub central y vuelta hacia él.
 * ============================================================================ */