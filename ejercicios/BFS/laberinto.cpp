#include <bits/stdc++.h>

using namespace std;

//Arriba, Abajo, Izquierda, Derecha
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    int start_r = -1, start_c = -1;

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S') {
                start_r = i;
                start_c = j;
            }
        }
    }

    // Matriz de distancias / visitados inicializada en -1
    vector<vector<int>> dist(n, vector<int>(m, -1));
    
    // Cola para el BFS (guarda coordenadas)
    queue<pair<int, int>> q;

    // Inicialización con el punto de origen
    dist[start_r][start_c] = 0;
    q.push({start_r, start_c});

    int respuesta = -1;

    // Bucle principal del BFS
    while (!q.empty()) {
        pair<int, int> actual = q.front();
        q.pop();

        int r = actual.first;
        int c = actual.second;

        //salida
        if (grid[r][c] == 'E') {
            respuesta = dist[r][c];
            break;
        }

        // vecinos
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            //dentro de límites, no es pared y no visitado
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    cout << respuesta << "\n";

    return 0;
}