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
    int t,num,counter=0;
    string s;
    cin>>t;
    deque<int>deq;
    while(t--){
        cin>>s;
        if(s=="reverse")
            counter++;

        if(!(counter&1)){
            if(s=="toFront"){
                cin>>num;
                deq.push_front(num);
            }else if(s=="front"){
                if(deq.empty())
                    cout<<"No job for Ada?\n";    
                else{
                    cout<<deq.front()<<"\n";
                    deq.pop_front();
            }
            }else if(s=="back"){
                if(deq.empty())
                    cout<<"No job for Ada?\n";    
                else{
                    cout<<deq.back()<<"\n";
                    deq.pop_back();
                }
            }else if(s=="push_back"){
                cin>>num;
                deq.push_back(num);
            }
        }else{
            if(s=="push_back"){
                cin>>num;
                deq.push_front(num);
            }else if(s=="back"){
                if(deq.empty())
                    cout<<"No job for Ada?\n";    
                else{
                    cout<<deq.front()<<"\n";
                    deq.pop_front();
                }
            }else if(s=="front"){
                if(deq.empty())
                    cout<<"No job for Ada?\n";    
                else{
                    cout<<deq.back()<<"\n";
                    deq.pop_back();
                }
            }else if(s=="toFront"){
                cin>>num;
                deq.push_back(num);
            }
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
