#include<iostream>

using namespace std;

#define MAX_STACK_SIZE 100


typedef struct {
    int key;
} element;


typedef struct {
    element list[MAX_STACK_SIZE];
    int top;
} stackStruct;


int isfull(stackStruct *s){
    if(s->top >= MAX_STACK_SIZE - 1) return 1;
    return 0;
}

int isempty(stackStruct *s){
    if(s->top == - 1) return 1;
    return 0;
}

element top(stackStruct *s){
    return s->list[s->top];
}

void push(stackStruct *s, element e){
    (s->top)++;
    s->list[s->top] = e;
}

void pop(stackStruct *s){
    (s->top)--;
}

void print(stackStruct *s){
    for (int i = 0; i <= s->top; i++) cout<<s->list[i].key<<" ";    
    cout<<endl;
}

int main(){

    stackStruct Z;
    Z.top = -1;
    cout<<"Create pila"<<endl;
    cout<<"La pila esta llena: "<<isfull(&Z)<<endl;
    cout<<"La pila esta vacia: "<<isempty(&Z)<<endl;
    cout<<"El top de la pila: "<<top(&Z).key<<endl;
    cout<<"Imprimir la pila: ";
    print(&Z);

    
    cout<<"Push un elemento a la pila"<<endl;
    element e1;
    e1.key =  10;
    push(&Z, e1);    
    cout<<"La pila esta llena: "<<isfull(&Z)<<endl;
    cout<<"La pila esta vacia: "<<isempty(&Z)<<endl;
    cout<<"El top de la pila: "<<top(&Z).key<<endl;
    cout<<"Imprimir la pila: ";
    print(&Z);

    cout<<"Push un elemento a la pila"<<endl;
    element e2;
    e2.key =  9;
    push(&Z, e2);    
    cout<<"La pila esta llena: "<<isfull(&Z)<<endl;
    cout<<"La pila esta vacia: "<<isempty(&Z)<<endl;
    cout<<"El top de la pila: "<<top(&Z).key<<endl;
    cout<<"Imprimir la pila: ";
    print(&Z);

    cout<<"Push un elemento a la pila"<<endl;
    element e3;
    e3.key =  19;
    push(&Z, e3);    
    cout<<"La pila esta llena: "<<isfull(&Z)<<endl;
    cout<<"La pila esta vacia: "<<isempty(&Z)<<endl;
    cout<<"El top de la pila: "<<top(&Z).key<<endl;
    cout<<"Imprimir la pila: ";
    print(&Z);

    cout<<"Pop un elemento a la pila"<<endl;
    pop(&Z);
    cout<<"La pila esta llena: "<<isfull(&Z)<<endl;
    cout<<"La pila esta vacia: "<<isempty(&Z)<<endl;
    cout<<"El top de la pila: "<<top(&Z).key<<endl;
    cout<<"Imprimir la pila: ";
    print(&Z);

    return 0;
}