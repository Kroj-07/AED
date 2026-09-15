


string removeBrackets(string s){
    Cola cola;
    for (char c: s){
            if(c== '(' || c=='{' || c=='[')
               cola.enqueue(c);
            else if(c== ')' || c=='}' || c==']')
                if (cola.estaVacia())
                    return "NO";
                else
                cola.dequeue();
    }
    return "SI";
}

int main(){
    string s;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s;

        cout<<removeBrackets(s)<<endl;
}}

