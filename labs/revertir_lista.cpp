//https://github.com/Kroj-07/AED.git

#include<iostream>
using namespace  std;

template<typename data_type>
struct LinkedNode {
    data_type data;
    LinkedNode* next;

    LinkedNode() {
        next = nullptr;
    }

    LinkedNode(data_type data, LinkedNode<data_type>* next = nullptr) : data(data), next(next) {}
};

template<typename data_type>
struct LinkedList {
    LinkedNode<data_type>* head;
    LinkedNode<data_type>* tail;

    LinkedList() {
        head = tail = nullptr;
    };


    void push_front(data_type value) {
        LinkedNode<data_type>* new_node = new LinkedNode<data_type>(value, head);
        if (head == nullptr) {
            tail = new_node;
        }
        head = new_node;
    }
    void push_back(data_type value) {
        if (tail == nullptr) {
            head = tail = new LinkedNode<data_type>(value);
        }
        else {
            tail -> next = new LinkedNode<data_type>(value);
            tail = tail -> next;
        }
    }

    void print() {
        LinkedNode<data_type>* current = head;
        while (current != nullptr) {
            cout << current -> data << " ";
            current = current -> next;
        }
        cout << '\n';
    }


};


LinkedList<long long> revertir(LinkedList<long long>& L){
    LinkedNode<long long>* current =L.head;
    LinkedList<long long> R = LinkedList<long long>();
    if (current == nullptr) return R;
    while(current!=nullptr){
        R.push_front(current->data);
        current=current->next;
    };
    return R;


}

int main() {
    LinkedList<long long> L;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        L.push_back(x);
    }
    L = revertir(L);
    L.print();
    return 0;
}