/*CONCEPTO: secucneica d nodos donde cada elemento apunta al sgt
SE USA WHEN:
muchas inserciones y eliminaciones en medio d la lista.
no se necesita acceso aleatorio por indice
*/

#include<iostream>
using namespace::std;

template<typename data_type>
struct LinkedNode {
    long long exp;
    long long coef;
    LinkedNode* next;

    LinkedNode() {
        next = nullptr;
    }

    LinkedNode(long long exp, long long coef, LinkedNode<data_type>* next = nullptr) : exp(exp), coef(coef), next(next) {}
};

template<typename data_type>
struct LinkedList {
    LinkedNode<data_type>* head;
    LinkedNode<data_type>* tail;

    LinkedList() {
        head = tail = nullptr;
    };

    void push_front(data_type value) {
        // Inserta un nodo con informacion "value"
        // al inicio de la lista
        LinkedNode<data_type>* new_node = new LinkedNode<data_type>(value, head);
        if (head == nullptr) {
            tail = new_node;
        }
        head = new_node;
    }

    void push_back(long long x, long long y) {
        if (tail == nullptr) {
            head = tail = new LinkedNode<data_type>(x,y);
        }
        else {
            tail -> next = new LinkedNode<data_type>(x,y);
            tail = tail -> next;
        }
    }

    void insert(LinkedNode<data_type>* node, data_type value) {
        // Inserta un nodo con informacion "value"
        // Después del nodo "node" que no es nulo
        LinkedNode<data_type>* new_node = new LinkedNode<data_type>(value, node -> next);
        if (node == tail) {
            tail = new_node;
        }
        node -> next = new_node;
    }

    void insert(int k, data_type value) {
        // Inserta "value" como el k-ésimo valor en la nueva secuencia
        // Es 0-indexed
        if (k == 0) push_front(value);
        else {
            LinkedNode<data_type>* current = head;
            for (int i = 1; i <= k - 1; ++i) {
                current = current -> next;
            }
            insert(current, value);
        }
    }

    LinkedList<data_type> copy(LinkedList<data_type>& r, LinkedList<data_type>& q){
        while (q!=nullptr){
            r.push_back(q->exp, q->coef);
            q=q->next;
        }
        return r;
    }


    void pop_front() {
        LinkedNode<data_type>* current = head;
        head = head -> next;
        if (head == nullptr) tail = nullptr;
        delete current;
    }

    void erase(LinkedNode<data_type>* node) {
        // Elimina el siguiente al nodo "node"
        if (node -> next) {
            LinkedNode<data_type>* current = node -> next;
            if (node -> next == tail) {
                tail = node;
            }
            node -> next = node -> next -> next;
            delete current;
        }
    }

    void erase(int k) {
        if (k == 0) pop_front();
        else {
            LinkedNode<data_type>* current = head;
            for (int i = 1; i <= k - 1; ++i) {
                current = current -> next;
            }
            erase(current);
        }
    }

    void print() {
        LinkedNode<data_type>* current = head;
        int count=0;

        while (current != nullptr) {
            count ++;
            current = current -> next;
        }
        cout <<count<< '\n';

        current=head;
        while (current != nullptr) {
            cout << current -> exp << " " << current -> coef << endl;
            current = current -> next;}
    }

    
};


    LinkedList<long long> sum(LinkedList<long long>& P, LinkedList<long long>& Q ){
        LinkedNode<long long>* p=P.head;
        LinkedNode<long long>* q=Q.head;
        LinkedList<long long> R;
        while (p!=nullptr&&q!=nullptr){
            if (p->exp>q->exp){
                R.push_back(q->exp, q->coef);
                q=q->next;
            }
            else if(p->exp<q->exp){
                R.push_back(p->exp, p->coef);
                p=p->next;
            }
            else{
                long long coef = p->coef + q->coef;

                if (coef != 0) {
                    R.push_back(p->exp, coef);
                }
                p=p->next;
                q=q->next;
            }
            
        }
        while (p!=nullptr){
            R.push_back(p->exp, p->coef);
            p=p->next;
        }
        while (q!=nullptr){
            R.push_back(q->exp, q->coef);
            q=q->next;
        }
        return R;


    }



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n1;
    cin >> n1;

    LinkedList<long long> P;
    for (int i=0; i<n1; i++){
        long long x, y;
        cin >> x >> y;
        P.push_back(x, y);
    }

    int n2;
    cin >> n2;
    LinkedList<long long> Q;
    for(int i=0; i<n2; i++){
        long long x, y;
        cin >> x >> y;
        Q.push_back(x, y);
    }

    

    LinkedList<long long> R = sum(P, Q);
    R.print();
    return 0;
}