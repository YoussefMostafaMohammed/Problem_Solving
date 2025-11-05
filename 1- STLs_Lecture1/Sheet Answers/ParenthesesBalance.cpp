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
    int ans =1;
    string s ;
    getline(cin,s);
    stack <char>st;
    for(char c:s){
        if(c=='(' ||c=='[' )
            st.push(c);
        else if(c==']' || c==')')
            if(st.empty())
                ans=0;
            else if(c==')' && st.top()=='[')
                ans=0;
            else if (c==']' && st.top()=='(')
                ans=0;
            else
                st.pop();
    }
    if(!st.empty())
        ans=0;
    if (ans)
        cout<<"Yes"<<"\n";
    else
        cout<<"No"<<"\n";
}
int main()
{
    FIO;
    ll tc = 1;
    string slach;
    //      TxtIO;
    cin >> tc;
    getline(cin,slach);
    for (ll i = 1; i <= tc; i++)
    {
        // cout << "Test case #" << i << "\n";
        start(i);
        // if (i != tc)
        // cout << "\n";
    }
    return 0;
}
