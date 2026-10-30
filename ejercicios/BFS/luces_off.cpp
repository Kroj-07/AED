#include <bits/stdc++.h>

using namespace std;

// Direcciones 
const int dr[] = {0, -1, 1, 0, 0};
const int dc[] = {0, 0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int estado_inicial = 0;
    
    //Bitmask entero
    for (int r = 0; r < n; ++r) {
        string fila;
        cin >> fila;
        for (int c = 0; c < m; ++c) {
            if (fila[c] == '1') {
                int bit = r * m + c;
                estado_inicial |= (1 << bit);
            }
        }
    }

    // Precalcular las máscaras para cada casilla (r, c)
    // Presionar (r, c) invierte esa posición y sus vecinas válidas
    int total_casillas = n * m;
    vector<int> mascaras(total_casillas, 0);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            int casilla = r * m + c;
            for (int i = 0; i < 5; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    int bit_vecino = nr * m + nc;
                    mascaras[casilla] |= (1 << bit_vecino);
                }
            }
        }
    }

    // Estructuras para la BFS
    // Como n, m <= 4, el número máximo de estados es 2^16 = 65536
    vector<int> dist(1 << total_casillas, -1);
    queue<int> q;

    q.push(estado_inicial);
    dist[estado_inicial] = 0;

    int respuesta = -1;

    while (!q.empty()) {
        int actual = q.front();
        q.pop();

        if (actual == 0) {
            respuesta = dist[actual];
            break;
        }

        // Probar presionar cada una de las casillas
        for (int i = 0; i < total_casillas; ++i) {
            int siguiente = actual ^ mascaras[i]; // Aplicar cambio con XOR

            if (dist[siguiente] == -1) {
                dist[siguiente] = dist[actual] + 1;
                q.push(siguiente);
            }
        }
    }

    cout << respuesta << "\n";

    return 0;
}