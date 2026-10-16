#include <iostream>
using namespace std;

void hanoi(int n, int src, int pivot, int snk) {
    if (n == 0) return;

    // Mover n-1 discos del origen al poste pivote usando el destino como aux
    hanoi(n - 1, src, snk, pivot);

    // Mover el disco n del origen al destino (con espacios entre valores)
    cout << n << " " << src << " " << snk << '\n';

    // Mover n-1 discos del pivote al destino usando el origen como aux
    hanoi(n - 1, pivot, src, snk);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        hanoi(n, 1, 2, 3);
    }
    return 0;
}