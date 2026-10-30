#include<bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(0) -> sync_with_stdio(false);

    int n;
    long long k;

    cin>>n>>k;

    vector<long long> a(n);
    for (int i =0; i < n; ++i) {
        cin >> a[i];
    }

    deque<int> max_dq; 
    deque<int> min_dq; 

    long long total_tramos = 0;
    int max_longitud = 0;
    int l = 0; 

    for (int r =0; r < n; ++r) {
        while (!max_dq.empty() && a[max_dq.back()] <= a[r]) {
            max_dq.pop_back();
        }
        max_dq.push_back(r);

        while (!min_dq.empty() && a[min_dq.back()]>= a[r]) {
            min_dq.pop_back();
        }
        min_dq.push_back(r);

        while (a[max_dq.front()] - a[min_dq.front()] > k) {
            l++;
            while (!max_dq.empty() && max_dq.front() < l) {
                max_dq.pop_front();
            }
            while (!min_dq.empty() && min_dq.front() < l) {
                min_dq.pop_front();
            }
            
        }

        int len = r- l+ 1;
        total_tramos += len;
        max_longitud = max(max_longitud, len);
    }

    cout << total_tramos << " "<< max_longitud << "\n";

    return 0;
}