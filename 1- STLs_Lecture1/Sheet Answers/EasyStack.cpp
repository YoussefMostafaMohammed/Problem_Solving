#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#define FIO                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

#define TxtIO                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#define X first
#define Y second
#define pb push_back
#define ll long long
using namespace std;

const ll N = 1 << 18, M = 1e3 + 5, OO = 1e12, L = 26;

void start(ll tc)
{
    int t,op,num;
    stack<int>st;
    cin>>t;
    while(t--){
        cin>>op;
        if(op==1){
            cin>>num;
            st.push(num);
        }else if(op==2){
            if(!st.empty())
                st.pop();
        }else{
            if(st.empty())
                cout<<"Empty!\n";
            else
                cout<<st.top()<<"\n";
        }
    }
}

int main()
{
    FIO;
    ll tc = 1;
    //      TxtIO;
    // cin >> tc;
    for (ll i = 1; i <= tc; i++)
    {
        // cout << "Test case #" << i << "\n";
        start(i);
        // if (i != tc)
        // cout << "\n";
    }
    return 0;
}
