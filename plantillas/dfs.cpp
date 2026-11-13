#include <iostream>
#include <vector>
#include <stack>
#include <utility> // Para std::pair

using namespace std;

void dfs_iterativo(int s, const vector<vector<int>>& adj, 
                   vector<int>& tin, vector<int>& tout, 
                   vector<int>& padre, int& t) {
    
    stack<pair<int, int>> P;

    // Entramos al nodo raíz s
    tin[s] = t++;
    P.push({s, 0}); // Guardamos (vértice s, vecino índice 0)

    while (!P.empty()) {
        auto& top_pair = P.top(); 
        int u = top_pair.first;
        int i = top_pair.second;

        // ¿Todavía tiene vecinos pendientes u?
        if (i < adj[u].size()) {
            // Avanzamos el contador de vecino en la pila para la siguiente vuelta
            P.top().second = i + 1; 

            int v = adj[u][i]; // Obtenemos el vecino actual

            // Si el vecino v no ha sido visitado (tin[v] == -1)
            if (tin[v] == -1) {
                padre[v] = u;
                tin[v] = t++;
                P.push({v, 0}); // Apilamos a v para profundizar inmediatamente
            }
        } else {
            // u ya no tiene más vecinos por explorar: TERMINÓ
            tout[u] = t++;
            P.pop(); // Sacamos u de la pila definitivamente
        }
    }
}