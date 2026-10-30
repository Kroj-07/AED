#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

template <typename T, typename W = int>
class Grafo {
public:
    struct Arista {
        T destino;
        W peso;
    };

private:
    bool esDirigido;
    std::unordered_map<T, std::vector<Arista>> listaAdy;

public:
    // Constructor: por defecto es un grafo no dirigido
    Grafo(bool dirigido = false) : esDirigido(dirigido) {}

    // Agregar un vertice/nodo individual (util si no tiene aristas)
    void agregarVertice(const T& u) {
        if (listaAdy.find(u) == listaAdy.end()) {
            listaAdy[u] = std::vector<Arista>();
        }
    }

    // Agregar una arista con peso (por defecto peso = 1)
    void agregarArista(const T& u, const T& v, W peso = 1) {
        agregarVertice(u);
        agregarVertice(v);
        
        listaAdy[u].push_back({v, peso});
        if (!esDirigido) {
            listaAdy[v].push_back({u, peso});
        }
    }

    // Obtener los vecinos de un nodo
    const std::vector<Arista>& obtenerVecinos(const T& u) const {
        static const std::vector<Arista> vacio;
        auto it = listaAdy.find(u);
        return (it != listaAdy.end()) ? it->second : vacio;
    }

    // Obtener todos los vertices del grafo
    std::vector<T> obtenerVertices() const {
        std::vector<T> vertices;
        for (const auto& par : listaAdy) {
            vertices.push_back(par.first);
        }
        return vertices;
    }

    // Recorrido BFS (Busqueda en Anchura)
    void bfs(const T& inicio) const {
        if (listaAdy.find(inicio) == listaAdy.end()) return;

        std::unordered_map<T, bool> visitado;
        std::queue<T> q;

        q.push(inicio);
        visitado[inicio] = true;

        std::cout << "BFS desde " << inicio << ": ";
        while (!q.empty()) {
            T u = q.front();
            q.pop();
            std::cout << u << " ";

            for (const auto& arista : listaAdy.at(u)) {
                if (!visitado[arista.destino]) {
                    visitado[arista.destino] = true;
                    q.push(arista.destino);
                }
            }
        }
        std::cout << "\n";
    }

    // Algoritmo de Dijkstra para caminos minimos desde un nodo origen
    std::unordered_map<T, W> dijkstra(const T& origen) const {
        std::unordered_map<T, W> dist;
        for (const auto& par : listaAdy) {
            dist[par.first] = std::numeric_limits<W>::max();
        }

        if (listaAdy.find(origen) == listaAdy.end()) return dist;

        // Min-heap de pares: {distancia, nodo}
        using Par = std::pair<W, T>;
        std::priority_queue<Par, std::vector<Par>, std::greater<Par>> pq;

        dist[origen] = 0;
        pq.push({0, origen});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (const auto& arista : listaAdy.at(u)) {
                if (dist[u] + arista.peso < dist[arista.destino]) {
                    dist[arista.destino] = dist[u] + arista.peso;
                    pq.push({dist[arista.destino], arista.destino});
                }
            }
        }
        return dist;
    }

    // Imprimir representacion simple del grafo
    void imprimir() const {
        for (const auto& [nodo, vecinos] : listaAdy) {
            std::cout << nodo << " -> ";
            for (const auto& a : vecinos) {
                std::cout << "(" << a.destino << ", peso: " << a.peso << ") ";
            }
            std::cout << "\n";
        }
    }
};