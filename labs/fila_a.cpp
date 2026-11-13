#include<bits/stdc++.h>
using namespace::std;


/*
Group Ejemplos: 0.0 point(s)
    Test 1: OK
    Test 2: WRONG_ANSWER
Group Grupo1: 0.0 point(s)
    Test 3: OK
    Test 4: WRONG_ANSWER
    Test 5: OK
    Test 6: OK
Group Grupo2: 0.0 point(s)
    Test 7: OK
    Test 8: WRONG_ANSWER
    Test 9: OK
    Test 10: WRONG_ANSWER
    Test 11: OK
    Test 12: OK
    Test 13: WRONG_ANSWER
    Test 14: WRONG_ANSWER
    Test 15: OK
Group Grupo3: 0.0 point(s)
    Test 16: OK
    Test 17: WRONG_ANSWER
    Test 18: WRONG_ANSWER
    Test 19: WRONG_ANSWER
    Test 20: WRONG_ANSWER
    Test 21: OK

=
Points: 0.0*/

int main(){
    cin.tie(0) -> sync_with_stdio(false);

    int n, m;
    cin >>n>>m;
    
    vector<vector<int>> grafo(n + 1);
    for (int i=1; i<=m; i++ ){
        int p, q;
        cin>>p>>q;
        grafo[p].push_back(q);
        grafo[q].push_back(p);     
    }

    if (m != n - 1){
        cout<<"NO"<<'\n';
        return 0;
    }

    for (int i=1; i<=n; i++){
        if(grafo[i].size()>2){
            cout<<"NO"<<'\n';
            return 0;
        }
    }

    vector<bool> visitado(n + 1, false);
    queue<int> pendientes;
    pendientes.push(1);
    visitado[1] = true;
    int cantidadVisitados = 0;

    while (!pendientes.empty()){
        int actual = pendientes.front();
        pendientes.pop();
        cantidadVisitados++;

        for (int vecino : grafo[actual]){
            if (!visitado[vecino]){
                visitado[vecino] = true;
                pendientes.push(vecino);
            }
        }
    }

    if (cantidadVisitados != n){
        cout<<"NO"<<'\n';
        return 0;
    }

    cout<<"SI"<<endl;

return 0;

    
}