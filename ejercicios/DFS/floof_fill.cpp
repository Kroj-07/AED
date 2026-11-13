#include<bits/stdc++.h>
using namespace::std;


//arreglos d desplazamientos 
int df[]= {-1, 1, 0,0};
int dc[]={ -1, 1, 0, 0};

//debe estar dentro d los loimites d la matriz
bool es_valida( int f, int c, int R, int C){
    return (f>=0 && f< R && c>= 0&& c<C);
}

void floo_fill_iteartivo(int f_init, int c_init, vector<vector<int>>& grilla,
                         vector<vectro<bool>>& visitado, int R, int C){
    stack<pair<int, int>> P;

    P.push({f_init, c_init});
    visitado[f_init] [c_init]=true;

    while (!P.empty()){
        auto [f, c]=P.top();//casilla actual
        P.pop();

        for(int k=0; k<4; k++){  //exploracion d sus 4 vecinos
            int nf= f+df[k];
            int nc=c+dc[k];

            if(es_valida(nf,nc,R,C)&& grilla[nf][nc]== 1 && !visitado[nf][nc]){
                visitado[nf][nc]=true;
                P.push({nf, nc});
            }
        }
    }

}

int contar_islas(vector<vector<int>>$ grilla, int R, int C){
    vector<vector<bool>> visitado (R, vector<bool>(C, false));
    int cantidad_islas=0;
//recorrer toda la grilla fila por fila
    for (int f=0; f<R; f++){
      for(int c=0; c<C; C++){
        //tierra no ivsitada, new isla
        if(grilla[f][c]==1 && !visitado[f][c]){
            cantidad_islas++;
            //inundamos toda la isla dcompleta para no volver a contar
            floo_fill_iterativo(f, c, grilla, visitado, R, C);
        }
      }
    }
    return cantidad_islas;

}

