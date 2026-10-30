#include<bits/stdc++.h>

using namespace std;

//estado dentro del BFS
struct State {
    int r, c, dir;
};

//0: Derecha, 1: Abajo, 2: Izquierda, 3: Arriba
const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // dist[r][c][dir] almacena la menor cantidad de acciones para llegar a esa posición y dirección
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(4, -1)));
    queue<State> q;

    // Estado inicial: (0, 0) mirando hacia la derecha (dir = 0)
    dist[0][0][0] = 0;
    q.push({0, 0, 0});

    int ans = -1;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        int r = curr.r;
        int c = curr.c;
        int dir = curr.dir;
        int d = dist[r][c][dir];

        // Si llegamos a la casilla de destino (n-1, m-1)
        if (r == n - 1 && c == m - 1) {
            ans = d;
            break;
        }

        // a la derecha (+1 a la dirección mod 4)
        int right_dir = (dir + 1) % 4;
        if (dist[r][c][right_dir] == -1) {
            dist[r][c][right_dir] = d + 1;
            q.push({r, c, right_dir});
        }

        //a la izquierda (+3 mod 4 es equivalente a -1 mod 4)
        int left_dir = (dir + 3) % 4;
        if (dist[r][c][left_dir] == -1) {
            dist[r][c][left_dir] = d + 1;
            q.push({r, c, left_dir});
        }

        // 3. Avanzar
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#') {
            if (dist[nr][nc][dir] == -1) {
                dist[nr][nc][dir] = d + 1;
                q.push({nr, nc, dir});
            }
        }
    }

    cout << ans << "\n";

    return 0;
}