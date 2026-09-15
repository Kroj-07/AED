#include <iostream>
using namespace std;

#define MAX_STACK_SIZE 100

typedef struct {
    int key;
} element;

typedef struct {
    element list[MAX_STACK_SIZE];
    int top;
} custom_stack;

int isfull(custom_stack *s){
    return s->top >= MAX_STACK_SIZE - 1;
}

int isempty(custom_stack *s){
    return s->top == -1;
}

element top(custom_stack *s){
    return s->list[s->top];
}

void push(custom_stack *s, element e){
    if (!isfull(s)) {
        s->top++;
        s->list[s->top] = e;
    }
}

void pop(custom_stack *s){
    if (!isempty(s)) {
        s->top--;
    }
}

void print(custom_stack *s){
    for (int i = 0; i <= s->top; i++) {
        cout << s->list[i].key << " ";
    }
    cout << endl;
}

class Solution {
public:
    string removeDuplicateLetters(string s) {
        int ultimo[26];
        for (int i = 0; i < 26; ++i) ultimo[i] = -1;
        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j < s.size(); ++j) {
                if (s[j] == 'a' + i) {
                    ultimo[i] = j;
                }
            }
        }

        char lista[26];
        for (int i = 0; i < 26; ++i) lista[i] = 0;

        custom_stack stack;
        stack.top = -1;

        for (int i = 0; i < s.size(); i++) {
            bool duplicados = false;
            for (int j = 0; j < 26; ++j) {
                if ((char)('a' + j) == s[i] && lista[j]) {
                    duplicados = true;
                    break;
                }
            }

            if (duplicados) continue;

            while (!isempty(&stack)) {
                char ch = stack.list[stack.top].key;
                if (ch > s[i]) {
                    int idx = -1;
                    for (int k = 0; k < 26; ++k) {
                        if ((char)('a' + k) == ch) {
                            idx = k;
                            break;
                        }
                    }
                    if (ultimo[idx] > i) {
                        lista[idx] = 0;
                        pop(&stack);
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }

            push(&stack, {s[i]});
            for (int j = 0; j < 26; ++j) {
                if ((char)('a' + j) == s[i]) {
                    lista[j] = 1;
                    break;
                }
            }
        }

        string result = "";
        for (int i = 0; i <= stack.top; i++) {
            result += stack.list[i].key;
        }
        return result;
    }
};