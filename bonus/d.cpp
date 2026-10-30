#include <bits/stdc++.h>
using namespace std;

struct Par {
    long long suma;
    int idx_izq;
    int ver_izq;
    int ver_der;

    bool operator>(const Par& o) const {
        if (suma != o.suma)
          return suma > o.suma;
        return idx_izq > o.idx_izq;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<long long> val(n);
    vector<int> left_neighbor(n), right_neighbor(n);
    vector<int> version(n, 0);
    vector<bool> alive(n, true);

    for (int i = 0; i < n; ++i) {
        cin >> val[i];
        left_neighbor[i] =i - 1;
        right_neighbor[i]= i + 1;
    }
    right_neighbor[n - 1] = -1;

    priority_queue<Par, vector<Par>, greater<Par>> pq;

    for (int i = 0; i < n - 1; i++) {
        pq.push({val[i] + val[i + 1], i, version[i], version[i + 1]});
    }

    int bloques_actuales=n;

    while (bloques_actuales > k) {
        Par top = pq.top();
        pq.pop();

        int u = top.idx_izq;
        int v = right_neighbor[u];

        if (v == -1 || !alive[u] || !alive[v]) continue;
        if (version[u] != top.ver_izq || version[v] != top.ver_der) continue;

        val[u] += val[v];
        alive[v] = false;
        version[u]++;

        int nxt = right_neighbor[v];
        right_neighbor[u] = nxt;
        if (nxt != -1) {
            left_neighbor[nxt]= u;
        }

        bloques_actuales--;

        int prv=left_neighbor[u];
        if (prv != -1) {
            pq.push({val[prv] +val[u], prv, version[prv], version[u]});
        }
        if (nxt!= -1) {
            pq.push({val[u] + val[nxt], u, version[u], version[nxt]});
        }
    }

    int curr = 0;
    while (curr != -1 && !alive[curr]) curr++;

    vector<long long> resultado;
    while (curr != -1) {
        resultado.push_back(val[curr]);
        curr = right_neighbor[curr];
    }

    for (size_t i = 0; i < resultado.size(); i++) {
        cout << resultado[i] << (i + 1 == resultado.size() ? "" : " ");
    }
    cout <<endl;

    return 0;
}