#include <bit/stdc++.h>
using namespace std;

template<typename data_type>
struct Queue{
    struct QueueNode{
        data_type data;
        QueueNode* next;

        QueueNode(){

        }
        QueueNode(data_type data): data(data), nest(nullptr){}
    };

    QueueNode* _front, *_back;
    Queue() {
        _front=nullptr;
        _back=nullptr;
    }

    void push(data_type value){
        if(_front==nullptr){
            _front= new Queue(value);
            _back=_front;

        }
        else{
            _back-> next=new QueueNode(value);
            _back=_back->next
        }
    }
    void pop(){
        if(_front !=nullptr){
            _front=front->next;
        }
    }

    data_type front(){
        return _front==nullptr?data_type() : _front->data;
    }

    bool empty(){
        return _front==nullptr;
    }

};

 
int main(){


    return 0;
}