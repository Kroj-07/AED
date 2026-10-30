#include <bits/stdc++.h>
using namespace std;



int BFS(int sx, int sy, int tx, int ty, int n, int m, vector<string> &s) {
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
    vector<vector<int>> D(n, vector<int>(m, -1));
    queue<pair<int, int>> Q;
    Q.emplace(sx, sy);
    D[sx][sy] = 0;
    while (not Q.empty()) {
        int ux, uy;
        tie(ux, uy) = Q.front();
        Q.pop();
        for (int k = 0; k < 4; ++k) {
            int vx = ux + dx[k];
            int vy = uy + dy[k];
            if (vx < 0 or vy < 0 or vx >= n or vy >= m) continue;
            if (s[vx][vy] == '#') continue;
            if (D[vx][vy] != -1) continue;
            D[vx][vy] = D[ux][uy] + 1;
            Q.emplace(vx, vy);
}
}
    return D[tx][ty];
}
int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m>>endl;

    vector<string> s(n);
    int sx=-1, sy=-1, tx=-1, ty=-1;


    for(int i=0; i<n; i++){
        cin>>s[i];
        for (int j=0;j<m;j++){
            if(s[i][j]=='S'){ sx=i; sy=j;}
            if(s[i][j]=='E'){tx=i; ty=j; }            
            
        }
    }

    intresjultado =bfs(n,m,sx,sy,tx,ty,s)
    cout<<resultado<<endl;

    return 0;
}


