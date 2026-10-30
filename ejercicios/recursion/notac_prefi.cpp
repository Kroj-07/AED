/*
Leer m
Leer la lista de m tokens

Crear una pila vacía de enteros de 64 bits (long long)

Para i desde m - 1 hasta 0 (recorrido de derecha a izquierda):
    token = lista[i]
    
    Si token es un número:
        convertir token a entero
        guardar en la pila
    Sino (es un operador +, - o *):
        A = sacar de la pila  (primer operando / lado izquierdo)
        B = sacar de la pila  (segundo operando / lado derecho)
        
        Si token == '+': resultado = A + B
        Si token == '-': resultado = A - B
        Si token == '*': resultado = A * B
        
        guardar resultado en la pila

El resultado final es el único elemento que queda en la pila
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int main() {
    // Optimización de entrada/salida rápida en C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    if (!(cin >> m)) return 0;

    vector<string> tokens(m);
    for (int i = 0; i < m; ++i) {
        cin >> tokens[i];
    }

    stack<long long> pila;

    // Recorremos de derecha a izquierda
    for (int i = m - 1; i >= 0; --i) {
        string t = tokens[i];

        // Verificamos si es un operador
        if (t == "+" || t == "-" || t == "*") {
            long long a = pila.top(); pila.pop();
            long long b = pila.top(); pila.pop();

            if (t == "+") pila.push(a + b);
            else if (t == "-") pila.push(a - b);
            else if (t == "*") pila.push(a * b);
        } else {
            // Es un número: lo convertimos a entero de 64 bits
            pila.push(stoll(t));
        }
    }

    // El tope de la pila contiene la respuesta final
    cout << pila.top() << "\n";

    return 0;
}