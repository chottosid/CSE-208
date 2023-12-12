#include "bits/stdc++.h"
using namespace std;
#define MAXN 10000
#define INF 1000000
vector<pair<int,int>> g[MAXN];
int n,m,source,destination;

void print_path(int parent[],int d[])
{
    vector<int> path;
    for (int v=destination;v!=source;v=parent[v])
    {
        path.push_back(v);
    }
    path.push_back(source);
    reverse(path.begin(), path.end());
    for(int i=0;i<path.size()-1;i++) cout<<path[i]<<"->";
    cout<<path[path.size()-1]<<endl;
}

void dijakstra()
{
    int d[n];
    int parent[n];
    for(int i=0;i<n;i++){
        d[i]=INF;
        parent[i]=-1;
    }
    set<pair<int,int>> q;
    d[source]=0;
    q.insert({0,source});
    while (!q.empty())
    {
        auto x=*q.begin();
        int u;
        u=x.second;
        q.erase(q.begin());
        for(auto node:g[u]){
            int v=node.first;
            int w=abs(node.second);
            if(d[v]>d[u]+w){
                d[v]=d[u]+w;
                parent[v]=u;
                q.insert({d[v],v});
            }
        }
    }
    cout<<d[destination]<<endl;
    print_path(parent,d);
    cout<<endl;
}

void bellman_ford()
{
    int d[n];
    int parent[n];
    for(int i=0;i<n;i++){
        d[i]=INF;
        parent[i]=-1;
    }
    d[source]=0;
    for(int i=0;i<n-1;i++){
        for(int u=0;u<n;u++){
            for(auto v:g[u]){
                if(d[v.first]>d[u]+v.second){
                    d[v.first]=d[u]+v.second;
                    parent[v.first]=u;
                }
            }
        }
    }
    bool neg_cycle=false;
    for(int u=0;u<n;u++){
        for(auto v:g[u]){
            if(d[v.first]>d[u]+v.second){
                neg_cycle=true;
                break;
            }
        }
        if(neg_cycle) break;
    }
    if(neg_cycle) cout<<"Negative weight cycle present\n";
    else{
        cout<<d[destination]<<endl;
        print_path(parent,d);
        cout<<endl;
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin>>n;
    cin>>m;
    for(int i=0;i<m;i++){
        int a,b,w;cin>>a>>b>>w;
        g[a].push_back({b,w});
    }
    cin>>source>>destination;
    cout<<"Bellman Ford Algorithm:"<<endl;
    bellman_ford();
    cout<<endl;
    cout<<"Dijkstra Algorithm:"<<endl;
    dijakstra(); 
}