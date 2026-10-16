#include <iostream>
#include <algorithm>

using namespace std;

// Definición de la estructura del Nodo desde cero
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int val) : key(val), height(0), left(nullptr), right(nullptr) {}
};

// Variable global para contar las rotaciones de cada operación
int rotation_count = 0;

// Devuelve la altura de un nodo (-1 si es nulo)
int getHeight(Node* n) {
    if (n == nullptr) return -1;
    return n->height;
}

// Recalcula la altura en función de sus dos hijos
void updateHeight(Node* n) {
    if (n != nullptr) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }
}

// Calcula el Factor de Balanceo: FB(v) = altura(izq) - altura(der)
int getBalance(Node* n) {
    if (n == nullptr) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// Rotación simple a la Derecha
Node* rotateRight(Node* y) {
    rotation_count++; // Cuenta como 1 rotación
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotación simple a la Izquierda
Node* rotateLeft(Node* x) {
    rotation_count++; // Cuenta como 1 rotación
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Rebalancear un nodo según las reglas especificadas en el problema
Node* rebalance(Node* node) {
    if (node == nullptr) return nullptr;

    updateHeight(node);
    int fb = getBalance(node);

    // Caso FB(v) > 1: desbalanceado a la izquierda
    if (fb > 1) {
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left); // Precedida de Rotar-Izquierda
        }
        return rotateRight(node);
    }

    // Caso FB(v) < -1: desbalanceado a la derecha
    if (fb < -1) {
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right); // Precedida de Rotar-Derecha
        }
        return rotateLeft(node);
    }

    return node;
}

// Inserción en AVL
Node* insert(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }

    return rebalance(node);
}

// Encuentra el nodo con el valor mínimo en el subárbol (el sucesor)
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Eliminación en AVL
Node* remove(Node* node, int key) {
    if (node == nullptr) return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        // Encontrado el nodo a eliminar
        
        // Caso 1: Tiene 0 o 1 hijo
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;
            
            if (temp == nullptr) { // 0 hijos
                temp = node;
                node = nullptr;
            } else { // 1 hijo
                *node = *temp; // Copia el contenido del hijo
            }
            delete temp;
        } else {
            // Caso 2: Tiene 2 hijos -> Reemplazar por su sucesor
            Node* temp = getMinValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    if (node == nullptr) return nullptr;

    return rebalance(node);
}

int main() {
    // Optimización de la entrada y salida estándar
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    Node* root = nullptr;

    while (q--) {
        int type, x;
        cin >> type >> x;

        rotation_count = 0; // Reiniciar contador antes de cada operación

        if (type == 1) {
            root = insert(root, x);
        } else {
            root = remove(root, x);
        }

        // Imprimir: [rotaciones hechas] [altura actual del árbol]
        cout << rotation_count << " " << getHeight(root) << "\n";
    }

    return 0;
}