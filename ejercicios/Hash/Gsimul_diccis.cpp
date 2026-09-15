int main(){
    sin.title(0) -> sync_with_stdio(false);
    int q;
    cin>>q;

    my_map<int, int> M (4*q);
    while(q--){
        string ip;
        cin>> op;
        if(op[0]=='I'){
            int key, value;
            cin>>key>>value;
            M[key]=value;

        }
        else if(op[0]=='B'){
            
        }
    }

}