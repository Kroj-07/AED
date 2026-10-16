#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    // Rotación a la Izquierda
    void rotateLeft(Node*& root, Node*& x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // Rotación a la Derecha
    void rotateRight(Node*& root, Node*& y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

    // Corrección de violaciones a las propiedades tras la inserción
    void fixViolation(Node*& root, Node*& pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            /*  Caso A:
                El padre de pt es el hijo IZQUIERDO del abuelo */
            if (parent_pt == grand_parent_pt->left) {
                Node* uncle = grand_parent_pt->right;

                /* Caso 1: El tío de pt también es ROJO
                   Solución: Recolorear únicamente */
                if (uncle != nullptr && uncle->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    /* Caso 2: pt es hijo DERECHO
                       Solución: Rotación izquierda sobre el padre */
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Caso 3: pt es hijo IZQUIERDO
                       Solución: Rotación derecha sobre el abuelo y recolorear */
                    rotateRight(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            /*  Caso B:
                El padre de pt es el hijo DERECHO del abuelo (espejo del Caso A) */
            else {
                Node* uncle = grand_parent_pt->left;

                /* Caso 1: El tío es ROJO */
                if ((uncle != nullptr) && (uncle->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    /* Caso 2: pt es hijo IZQUIERDO */
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Caso 3: pt es hijo DERECHO */
                    rotateLeft(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        // Garantizar que la raíz siempre permanezca NEGRA
        root->color = BLACK;
    }

    // Recorrido In-Order recursivo
    void inorderHelper(Node* root) {
        if (root == nullptr)
            return;

        inorderHelper(root->left);
        std::cout << root->data << "(" << (root->color == RED ? "RED" : "BLACK") << ") ";
        inorderHelper(root->right);
    }

public:
    RedBlackTree() : root(nullptr) {}

    // Inserción estándar de BST seguida de la corrección del balance
    void insert(const int &data) {
        Node* pt = new Node(data);

        // BST Insert Estándar
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (pt->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        pt->parent = y;
        if (y == nullptr)
            root = pt;
        else if (pt->data < y->data)
            y->left = pt;
        else
            y->right = pt;

        // Reparar posibles violaciones de las propiedades Roji-Negras
        fixViolation(root, pt);
    }

    void inorder() {
        inorderHelper(root);
        std::cout << std::endl;
    }
};

int main() {
    RedBlackTree tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);

    std::cout << "Recorrido In-Order del Red-Black Tree impreso como valor(color):\n";
    tree.inorder();

    return 0;
}