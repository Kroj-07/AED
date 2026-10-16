#pragma once
#include <bits/stdc++.h>

template <typename K>
class AVL {
public:
struct Node {
K key;
int h = 0; // altura del subarbol con raiz en este nodo
Node *l = nullptr, *r = nullptr;
explicit Node(const K& k) : key(k) {}
};

struct Stats {
std: : size_t single = 0; // reestructuraciones con rotacion simple (LL o RR)
// reestructuraciones con rotación doble (LR o RL)
std :: size_t dbl = 0;
};


AVL() = default;
AVL(const AVL&) = delete;
AVL& operator=(const AVL&) = delete;
AVL(AVL&& o) noexcept : root_(o.root_), n_(o.n_), st(o.st) { o.root _= nullptr; o.n _= 0; }
~AVL() { destroy(root_); }

bool insert(const K& k) {
bool ok = false;
root_ = ins(root_, k, ok); // la raiz puede cambiar: SIEMPRE se reasigna
n_ += ok;
return ok;}

bool erase(const K& k) {
bool ok = false;
root _= era(root_, k, ok);
n_ -= ok;
return ok;}

bool contains(const K& k) const {
for (const Node* x = root _; x;) {
if (k < x->key) x = x->l;
else if (x->key < k) x = x->r;
else return true;}

return false;}

// Mayor clave <= k (floor) y menor clave >= k (ceil); nullptr si no existe.
const K* floor(const K& k) const {
const K* best = nullptr;
for (const Node* x = root _; x;) {
if (k < x->key) x = x->l;
else { best = &x->key; if (x->key < k) x = x->r; else break; }

return best;}

const K* ceil(const K& k) const {
const K* best = nullptr;

}

}

for (const Node* x = root _; x; ) {
if (x->key < k) x = x->r;
else { best = &x->key; if (k < x->key) x = x->l; else break; }
}
return best;
}
int height() const { return h(root_); }
std: : size_t size() const { return n _; }
const Node* root() const { return root _; }
static int h(const Node* x) { return x ? x->h : -1; }
static int bf(const Node* x) { return h(x->l) - h(x->r); }

// Comprueba orden BST, alturas almacenadas, |bf| <= 1 y el tamaño.
bool verify() const {
std :: size_t cnt = 0;
int hh = 0;
bool ok = check(root_, nullptr, nullptr, hh, cnt);
return ok && cnt == n _;
}

Stats st; // contadores de reestructuraciones (para experimentos)

private:
Node* root_ = nullptr;
std :: size_t n_ = 0;

static void destroy(Node* x) {
if (!x) return;
destroy(x->L);
destroy(x->r);
delete x;
}

static void upd(Node* x) { x->h = 1 + std: :max(h(x->l), h(x->r)); }

static Node* rot_right(Node* y) {
Node* x = y->l;
y->l = x->r;
x->r = y;
upd(y); // primero el que ha bajado (y es ahora hijo de x) ...
upd(x); // ... y despues el que ha subido
return x;
}

static Node* rot_left(Node* x) {
Node* y = x->r;
x->r = y->l;
y->l = x;
upd(x);
upd(y);
return y;
}


// Restablece |bf| <= 1 en x, suponiendo que los hijos ya son AVL y que
// sus alturas difieren a lo sumo en 2. Devuelve la nueva raíz del subárbol.
Node* rebalance(Node* x) {
upd(x);
int b = bf(x);
if (b > 1) {
if (bf(x->l) <0) {

// pesado a la izquierda
// zig-zag (LR): primero enderezar el hijo

x->l = rot_left(x->l);
++st.dbl;
} else {
++st.single;

return rot_right(x);

if (b < -1) {
if (bf(x->r) > 0) {
x->r = rot_right(x->r);
++st.dbl;
} else {
++st.single;

return rot_left(x);

return x;

// LL (bf(hijo) = 1, o 0 solo en eliminación)

// pesado a la derecha
// zig-zag (RL)

// RR

Node* ins(Node* x, const K& k, bool& ok) {
if (!x) { ok = true; return new Node(k); }
if (k < x->key) x->l = ins(x->l, k, ok);
else if (x->key < k) x->r = ins(x->r, k, ok);
else { ok = false; return x; } // duplicado: nada cambió
return ok ? rebalance(x) : x;

Node* era(Node* x, const K& k, bool& ok) {
if (!x) { ok = false; return nullptr; }
if (k < x->key) x->l = era(x->l, k, ok);
else if (x->key < k) x->r = era(x->r, k, ok);
else {
ok = true;
if (!x->l || !x->r) {
Node* c = x->l ? x->l : x->r;
delete x;
return c;

Node* m = x->r;
while (m->l) m = m->l;
K s = m->key;
x->key = s;
bool dummy = false;
x->r = era(x->r, s, dummy);

return ok ? rebalance(x) : x;

// 0 o 1 hijo: el hijo (o nulo) ocupa su lugar

// 2 hijos: sucesor inorden

// borrar el sucesor (como maximo 1 hijo)

// reequilibrar en CADA nodo del camino de vuelta

bool check(const Node* x, const K* lo, const K* hi, int& hh, std :: size_t& cnt) const {
if (!x) { hh = -1; return true; }
if ((lo && !(*lo < x->key) ) || (hi && ! (x->key < *hi))) return false;
int hl = 0, hr=0;
if (!check(x->l, lo, &x->key, hl, cnt)) return false;
if (!check(x->r, &x->key, hi, hr, cnt)) return false;
hh = 1 + std: :max(hl, hr);
++cnt;
return x->h == hh && (hl - hr <= 1) && (hr - hl <= 1);