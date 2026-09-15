// Repositorio público: https://github.com/tu-usuario/tu-repositorio

#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value = T(), Node* n = nullptr) : data(value), next(n) {}
};

template <typename T>
struct LinkedList {
    Node<T>* head;
    Node<T>* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    unsigned long long toDecimal() const {
        unsigned long long result = 0;
        Node<T>* current = head;

        while (current != nullptr) {
            result = (result << 1) + static_cast<unsigned long long>(current->data);
            current = current->next;
        }

        return result;
    }
};

int main() {
    int n;
    cin >> n;

    LinkedList<int> bits;
    for (int i = 0; i < n; ++i) {
        int bit;
        cin >> bit;
        bits.push_back(bit);
    }

    cout << bits.toDecimal() << '\n';
    return 0;
}