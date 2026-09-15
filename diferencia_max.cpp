/*Dado un arreglo de n enteros, encuentra el máximo valor de Aj−Ai
 tal que i<j
 (es decir, el mayor incremento posible entre un elemento y otro que aparece después de él en el arreglo). Si no existe ningún par (i,j)
 con i<j y Ai<Aj, imprime −1.

Input
La primera línea contiene un entero n
 — La cantidad de elementos del arreglo.

La segunda línea contiene n
 enteros a1,a2,…,an
 — El i-ésimo entero es el i-ésimo elemento del arreglo.

Output
Imprime un único entero — La diferencia máxima Aj−Ai
 con i<j, o −1
 si no existe ningún par (i,j) con Ai<Aj.

Este problema tiene subtareas, por lo cual es posible obtener un puntaje en base a las subtareas que logren ser resueltas.

2≤n≤10**5
1≤ai≤10**9 para todo i=1,…,n
.

2≤n≤1000
Grupo 2 (3 puntos)

Sin restricciones adicionales.
Example
InputCopy
6
7 1 5 3 6 4
OutputCopy
5
*/


#include <iostream>
using namespace std;


int *diferencia_max(int * b, int n){
    
}



int main(){

    cin>>n;
    int* b= new int[n]
    for (int i=0; i<n; i++){
        cin>>b[i];
    }

    diferencia_max(b,n)


    return 0;
}