#include <bits/stdc++.h>


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

    int n, m, a, b;
    if (!(cin >> n >> m >> a >> b)) return 0;

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // =========================================================================
    // 1. DESCOMPOSICIÓN DEL CAMINO CON PARADAS INTERMEDIAS

    // Ir de 1 a n pasando por 'a' y 'b' en cualquier orden (permitiendo repetir
    // nodos/aristas). Como el grafo es no dirigido (bidireccional), solo hay
    // dos órdenes posibles de visita:
    //   Opción 1:  1 ---> a ---> b ---> n
    //   Opción 2:  1 ---> b ---> a ---> n
    //
    // Nota: Si el camino óptimo de 1 a 'b' ya pasa por 'a' en el medio, la
    // Opción 1 (1 -> a -> b -> n) lo cubrirá automáticamente con el mismo costo
    // mínimo, porque dist(1, a) + dist(a, b) == dist(1, b).
    //
    // Solo necesitamos ejecutar Dijkstra desde 'a' y desde 'b' (2 veces en total),
    // ya que al ser bidireccional, dist(1, a) == dist(a, 1) y dist(b, n) == dist(n, b).
    vector<long long> da = dijkstra(a, n, adj);
    vector<long long> db = dijkstra(b, n, adj);

    long long respuesta = INF;

    // Evaluar Opción 1: 1 -> a -> b -> n
    if (da[1] != INF && da[b] != INF && db[n] != INF) {
        respuesta = min(respuesta, da[1] + da[b] + db[n]);
    }

    // Evaluar Opción 2: 1 -> b -> a -> n
    if (db[1] != INF && db[a] != INF && da[n] != INF) {
        respuesta = min(respuesta, db[1] + db[a] + da[n]);
    }

    if (respuesta == INF) {
        cout << -1 << "\n";
    } else {
        cout << respuesta << "\n";
    }

    return 0;
}

/* ============================================================================
 * GUÍA DE REUTILIZACIÓN: ¿Para qué otros ejercicios te sirve este código?
 * ============================================================================
 * 1. Caminos con "Waypoints" o puntos de control obligatorios:
 *    - Si te piden ir de S a T pasando por K nodos obligatorios (donde K es 
 *      pequeño, ej. K <= 8), ejecutas Dijkstra desde S y desde cada uno de los
 *      K puntos, y luego pruebas las K! permutaciones posibles (`next_permutation`).
 * 
 * 2. ¿Qué pasa si el grafo fuera DIRIGIDO (unidireccional)?
 *    - En un grafo dirigido, dist(1, a) NO es igual a dist(a, 1). En ese caso,
 *      simplemente ejecutas un tercer Dijkstra desde el origen `d1 = dijkstra(1, ...)`
 *      y sumas `d1[a] + da[b] + db[n]`.
 * ============================================================================ */