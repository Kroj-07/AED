#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

template<class Key, class Value>
class HashTable {
private:
    static const int SIZE = 1000;
    struct Node {
        Key key;
        Value value;
        Node* next;
        Node(Key k, Value v) : key(k), value(v), next(nullptr) {}
    };
    Node* D[SIZE];

public:
    HashTable() {
        for (int i = 0; i < SIZE; ++i) {
            D[i] = nullptr;
        }
    }

    int hash(const Key& key) {
        if constexpr (is_same<Key, char>::value) {
            return int(key); 
        } else if constexpr (is_same<Key, string>::value) {
            int h = 0;
            for (char c : key) {
                h = (h * 31 + c) % SIZE; 
            }
            return h;
        } 
    }

    void insert(const Key& key, const Value& value) {
        int idx = hash(key);
        Node* node = D[idx];
        while (node) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        Node* newNode = new Node(key, value);
        newNode->next = D[idx];
        D[idx] = newNode;
    }

    Value get(const Key& key) {
        int idx = hash(key);
        Node* node = D[idx];
        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        return Value(); 
    }
};

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words;
        string word;
        stringstream ss(s);
        while (ss >> word) {
            words.push_back(word);
        }

        if (pattern.size() != words.size()) {
            return false;
        }

        HashTable<char, int> char_to_idx;
        HashTable<string, int> word_to_idx;

        for (int i = 0; i < pattern.size(); ++i) {
            char c = pattern[i];
            string w = words[i];

            int mapped_char = char_to_idx.get(c);
            int mapped_word = word_to_idx.get(w);

            if (mapped_char == 0 && mapped_word == 0) {
                char_to_idx.insert(c, i + 1); 
                word_to_idx.insert(w, i + 1);
            } else {
                if (mapped_char != mapped_word) {
                    return false;
                }
            }
        }

        return true;
    }
};