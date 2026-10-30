#include<bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, L;
    cin>>n>>L;


    vector<string> palabras(n);
    unordered_map<string, vector<string>> mapa_patrones;

    for (int i=0; i<n; ++i){
        cin>>palabras[i];
    }

    for (const auto& palabra: palabras){
        for (int i=0; i<L; ++i){
            string patron=palabra;
            patron[i]='*';
            mapa_patrones[patron].push_back(palabra);
        }
    }

    int sum_grados=0;
    int max_grado=0;
    int pal_aisladas=0;

    for (const auto& palabra: palabras){
        unordered_set<string> vecinos;


        for (int j=0; j<L; ++j){
            string patron=palabra;
            patron[j]='*';

            for (const string& v: mapa_patrones[patron]){
                vecinos.insert(v);
            }
    }

    vecinos.erase(palabra);
    
    int grado=vecinos.size();

    if (grado==0){
        pal_aisladas++;
    }

    max_grado=max(max_grado, grado);

    sum_grados+=grado;

}

int m=sum_grados/2;

cout<<m<<" "<<max_grado<<" "<<pal_aisladas<<endl;



    return 0;
}