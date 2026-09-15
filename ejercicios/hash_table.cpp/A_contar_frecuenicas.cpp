#include <bits/stdc++.h>

using namespace std;

template <typename key_type, typename value_type>
struct my_map {

    int m;
    vector<vector<pair<key_type, value_type>>> chains;

    my_map(int m) : m(m) {
        chains.resize(m);
    }

    value_type& operator[](const key_type& key) {

        int chain_position = _hash(key);
        int at = 0;

        // Buscar la clave
        while (
            at < (int)chains[chain_position].size() &&
            chains[chain_position][at].first != key
        ) {
            ++at;
        }

        // Si no existe, crearla
        if (at == (int)chains[chain_position].size()) {
            chains[chain_position].emplace_back(
                key,
                value_type()
            );

            // IMPORTANTE:
            // ahora el nuevo elemento está en la posición at
        }

        return chains[chain_position][at].second;
    }

    bool has_key(const key_type& key) const {

        int chain_position = _hash(key);
        int at = 0;

        while (
            at < (int)chains[chain_position].size() &&
            chains[chain_position][at].first != key
        ) {
            ++at;
        }

        return at != (int)chains[chain_position].size();
    }

private:

    int _hash(key_type key) const {

        // Para enteros
        const long long B = 311;
        const long long MOD = 1000000007LL;

        long long hash_value = 0;

        while (key > 0) {

            int d = key % 10;

            hash_value =
                (hash_value * B + (d + 1)) % MOD;

            key /= 10;
        }

        return hash_value % m;
    }

public:

    void print() {

        for (int i = 0; i < m; ++i) {

            cout << "Bucket " << i << ":" << endl;

            for (auto& e : chains[i]) {
                cout << e.first
                     << " --> "
                     << e.second
                     << endl;
            }

            cout << "End bucket" << endl;
        }
    }
};


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;

    cin >> n >> q;

    // Usamos 2*n buckets para reducir colisiones
    my_map<int, int> frecs(2 * n);

    // Leer arreglo y contar frecuencias
    for (int i = 0; i < n; ++i) {

        int x;
        cin >> x;

        ++frecs[x];
    }

    // Resolver consultas
    while (q--) {

        int x;
        cin >> x;

        cout << frecs[x] << '\n';
    }

    return 0;
}