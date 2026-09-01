#include<iostream>
using namespace std;

struct Node {
    string value;
    string tokenId;
    int expirationTime;
    Node* next;
    Node* prev;

    Node(string _tokenId, int _expirationTime) {
        tokenId = _tokenId;
        expirationTime = _expirationTime;
        next = nullptr;
        prev = nullptr;
    }
};

class DLL {
public:
    Node* head;
    Node* tail;
    int size;

    DLL() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
        void print(){
            Node *temp = head;
            while(temp != nullptr){
                cout<<temp->value<<" ";
                temp = temp->next;
            }
            cout<<endl;
        }
        void push_front(Node *node_new){
            node_new->next = head;
            if(head != NULL){
                head->prev = node_new;
            }else{
               tail = node_new; 
            }
            head = node_new;
            size++;
        }
        void push_back(Node *node_new){
            node_new->prev = tail;
            if (tail != nullptr){
                tail->next = node_new;
            }else{
                head = node_new;
            }
            tail = node_new;
            size++;
        }

        void pop_back(){
            Node *temp = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete temp;
            size--;
        }

    void pop_front() {
        if (head == nullptr) return;
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = nullptr;
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    void insert(int p, Node *node_new){
            if(p >= 0 && p <= size - 1){
                if (p == 0){
                    push_front(node_new);
                } else{
                    int i = 0;
                    Node *temp = head;
                    while (i++ < p - 1)  temp = temp->next;
                    node_new->next = temp->next;
                    node_new->prev = temp;
                    temp->next->prev = node_new;
                    temp->next = node_new;
                }
                size++;
            }
        }

        void free_memory(){
            Node *temp = nullptr;
            while(head != nullptr){
                temp = head;
                head = head->next;
                delete temp;
            }
            size = 0;
        }

    int getSize() {
        return size;
    }
};

class AuthenticationManager {
private:
    int timeToLive;
    DLL tokens;

public:
    AuthenticationManager(int _timeToLive) {
        timeToLive = _timeToLive;
    }

    void generate(string tokenId, int currentTime) {
        Node* node = new Node(tokenId, currentTime + timeToLive);
        tokens.push_back(node);
    }

    void renew(string tokenId, int currentTime) {
        Node* temp = tokens.head;
        while (temp != nullptr) {
            if (temp->tokenId == tokenId && temp->expirationTime > currentTime) {
                generate(tokenId, currentTime);
                return;
            }
            temp = temp->next;
        }
    }

    int countUnexpiredTokens(int currentTime) {
        while (tokens.head != nullptr && tokens.head->expirationTime <= currentTime) {
            tokens.pop_front();
        }
        return tokens.getSize();
    }
};
