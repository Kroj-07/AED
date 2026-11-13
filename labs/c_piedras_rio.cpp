/*time limit per test2 seconds
memory limit per test256 megabytes
Valentina quiere cruzar un río saltando sobre n
 piedras alineadas, numeradas de 1
 a n
 de una orilla a la otra. Sobre cada piedra i
 hay un número ai
: si está parada en la piedra i
, puede dar un salto de exactamente ai
 piedras hacia la derecha (a la piedra i+ai
) o de exactamente ai
 piedras hacia la izquierda (a la piedra i−ai
), siempre que esa piedra exista.

Valentina empieza en la piedra 1
 y quiere llegar a la piedra n
. ¿Cuál es la menor cantidad de saltos?

Input
La primera línea contiene un entero n
 (2≤n≤2⋅105
).

La segunda línea contiene n
 enteros a1,a2,…,an
 (1≤ai≤n
).

Output
Imprime la menor cantidad de saltos para ir de la piedra 1
 a la piedra n
, o −1
 si no se puede llegar.*/



 //se tendria que usar bfs para recorrer el grafo y encontrar la menor cantidad de saltos
// se ahria un grafo donde cada piedra es un nodo y hay una arista entre dos piedras si se puede saltar de una a otra. Luego se aplicaria bfs para encontrar la menor cantidad de saltos desde la piedra 1 hasta la piedra n.

//detallando el codigo, se tendria que crear un vector de vectores para representar el grafo, donde cada piedra es un nodo y cada arista es una conexion entre dos piedras. Luego se aplicaria bfs para encontrar la menor cantidad de saltos desde la piedra 1 hasta la piedra n. Se tendria que usar una cola para almacenar los nodos a visitar y un vector para almacenar las distancias desde la piedra 1 hasta cada piedra. Al final se imprimiria la distancia desde la piedra 1 hasta la piedra n, o -1 si no se puede llegar.
 #include<bits/stdc++.h>
using namespace::std;

int main(){
    cin.tie(0) -> sync_with_stdio(false);


    int n;
    cin>>n;
    vector<vector<int>> grafo(n + 1);


    for(int i=0; i<n; i++){
        int a;
        cin>>a;
        if(i + a < n){
            grafo[i + 1].push_back(i + a + 1);
        }
        if(i - a >= 0){
            grafo[i + 1].push_back(i - a + 1);
        }
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : grafo[u]){
            if(dist[v] == -1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    cout << dist[n] << endl;





    return 0;
}