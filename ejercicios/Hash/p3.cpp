#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    int D[128] = {0};
public:
    int hash(char c){
        return int(c);
    }

    void insert(char c, char d){
        D[hash(d)]++;
    }

    int get(char d){
        return D[hash(d)];
    }

    void reset() {
        for (int i = 0; i < 128; i++)
            D[i] = 0;
    }
};

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        HashTable tabla;

        for (int fila = 0; fila < 9; ++fila) {
            tabla.reset();
            for (int columna = 0; columna < 9; ++columna) {
                char valor = board[fila][columna];
                if (valor == '.') continue;
                if (tabla.get(valor) > 0) return false;
                tabla.insert('F', valor);
            }
        }

        for (int columna = 0; columna < 9; ++columna) {
            tabla.reset();
            for (int fila = 0; fila < 9; ++fila) {
                char valor = board[fila][columna];
                if (valor == '.') continue;
                if (tabla.get(valor) > 0) return false;
                tabla.insert('C', valor);
            }
        }

        // Validamos las subcuadrículas de 3x3
        for (int bloque_f = 0; bloque_f < 3; ++bloque_f) {
            for (int bloque_c = 0; bloque_c < 3; ++bloque_c) {
                tabla.reset();
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        int fila = bloque_f * 3 + i;
                        int columna = bloque_c * 3 + j;
                        char valor = board[fila][columna];
                        if (valor == '.') continue;
                        if (tabla.get(valor) > 0) return false;
                        tabla.insert('B', valor);
                    }
                }
            }
        }

        return true;
    }
};