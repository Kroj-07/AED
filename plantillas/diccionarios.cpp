/* buscar, insertar y borrar datos rápidamente usando una etiqueta o nombre en lugar de un nmr.
std::map ordena las claves automáticamente; std::unordered_map es más rápido pero no mantiene un orden específico.
*/

#include <iostream>
#include <string>
using namespace std;

class Diccionario {
private:
    string claves[100];
    string valores[100];
    int cantidad;

public:
    Diccionario() {
        cantidad = 0;
    }

    void insertar(string clave, string valor) {
        for (int i = 0; i < cantidad; i++) {
            if (claves[i] == clave) {
                valores[i] = valor;
                return;
            }
        }

        if (cantidad < 100) {
            claves[cantidad] = clave;
            valores[cantidad] = valor;
            cantidad++;
        }
    }

    string buscar(string clave) {
        for (int i = 0; i < cantidad; i++) {
            if (claves[i] == clave) {
                return valores[i];
            }
        }

        return "No encontrado";
    }

    void eliminar(string clave) {
        for (int i = 0; i < cantidad; i++) {

            if (claves[i] == clave) {

                for (int j = i; j < cantidad - 1; j++) {
                    claves[j] = claves[j + 1];
                    valores[j] = valores[j + 1];
                }

                cantidad--;
                return;
            }
        }
    }
};