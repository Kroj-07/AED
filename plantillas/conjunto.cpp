/*  verificar de forma rápida si un elemento ya existe en la colección
Cuando el orden o la duplicidad de los datos no está permitida
*/

#include <iostream>
using namespace std;

class Conjunto {
private:
    int datos[100];
    int cantidad;

public:
    Conjunto() {
        cantidad = 0;
    }

    bool pertenece(int valor) {
        for (int i = 0; i < cantidad; i++) {
            if (datos[i] == valor) {
                return true;
            }
        }

        return false;
    }

    void insertar(int valor) {
        if (cantidad == 100) {
            return;
        }

        if (!pertenece(valor)) {
            datos[cantidad] = valor;
            cantidad++;
        }
    }

    void eliminar(int valor) {
        for (int i = 0; i < cantidad; i++) {

            if (datos[i] == valor) {

                for (int j = i; j < cantidad - 1; j++) {
                    datos[j] = datos[j + 1];
                }

                cantidad--;
                return;
            }
        }
    }

    void mostrar() {
        cout << "{ ";

        for (int i = 0; i < cantidad; i++) {
            cout << datos[i] << " ";
        }

        cout << "}" << endl;
    }
};

int main() {

    Conjunto A;

    A.insertar(10);
    A.insertar(20);
    A.insertar(30);
    A.insertar(20);

    A.mostrar();

    cout << A.pertenece(20) << endl; // 1
    cout << A.pertenece(50) << endl; // 0

    A.eliminar(20);

    A.mostrar();

    return 0;
}