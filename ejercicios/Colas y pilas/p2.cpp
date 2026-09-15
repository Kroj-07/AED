#include <iostream>
using namespace std;

#define MAX_STACK_SIZE 100

typedef struct {
    int key;
} element;

typedef struct {
    element list[MAX_STACK_SIZE];
    int top;
} StackStruct;

int isfull(StackStruct *s){
    return s->top >= MAX_STACK_SIZE - 1;
}

int isempty(StackStruct *s){
    return s->top == -1;
}

element top(StackStruct *s){
    return s->list[s->top];
}

void push(StackStruct *s, element e){
    if (!isfull(s)) {
        s->top++;
        s->list[s->top] = e;
    }
}

void pop(StackStruct *s){
    if (!isempty(s)) {
        s->top--;
    }
}

void print(StackStruct *s){
    for (int i = 0; i <= s->top; i++) {
        cout << s->list[i].key << " ";
    }
    cout << endl;
}

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> last(26);           
        vector<bool> visits(26, false);  

        for (int i = 0; i < s.size(); i++) {
            last[s[i] - 'a'] = i;
        }

        StackStruct stack;
        stack.top = -1;

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            if (visits[c - 'a']) continue;

            while (!isempty(&stack) && c < top(&stack).key && last[top(&stack).key - 'a'] > i) {
                visits[top(&stack).key - 'a'] = false; 
                pop(&stack);
            }

            element e;
            e.key = c;
            push(&stack, e);
            visits[c - 'a'] = true;  
        }

        string result = "";
        for (int i = 0; i <= stack.top; i++) {
            result += (char)stack.list[i].key;
        }

        return result; 
    }
};