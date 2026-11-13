#include <bits/stdc++.h>

using namespace std;

// La distancia máx posible es n * w_max = 2*10^5 * 10^9 = 2*10^14.
// Usamos 1e18 con long long para evitar desbordamientos.
const long long INF = 1e18;

// Recibe el grafo y un nodo 'inicio', y devuelve el vector con las distancias
// mínimas desde 'inicio' hacia todos los demás nodos (1 .. n).
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

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // Las carreteras son bidireccionales
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // =========================================================================
    // 1.DOBLE DIJKSTRA (Desde ambos orígenes)
    // Dos personas salen simultáneamente desde el nodo 1 y el nodo n, y quieren
    // encontrarse en una ciudad 'c' minimizando max(dist_1[c], dist_n[c]).
    //
    // En lugar de probar cada ciudad 'c' por separado, ejecutamos Dijkstra solo
    // DOS veces: una desde 1 y otra desde n. Con esos dos arreglos de distancias,
    // podemos evaluar cada candidato 'c' en O(1). Complejidad total: O(m log n).
    vector<long long> d1 = dijkstra(1, n, adj);
    vector<long long> dn = dijkstra(n, n, adj);

    // =========================================================================
    // 2. EVALUACIÓN DE TODOS LOS PUNTOS DE ENCUENTRO POSIBLES
    long long mejor_T = INF;
    int cantidad_ciudades = 0;

    for (int c = 1; c <= n; ++c) {
        // Ambas personas deben poder llegar a la ciudad 'c'
        if (d1[c] != INF && dn[c] != INF) {
            long long tiempo_encuentro = max(d1[c], dn[c]);

            if (tiempo_encuentro < mejor_T) {
                mejor_T = tiempo_encuentro;
                cantidad_ciudades = 1; // Reiniciamos contador al hallar un nuevo mínimo
            } else if (tiempo_encuentro == mejor_T) {
                cantidad_ciudades++;   // Sumamos otra ciudad que empata el mejor tiempo
            }
        }
    }

    if (mejor_T == INF) {
        cout << -1 << "\n";
    } else {
        cout << mejor_T << " " << cantidad_ciudades << "\n";
    }

    return 0;
}

/*
 * 1. "Meet in the Middle" en grafos (Puntos de encuentro / Rendezvous):
 *    - Dos amigos, dos robots o dos vehículos salen de puntos A y B y deben
 *      reunirse minimizando:
 *      * El tiempo de espera (max(dA[c], dB[c])) -> Este problema.
 *      * El gasto total de combustible combinado (dA[c] + dB[c]).
 * 
 * 2. Aristas críticas o "¿Esta arista pertenece a algún camino mínimo de A a B?":
 *    - Ejecutas Dijkstra desde A (dA) y desde B (dB). Una arista (u, v, w) está
 *      en un camino óptimo si y solo si: dA[u] + w + dB[v] == dA[B].
 * ============================================================================ */