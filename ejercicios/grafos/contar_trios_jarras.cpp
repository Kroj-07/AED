#include <bits/stdc++.h>
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*int n, m;
    cin>>n>>m;


    vector<pair<int, int>> amistades;
    //matriz d adyacencia iniciado en false
    vector<vector<bool>> es_amigo(n+1, vector<bool>(n+1,  false));

    // 1. Leer y marcar TODAS las amistades
    for (int i=0; i<m; i++){
        int a, b;

        cin>> a>>b;
        amistades.push_back({a,b});
        es_amigo[a][b] = es_amigo[b][a] = true;

    }

    int trios=0;
    //marcar las amistades en la matriz
    for (auto& [a,b]: amistades){
        for(int c=0; c<=n; c++)
            if (es_amigo[a][c] && es_amigo[b][c]) {
                trios++;
            }

    }

    // 3. Cada triángulo se contó 3 veces
    cout <<trios/3<<endl;*/


    int A, B, x, y;
    if (!(cin >> A >> B >> x >> y)) return 0;

    int t_aristas = 0;
    int g_entrada = 0;

    // Func. auxiliar que procesa cada jugada válida
    auto probar_jugada = [&](int estado_a, int estado_b, int nuevo_a, int nuevo_b) {
        // Solo es una arista si el nuevo estado es DIFERENTE al actual
        if (nuevo_a != estado_a || nuevo_b != estado_b) {
            t_aristas++;
            if (nuevo_a == x && nuevo_b == y) {
                g_entrada++;
            }
        }
    };

    for (int a = 0; a <= A; ++a) {
        for (int b = 0; b <= B; ++b) {
            
            probar_jugada(a, b, A, b);

            probar_jugada(a, b, a, B);

            probar_jugada(a, b, 0, b);

            probar_jugada(a, b, a, 0);

            int v1 = min(a, B - b);
            probar_jugada(a, b, a - v1, b + v1);

            int v2 = min(b, A - a);
            probar_jugada(a, b, a + v2, b - v2);
        }
    }

    cout<<t_aristas << " " << g_entrada << "\n";

    return 0;
}

