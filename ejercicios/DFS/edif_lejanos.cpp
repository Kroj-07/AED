#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Lista de adyacencia global para facilitar la recursión del DFS.
// Guarda pares: {nodo_vecino, peso_del_camino}
vector<vector<pair<int, long long>>> adj;

// Variables globales para rastrear el nodo más lejano y la distancia máxima en cada DFS
long long max_dist;
int nodo_mas_lejano;

// =========================================================================
// BÚSQUEDA EN PROFUNDIDAD (DFS) EN ÁRBOLES
// =========================================================================
// Como el grafo es un árbol (conexión única sin ciclos), no necesitamos un arreglo
// de 'visitados'; basta con pasar el nodo 'padre' para no retroceder por la misma arista.
void dfs(int u, int padre, long long dist_actual) {
    if (dist_actual > max_dist) {
        max_dist = dist_actual;
        nodo_mas_lejano = u;
    }

    for (auto& arista : adj[u]) {
        int v = arista.first;
        long long peso = arista.second;
        if (v != padre) {
            dfs(v, u, dist_actual + peso);
        }
    }
}

int main() {
    // Optimización de lectura/escritura rápida (crucial para n = 200,000)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Caso base: si hay un solo edificio, la mayor distancia es 0
    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }

    adj.resize(n + 1);

    // =========================================================================
    // 1. LECTURA DEL ÁRBOL
    // =========================================================================
    // Un árbol con n nodos siempre tiene exactamente n - 1 aristas.
    // Nota sobre tipos de datos: La suma de hasta 2*10^5 caminos de longitud 10^9
    // puede llegar a ~2*10^14, lo que desborda un 'int' (límite ~2*10^9).
    // Por eso es obligatorio usar 'long long'.
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // =========================================================================
    // 2. ALGORITMO PRINCIPAL: DIÁMETRO DE UN ÁRBOL (DOBLE DFS / DOBLE BFS)
    // =========================================================================
    // ¿De qué trata el problema?
    // Nos piden hallar el "Diámetro del Árbol": el camino simple más largo entre
    // dos nodos cualesquiera.
    //
    // ¿Por qué no usar Dijkstra/DFS desde TODOS los nodos como en el problema B?
    // Porque aquí n <= 2*10^5. Hacer n recorridos tomaría O(n^2) ≈ 4*10^10 operaciones
    // y daría Time Limit Exceeded (TLE).
    //
    // Propiedad matemática de los árboles:
    // Si empiezas en CUALQUIER nodo (ej. el nodo 1) y buscas el nodo más lejano (A),
    // ese nodo A está garantizado a ser uno de los extremos del diámetro.
    // Luego, si buscas el nodo más lejano desde A (llamémoslo B), la distancia
    // entre A y B es exactamente el diámetro del árbol. Complejidad: O(n).

    // Paso 1: Encontrar un extremo del diámetro (nodo A) empezando desde el nodo 1
    max_dist = -1;
    nodo_mas_lejano = 1;
    dfs(1, 0, 0);
    int extremo_A = nodo_mas_lejano;

    // Paso 2: Encontrar el otro extremo (nodo B) y la distancia máxima empezando desde A
    max_dist = -1;
    dfs(extremo_A, 0, 0);

    cout << max_dist << "\n";

    return 0;
}

/* ============================================================================
 * GUÍA DE REUTILIZACIÓN: ¿Para qué otros ejercicios te sirve este código?
 * ============================================================================
 * 1. Diámetro de un árbol (ponderado o no ponderado):
 *    - Cualquier problema que diga "red sin ciclos", "n nodos y n-1 aristas",
 *      "único camino entre dos puntos" y pida la máxima distancia o el recorrido
 *      más largo posible.
 * 
 * 2. Encontrar el Centro de un Árbol (Minimizar la distancia máxima):
 *    - Si te piden ubicar un servidor o estación en un árbol para minimizar el
 *      tiempo hacia el nodo más lejano, el centro siempre se encuentra exactamente
 *      en la mitad del camino del diámetro (entre extremo_A y extremo_B).
 * 
 * 3. Distancia máxima desde CADA nodo del árbol (Tree Distances):
 *    - Una propiedad derivada de este algoritmo es que el nodo más lejano a
 *      CUALQUIER vértice 'u' del árbol siempre será extremo_A o extremo_B.
 *      Guardando las distancias desde A y desde B en dos arreglos, la máxima
 *      distancia desde cualquier nodo 'u' es simplemente max(distA[u], distB[u]).
 * 
 * Nota sobre variantes:
 * - Si los pesos de las aristas son todos 1 (árbol no ponderado), este mismo código
 *   funciona pasando peso = 1, o puedes usar un BFS doble.
 * - Si el árbol puede tener pesos NEGATIVOS, el truco del doble DFS deja de
 *   funcionar y debes usar Programación Dinámica en Árboles (Tree DP).
 * ============================================================================ */