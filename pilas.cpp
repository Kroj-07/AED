/* estructura LIFO (Last In, First Out)

 implementar la función de deshacer/rehacer (Ctrl+Z) 
 Para evaluar expresiones matemáticas o el manejo de llamadas a funciones 

*/


#include <iostream>
using namespace std;

class Pila {
private:
    int datos[100];
    int tope;

public:
    Pila() {
        tope = -1;
    }

    bool estaVacia() {
        return tope == -1;
    }

    bool estaLlena() {
        return tope == 99;
    }

    void push(int valor) {
        if (estaLlena()) {
            cout << "Pila llena\n";
            return;
        }

        tope++;
        datos[tope] = valor;
    }

    int pop() {
        if (estaVacia()) {
            cout << "Pila vacia\n";
            return -1;
        }

        int valor = datos[tope];
        tope--;

        return valor;
    }

    int peek() {
        if (estaVacia()) {
            cout << "Pila vacia\n";
            return -1;
        }

        return datos[tope];
    }
};