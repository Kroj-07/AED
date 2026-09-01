#include <iostream>
using namespace std;

#define MAX_STACK_SIZE 100

class Nodo {
public:
    int valor;
    Nodo* izquierda;
    Nodo* derecha;
    explicit Nodo(int val) : valor(val), izquierda(nullptr), derecha(nullptr) {}
};

typedef struct { Nodo* ptr; } element;

typedef struct {
    element list[MAX_STACK_SIZE];
    int top;
} stackStruct;

int isfull(stackStruct *s){ return s->top >= MAX_STACK_SIZE - 1; }
int isempty(stackStruct *s){ return s->top == -1; }
element top(stackStruct *s){ return s->list[s->top]; }
void push(stackStruct *s, element e){ if(!isfull(s)) s->list[++(s->top)] = e; }
void pop(stackStruct *s){ if(!isempty(s)) --(s->top); }

class BinaryTree {
private:
    Nodo* raiz = nullptr;

    Nodo* construirBalanceadoRec(const vector<int>& v, int l, int r) {
        if (l > r) return nullptr;
        int mid = (l + r) >> 1;
        Nodo* nodo = new Nodo(v[mid]);
        nodo->izquierda = construirBalanceadoRec(v, l, mid - 1);
        nodo->derecha   = construirBalanceadoRec(v, mid + 1, r);
        return nodo;
    }

    void liberar(Nodo* n){
        if(!n) return;
        liberar(n->izquierda);
        liberar(n->derecha);
        delete n;
    }

public:
    BinaryTree()  = default;
    ~BinaryTree() { liberar(raiz); }


    void construirBalanceado(vector<int>& valores){
        sort(valores.begin(), valores.end());           
        raiz = construirBalanceadoRec(valores, 0, (int)valores.size()-1);
    }

    vector<int> obtenerInsercionSinRotaciones() const{
        vector<int> orden;
        if(!raiz) return orden;
        queue<Nodo*> q;
        q.push(raiz);
        while(!q.empty()){
            Nodo* cur = q.front(); q.pop();
            orden.push_back(cur->valor);
            if(cur->izquierda) q.push(cur->izquierda);
            if(cur->derecha)   q.push(cur->derecha);
        }
        return orden;
    }
};

void imprimirVector(const vector<int>& v){
    cout << "[";
    for(size_t i = 0; i < v.size(); ++i){
        cout << v[i];
        if(i + 1 < v.size()) cout << ", ";
    }
    cout << "]\n";
}


int main(){
    vector<int> valores = {2, 4, 1, 3, 5, 6, 7};
    vector<int> valores2 = {1, 2, 3};

    BinaryTree avl;
    avl.construirBalanceado(valores);

    BinaryTree avl2;
    avl2.construirBalanceado(valores2);
    vector<int> insercion = avl.obtenerInsercionSinRotaciones();
    vector<int> insercion2 = avl2.obtenerInsercionSinRotaciones();

    cout << "Caso 1 : \n";
    imprimirVector(insercion);
    cout << "Caso 2 : \n";
    imprimirVector(insercion2);

    return 0;
}
