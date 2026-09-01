#include <iostream>
using namespace std;

class HashTable {
private:
    int D[128];  
    int usado;    

public:
    HashTable(): usado(0) {
        for (int i = 0; i < 128; ++i) {
            D[i] = 0;
        }
    }

    int hash(int k) const {         
        if (k< 0) k = -k;
        return k % 128;
    }

    void insert(int k) {
        if (usado< 128) {
            D[usado++] = k;
        }
    }

    bool almacenado(int k) const {
        for (int i = 0; i < usado; ++i)
            if (D[i] == k) return true;
        return false;
    }
};


class Solution {

    int SumaDigitos(int x) {
        int sum= 0;
        while (x> 0) {
            int d = x%10;
            sum += d*d;
            x /= 10;
        }
        return sum;
    }

public:
    bool isHappy(int n) {
        HashTable visitado;               
        while(n != 1){
            if(visitado.almacenado(n))
                return false;           
                visitado.insert(n);         
            n= SumaDigitos(n);      
        }
        return true;                   
    }
};
