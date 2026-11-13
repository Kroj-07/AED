#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> adj, adj_rev;
vector<bool> visitado;
vector<int> orden;

//calc orden de finalización (post-orden) para Kosaraju
void dfs1(int u) {
    visitado[u] = true;
    for (int v : adj[u]) {
        if (!visitado[v]) dfs1(v);
    }
    orden.push_back(u);
}

//recorre el grafo transpuesto para agrupar una Componente Fuertemente Conexa (SCC)
void dfs2(int u, int id_comp, vector<int>& comp) {
    comp[u] = id_comp;
    for (int v : adj_rev[u]) {
        if (comp[v] == -1) dfs2(v, id_comp, comp);
    }
}

//verifica si desde un candidato elegido se alcanza a TODOS los n nodos
int dfs_verificar(int u) {
    visitado[u] = true;
    int alcanzados = 1;
    for (int v : adj[u]) {
        if (!visitado[v]) {
            alcanzados += dfs_verificar(v);
        }
    }
    return alcanzados;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    adj_rev.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    // =========================================================================
    // 1. ALGORITMO DE KOSARAJU (Componentes Fuertemente Conexas - SCC)
    // Un nodo es "líder" (Mother Vertex) si llega a todos los demás en un grafo dirigido.
    // Propiedad clave de grafos dirigidos:
    //   - Si existe al menos un líder, el ÚLTIMO nodo que termina su recorrido en 
    //     el primer DFS de Kosaraju (`orden.back()`) ESTÁ GARANTIZADO a ser un líder.
    //   - Además, todos los nodos que pertenezcan a la MISMA Componente Fuertemente 
    //     Conexa (SCC) que ese líder también pueden llegar a él (y por transitividad, 
    //     a todos los demás), por lo que TODOS ellos son líderes (y nadie más).
    visitado.assign(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visitado[i]) dfs1(i);
    }

    // El último nodo en terminar el DFS1 es nuestro único candidato necesario
    int candidato = orden.back();

    // =========================================================================
    // 2. VERIFICACIÓN: ¿El candidato realmente llega a los 'n' servidores?
    // Si el grafo está desconectado (ej. ejemplo 2: 1->2 y 3->2), el candidato
    // no logrará visitar los n nodos.
    visitado.assign(n + 1, false);
    if (dfs_verificar(candidato) < n) {
        cout << 0 << "\n";
        return 0;
    }

    // =========================================================================
    // 3. CONTAR EL TAMAÑO DE LA SCC DEL CANDIDATO
    // Ejecutamos la segunda fase de Kosaraju para identificar qué nodos forman
    // un ciclo mutuo con el candidato. Complejidad total: O(n + m).
    vector<int> comp(n + 1, -1);
    int num_scc = 0;
    reverse(orden.begin(), orden.end());

    for (int u : orden) {
        if (comp[u] == -1) {
            dfs2(u, num_scc++, comp);
        }
    }

    int lideres = 0;
    for (int i = 1; i <= n; ++i) {
        if (comp[i] == comp[candidato]) {
            lideres++;
        }
    }

    cout << lideres << "\n";

    return 0;
}

/*
1. Mother Vertex (Vértice Madre):
 *    - Hallar uno o todos los vértices desde los cuales se puede alcanzar todo 
 *      un grafo dirigido en tiempo lineal O(n + m).
 * 2. Condensación de Grafos Dirigidos (SCC / Kosaraju):
 *    - Siempre que un grafo dirigido tenga ciclos y necesites agrupar nodos 
 *      mutuamente alcanzables en "supernodos" para convertir el grafo en un DAG 
 *      (Grafo Acíclico Dirigido). Por ejemplo: "¿Cuántas aristas mínimas debo 
 *      agregar para que todo el grafo sea fuertemente conexo?".
 * ============================================================================ */