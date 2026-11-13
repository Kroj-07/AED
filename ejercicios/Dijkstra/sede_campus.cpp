#include <bits/stdc++.h>


using namespace std;

// desbordamiento: la distancia máxima posible es n * w_max = 1000 * 10000 = 10^7,
const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    //lista de adyacencia porque el grafo es disperso (m <= 4000).
    // Nota: El enunciado indica que puede haber múltiples caminos entre el mismo par 
    // de edificios (multigrafo). La lista de adyacencia maneja esto naturalmente.
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        // Como los caminos son bidireccionales, agregamos la arista en ambos sentidos
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Variables para rastrear el edificio óptimo
    int mejor_edificio = -1;
    long long menor_suma = INF;

    // =========================================================================
    // 2.DIJKSTRA DESDE CADA NODO (All-Pairs Shortest Path)

    // Necesitamos hallar el "centro de gravedad" o mediana de un grafo ponderado:
    // el nodo cuya suma de distancias mínimas hacia todos los demás sea la menor.
    //
    // Como n <= 1000 y m <= 4000, ejecutar Dijkstra desde cada uno de los n nodos
    // toma O(n * (m log n)), lo cual realiza aprox. 1000 * 4000 * 10 ≈ 4*10^7 operaciones.
    // Esto entra sobrado en el límite de 2 segundos (y es más rápido que Floyd-Warshall O(n^3)).
    
    for (int inicio = 1; inicio <= n; ++inicio) {
        vector<long long> dist(n + 1, INF);
        dist[inicio] = 0;

        // Cola de prioridad (Min-Heap) que ordena de menor a mayor distancia: {distancia_actual, nodo}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, inicio});

        while (!pq.empty()) {
            long long d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // Si ya encontramos un camino más corto a 'u' anteriormente, ignoramos este estado
            if (d > dist[u]) continue;

            // Relajación de aristas vecinas
            for (auto& arista : adj[u]) {
                int v = arista.first;
                int peso = arista.second;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pq.push({dist[v], v});
                }
            }
        }

        // =====================================================================
        // 3. EVALUACIÓN DE LA MÉTRICA DEL PROBLEMA
        long long suma_actual = 0;
        for (int j = 1; j <= n; ++j) {
            suma_actual += dist[j];
        }

        // Como iteramos 'inicio' de 1 a n en orden ascendente, usar estrictamente '<'
        // garantiza que, en caso de empate en la suma, nos quedemos con el edificio
        // de menor índice numérico (cumpliendo la regla de desempate del problema).
        if (suma_actual < menor_suma) {
            menor_suma = suma_actual;
            mejor_edificio = inicio;
        }
    }

    cout << mejor_edificio << " " << menor_suma << "\n";

    return 0;
}

/*
 * 1. Problemas de ubicación óptima / Facility Location:
 *    - Ejercicios donde piden poner algo minimizando el tiempo total de viaje o distancia promedio.
 * 
 * 2. Variaciones cambiando solo la sección 3 (Evaluación):
 *    - Excentricidad / Centro del grafo: Si en lugar de la SUMA te piden minimizar 
 *      la distancia MÁXIMA hacia cualquier otro nodo solo cambias `suma_actual += dist[j]` 
 *      por `max_actual = max(max_actual, dist[j])`.
 *    - Diámetro del grafo: Si buscas la distancia mínima más larga entre cualquier par 
 *      de nodos de toda la red.
 * 
 * 3. Grafos con múltiples fuentes o restricciones de alcance:
 *    - Contar cuántos nodos están a menos de X minutos de cada vértice.
 * 
 * Nota sobre restricciones:
 * - Si los pesos de las aristas fueran todos iguales (o 1), reemplaza Dijkstra por un BFS simple.
 * - Si n <= 400 y el grafo es muy denso (muchas aristas), Floyd-Warshall es más corto de escribir.
 * - Si hubiera pesos negativos (sin ciclos negativos), cambia Dijkstra por Bellman-Ford.
 * ============================================================================ */