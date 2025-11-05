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
    int n,num,neg=0,gotNeg=0;
    cin>>n;
    vector<vector<int>> vec(3);
    for(int i =0;i<n;i++){
        cin>>num;
        if(num>0){
            vec[1].pb(num);
        }else if(num<0){
            vec[0].pb(num);
        }else{
            vec[2].pb(num);
        }
    }
    if( (vec[0].size()>2)){
        vec[1].pb(vec[0].back());
        vec[0].pop_back();
        vec[1].pb(vec[0].back());
        vec[0].pop_back();
    }
    if( ((vec[0].size()&1)==0)){
        vec[2].pb(vec[0].back());
        vec[0].pop_back();
    }

    for(int i =0;i<3;i++){
        cout<<vec[i].size()<<" ";
        sort(vec[i].begin(),vec[i].end());
        for(auto number:vec[i]){
            cout<< number<<" ";
        }
        cout<<"\n";
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
