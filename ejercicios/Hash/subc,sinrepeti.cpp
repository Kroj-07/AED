
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ============================================
    // PROBLEMA A: Nota de Rescate
    // ============================================
    // Contar frecuencia de cada letra en r y m.
    // Si r necesita más de alguna letra que m tiene, NO.
    // Si para todas las letras alcanza, SI.
    {
        string r, m;
        cin >> r >> m;

        int freqR[26] = {0};
        int freqM[26] = {0};

        for (char c : r) freqR[c - 'a']++;
        for (char c : m) freqM[c - 'a']++;

        bool posible = true;
        for (int i = 0; i < 26; i++) {
            if (freqR[i] > freqM[i]) {
                posible = false;
                break;
            }
        }

        cout << (posible ? "SI" : "NO") << '\n';
    }

    // ============================================
    // PROBLEMA B: Joyas y Piedras
    // ============================================
    // Marcar letras de J como joyas (con mayúsculas/minúsculas).
    // Recorrer S y contar cuántos caracteres son joyas.
    {
        string J, S;
        cin >> J >> S;

        bool esJoya[256] = {false};
        for (char c : J) {
            esJoya[(unsigned char)c] = true;
        }

        int respuesta = 0;
        for (char c : S) {
            if (esJoya[(unsigned char)c]) {
                respuesta++;
            }
        }

        cout << respuesta << '\n';
    }


+  

    {string s;
    if(!(cin>>s)) return 0;
    int n=s.length();
    int izq=0;
    int max_lon=0;

    //vector para guardar la ultim posi d cada caracter
    vector<int> ultima_pos(256,-1);

    for(int der=0; der<n; ++der){
        char c=s[der];

        //1. si el caracter c ya aparecio dentro d la ventana actual
        if (ultima_pos[c]>=izq){
            izq=ultima_pos[c]+1;
        }


        //2 actualiz. la ultim posici del caracter
        ultima_pos[c]=der

        //3. long d la ventana actual y actualiz el max
        int lon_actual= der-izq+1;
        max_lon=max(max_lon, lon_actual);



    }

    cout<<max_lon<<end;
    }
    return 0;
}