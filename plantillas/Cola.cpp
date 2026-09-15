/*estructura FIFO (First In, First Out)
simular filas de espera del mundo real
En la administración de tareas o procesos en un sistema operativo
*/

#include <iostream>
using namespace std;

class Cola {
private:
    int datos[1000];
    int frente;
    int final;

public:
    Cola() {
        frente = 0;
        final = -1;
    }

    bool estaVacia() {
        return frente > final;
    }

    bool estaLlena() {
        return final == 999;
    }

    void enqueue(int valor) {
        if (estaLlena()) {
            cout << "Cola llena\n";
            return;
        }

        final++;
        datos[final] = valor;
    }

    int dequeue() {
        if (estaVacia()) {
            cout << "Cola vacia\n";
            return -1;
        }

        int valor = datos[frente];
        frente++;

        return valor;
    }

    int peek() {
        if (estaVacia()) {
            cout << "Cola vacia\n";
            return -1;
        }

        return datos[frente];
    }
};