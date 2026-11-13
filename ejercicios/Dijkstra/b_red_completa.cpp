#include <bits/stdc++.h>


using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long P, Q, M;
    if (!(cin >> n >> P >> Q >> M)) return 0;

    // Caso borde explícito del enunciado
    if (n == 1) {
        cout << "0 0\n";
        return 0;
    }

    // =========================================================================
    // 1. FUNCIÓN GENERADORA DE PESOS AL VUELO (Grafo Implícito / Denso)
    // =========================================================================
    // ¿Por qué NO guardamos el grafo en una lista o matriz de adyacencia?
    // Porque con n = 10^4 hay n*(n-1)/2 ≈ 5*10^7 aristas. Guardarlas gastaría
    // demasiada memoria/tiempo y usar priority_queue haría O(n^2 log n) ≈ 1.3*10^9 ops (TLE).
    // En su lugar, calculamos el peso w(u, v) matemáticamente solo cuando lo necesitamos.
    // ¡Ojo! Usamos 'long long' porque (i * j * Q) puede llegar a 10^4 * 10^4 * 10^9 = 10^17.
    auto obtener_peso = [&](long long u, long long v) -> long long {
        if (u > v) swap(u, v); // La fórmula asume i < j, y el grafo es bidireccional
        return ((u + v) * P + u * v * Q) % M + 1;
    };

    // =========================================================================
    // 2. ALGORITMO PRINCIPAL: DIJKSTRA SIN COLA DE PRIORIDAD O(n^2)
    // =========================================================================
    // ¿De qué trata el problema?
    // Es un grafo COMPLETO (todos conectados con todos, E ≈ V^2).
    // Para grafos densos, el Dijkstra clásico con arreglo lineal busca el mínimo
    // no visitado en O(n) por cada uno de los n pasos -> Total: O(n^2).
    // Con n = 10^4, n^2 = 10^8 operaciones simples, que corren en ~0.15 segundos.
    //
    // Además, maneja DESEMPATE LEXICOGRÁFICO: queremos minimizar:
    //   1° criterio: tiempo total mínimo (dist[v])
    //   2° criterio: menor cantidad de carreteras usadas (tramos[v])

    vector<long long> dist(n + 1, INF);
    vector<int> tramos(n + 1, 1e9);
    vector<bool> visitado(n + 1, false);

    dist[1] = 0;
    tramos[1] = 0;

    for (int iter = 1; iter <= n; ++iter) {
        // Paso A: Buscar linealmente el nodo no visitado con menor (dist, tramos)
        int u = -1;
        for (int i = 1; i <= n; ++i) {
            if (!visitado[i]) {
                if (u == -1 || dist[i] < dist[u] || (dist[i] == dist[u] && tramos[i] < tramos[u])) {
                    u = i;
                }
            }
        }

        // Si no quedan nodos alcanzables o ya fijamos el destino 'n', terminamos
        if (u == -1 || u == n) break;
        visitado[u] = true;

        // Paso B: Relajar todos los vecinos 'v' (en un grafo completo, son todos los demás nodos)
        for (int v = 1; v <= n; ++v) {
            if (!visitado[v]) {
                long long w = obtener_peso(u, v);
                long long nueva_dist = dist[u] + w;
                int nuevos_tramos = tramos[u] + 1;

                // Actualizamos si encontramos un tiempo estrictamente menor,
                // O si empatamos en tiempo pero usamos menos carreteras.
                if (nueva_dist < dist[v] || (nueva_dist == dist[v] && nuevos_tramos < tramos[v])) {
                    dist[v] = nueva_dist;
                    tramos[v] = nuevos_tramos;
                }
            }
        }
    }

    cout << dist[n] << " " << tramos[n] << "\n";

    return 0;
}

/* ============================================================================
 * GUÍA DE REUTILIZACIÓN: ¿Para qué otros ejercicios te sirve este código?
 * ============================================================================
 * 1. Grafos Densos o Completos (n <= 5000 - 10000, m ≈ n^2):
 *    - Problemas de geometría donde cada punto en el plano 2D está conectado con
 *      todos los demás y el costo es la distancia Euclidiana o Manhattan.
 *    - Cuando E ≈ V^2, Dijkstra con arreglo O(V^2) SIEMPRE es más rápido que
 *      Dijkstra con priority_queue O(V^2 log V).
 * 
 * 2. Caminos mínimos con criterios de desempate (Tuplas de costo):
 *    - Muy común en concursos: "minimiza el costo; en caso de empate, minimiza
 *      el número de transbordos / peajes / aristas". Se resuelve guardando dos
 *      arreglos paralelos (o un `pair<long long, int>`) y comparando lexicográficamente.
 * ============================================================================ */