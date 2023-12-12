#include<bits/stdc++.h>
using namespace std;
#define INF 100000000

int main()
{
    freopen("input.txt","r",stdin);
    freopen("prim.txt","w",stdout);
    int n,m;cin>>n>>m;
    int source=0;
    vector<pair<int,int>> g[n];
    for(int i=0;i<m;i++){
        int a,b,w;cin>>a>>b>>w;
        g[a].push_back({b,w});
        g[b].push_back({a,w});
    }
    pair<int,int> parent[n];
    int distant[n];
    for(int i=0;i<n;i++)
    {
        parent[i]={-1,-1};
        distant[i]=INF;
    }
    distant[source]=0;
    priority_queue<pair<int,int>> temp;
    bool included[n];
    for(int i=0;i<n;i++) included[i]=false;
    temp.push({0,source});
    while (!temp.empty())
    {
        auto x=temp.top();
        int w=-x.first;
        int u=x.second;
        temp.pop();
        if(included[u]==true){
            continue;
        }
        included[u]=true;
        for(auto v:g[u]){
            if(v.second<distant[v.first] and included[v.first]==false){
                distant[v.first]=v.second;
                temp.push({-v.second,v.first});
                parent[v.first]={u,v.second};
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(parent[i].first!=-1)
            ans+=parent[i].second;
    }
    cout<<"Total Weight "<<ans<<endl;
    cout<<"Root Node "<<source<<endl;
    for(int i=0;i<n;i++){
        if(parent[i].first!=-1)
            cout<<parent[i].first<<" "<<i<<endl;
    }
    
}