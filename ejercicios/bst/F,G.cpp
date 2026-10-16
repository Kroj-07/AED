/*
===============================================================================
  SOLUCIÓN UNIFICADA: PROBLEMAS F Y G (ÁRBOLES BINARIOS DE BÚSQUEDA)
===============================================================================

  Este archivo contiene la solución a dos problemas que giran en torno al mismo
  TDA: Árbol Binario de Búsqueda (ABB) sin balanceo. Se implementan las
  operaciones clásicas vistas en clase: inserción, búsqueda, sucesor,
  predecesor, eliminación (con Transplantar) y recorrido inorder.

  El programa lee primero los datos del Problema F y luego los del Problema G,
  tal como se describe en sus respectivos enunciados.

  -----------------------------------------------------------------------------
  PATRÓN COMÚN EN PROBLEMAS DE ABB
  -----------------------------------------------------------------------------
  - Se construye un ABB insertando valores en un orden dado.
  - Se mantienen punteros: izquierdo, derecho y padre.
  - Muchas consultas se resuelven navegando el árbol usando estos punteros.
  - El sucesor/predecesor se calcula en O(h), donde h es la altura.
  - La eliminación requiere la operación auxiliar Transplantar para mover
    subárboles.
  - El recorrido inorder devuelve los valores ordenados ascendentemente.
  - Si el árbol degenera (insertar ordenado), la altura es O(n) y las
    operaciones cuestan O(n). Esto es esperado y aceptable para n ≤ 5000.
  - Para problemas similares, identificar si se pide: inserción, búsqueda,
    eliminación, sucesor, predecesor, recorrido inorder, etc. Implementar
    las funciones correspondientes con punteros padre.

===============================================================================
  PROBLEMA F: SUCESOR Y PREDECESOR
===============================================================================
  ENUNCIADO:
  Se insertan n enteros distintos en un ABB. Luego, para cada consulta x
  (garantizado presente), se debe reportar su predecesor y sucesor en el
  recorrido inorder. Si no existe, imprimir NONE.

  LÓGICA:
  1. Insertar los n valores en el ABB (algoritmo estándar).
  2. Para cada consulta x, buscar el nodo que contiene x.
  3. Sucesor de un nodo u:
     - Si u tiene subárbol derecho, el sucesor es el mínimo de ese subárbol
       (bajar siempre por la izquierda desde u->right).
     - Si no tiene subárbol derecho, subir por los punteros de padre hasta
       encontrar el primer ancestro del cual se viene desde un hijo izquierdo.
       Ese ancestro es el sucesor. Si se llega a la raíz subiendo siempre
       desde un hijo derecho, no hay sucesor.
  4. Predecesor: simétrico (intercambiar izquierda por derecha).
  5. Imprimir predecesor y sucesor, o NONE.

  COMPLEJIDAD:
  - Construcción: O(n * h) en peor caso O(n^2) si degenera.
  - Cada consulta: O(h) en peor caso O(n).
  Con n, q ≤ 5000, es suficiente.

===============================================================================
  PROBLEMA G: ELIMINAR NODOS
===============================================================================
  ENUNCIADO:
  Simular un ABB inicialmente vacío. Procesar m operaciones:
  - INSERTAR x: inserta x (garantizado no presente).
  - ELIMINAR x: elimina x (garantizado presente).
  - EXISTE x: consulta si x está presente.
  Por cada EXISTE, imprimir SI o NO.
  Al final, imprimir el recorrido inorder del árbol resultante (o VACIO).

  LÓGICA:
  1. Implementar ABB con punteros (padre, izquierdo, derecho).
  2. Inserción: algoritmo estándar.
  3. Búsqueda: para EXISTE y para localizar nodo a eliminar.
  4. Eliminación: algoritmo clásico con Transplantar.
     - Caso 1: nodo sin hijo izquierdo -> Transplantar(z, z->right).
     - Caso 2: nodo sin hijo derecho -> Transplantar(z, z->left).
     - Caso 3: dos hijos -> buscar sucesor y = mínimo(z->right).
       Si y->parent != z, Transplantar(y, y->right), y->right = z->right,
       y->right->parent = y. Luego Transplantar(z, y), y->left = z->left,
       y->left->parent = y.
  5. Tras procesar todo, recorrido inorder recursivo. Si vacío, VACIO.

  COMPLEJIDAD:
  - Cada operación: O(h) en peor caso O(m).
  - Total: O(m^2) en peor caso. Con m ≤ 5000, aceptable.
  - Recorrido inorder: O(m).

===============================================================================
  IMPLEMENTACIÓN
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Estructura de nodo para ABB con puntero al padre.
struct Node {
    int val;
    Node *left, *right, *parent;
    Node(int v) : val(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

// ============================================================================
// FUNCIONES AUXILIARES COMUNES
// ============================================================================

// Inserción estándar en ABB. Devuelve la raíz (posiblemente nueva).
Node* insertar(Node* root, int val) {
    Node* nuevo = new Node(val);
    if (!root) return nuevo;
    Node* cur = root;
    Node* padre = nullptr;
    while (cur) {
        padre = cur;
        if (val < cur->val) cur = cur->left;
        else cur = cur->right;
    }
    nuevo->parent = padre;
    if (val < padre->val) padre->left = nuevo;
    else padre->right = nuevo;
    return root;
}

// Búsqueda de un valor. Devuelve el nodo o nullptr.
Node* buscar(Node* root, int val) {
    while (root && root->val != val) {
        if (val < root->val) root = root->left;
        else root = root->right;
    }
    return root;
}

// Mínimo de un subárbol.
Node* minimo(Node* node) {
    while (node->left) node = node->left;
    return node;
}

// Máximo de un subárbol.
Node* maximo(Node* node) {
    while (node->right) node = node->right;
    return node;
}

// Sucesor de un nodo (siguiente en inorder).
Node* sucesor(Node* node) {
    if (node->right) return minimo(node->right);
    Node* padre = node->parent;
    while (padre && node == padre->right) {
        node = padre;
        padre = padre->parent;
    }
    return padre;
}

// Predecesor de un nodo (anterior en inorder).
Node* predecesor(Node* node) {
    if (node->left) return maximo(node->left);
    Node* padre = node->parent;
    while (padre && node == padre->left) {
        node = padre;
        padre = padre->parent;
    }
    return padre;
}

// ============================================================================
// PROBLEMA F: SUCESOR Y PREDECESOR
// ============================================================================
void solveF() {
    int n;
    cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        root = insertar(root, x);
    }
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        Node* nodo = buscar(root, x);
        Node* pred = predecesor(nodo);
        Node* suc = sucesor(nodo);
        if (pred) cout << pred->val;
        else cout << "NONE";
        cout << ' ';
        if (suc) cout << suc->val;
        else cout << "NONE";
        cout << '\n';
    }
}

// ============================================================================
// PROBLEMA G: ELIMINAR NODOS
// ============================================================================

// Transplantar: reemplaza el subárbol con raíz u por el subárbol con raíz v.
// Devuelve la nueva raíz del árbol (puede cambiar si u era la raíz).
Node* transplantar(Node* root, Node* u, Node* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
    return root;
}

// Eliminar un nodo z del ABB. Devuelve la nueva raíz.
Node* eliminar(Node* root, Node* z) {
    if (!z->left) {
        root = transplantar(root, z, z->right);
    } else if (!z->right) {
        root = transplantar(root, z, z->left);
    } else {
        Node* y = minimo(z->right); // sucesor
        if (y->parent != z) {
            root = transplantar(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        root = transplantar(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    delete z;
    return root;
}

// Recorrido inorder recursivo.
void inorder(Node* root, vector<int>& res) {
    if (!root) return;
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}

void solveG() {
    int m;
    cin >> m;
    Node* root = nullptr;
    string op;
    while (m--) {
        cin >> op;
        int x;
        cin >> x;
        if (op == "INSERTAR") {
            root = insertar(root, x);
        } else if (op == "ELIMINAR") {
            Node* z = buscar(root, x);
            if (z) root = eliminar(root, z);
        } else if (op == "EXISTE") {
            Node* z = buscar(root, x);
            cout << (z ? "SI" : "NO") << '\n';
        }
    }
    vector<int> res;
    inorder(root, res);
    if (res.empty()) {
        cout << "VACIO\n";
    } else {
        for (size_t i = 0; i < res.size(); ++i) {
            if (i) cout << ' ';
            cout << res[i];
        }
        cout << '\n';
    }
}

// ============================================================================
// MAIN
// ============================================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Ejecutar Problema F (lee su entrada y produce su salida)
    solveF();

    // Ejecutar Problema G (lee su entrada y produce su salida)
    solveG();

    return 0;
}