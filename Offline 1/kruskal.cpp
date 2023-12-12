#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000
int parent[MAXN];
int siz[MAXN];

void makeset(int u)
{
    parent[u]=u;
    siz[u]=1;
}
int findset(int u)
{
    if(parent[u]==u) return u;
    parent[u]=findset(parent[u]);
    return parent[u];
}
void unionset(int a,int b)
{
    int x=findset(a);
    int y=findset(b);
    if(x==y) return;
    if(siz[x]<=siz[y]){
        parent[x]=y;
        siz[y]+=siz[x];
    }
    else{
        parent[y]=x;
        siz[x]+=siz[y];
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("kruskal.txt","w",stdout);
    int n,m;cin>>n>>m;
    vector<tuple<int,int,int>> edgelist;
    for(int i=0;i<m;i++){
        int a,b,w;cin>>a>>b>>w;
        edgelist.push_back(make_tuple(w,a,b));
    }
    for(int i=0;i<n;i++){
        makeset(i);
    }
    sort(edgelist.begin(),edgelist.end());
    int ans=0;
    vector<pair<int,int>> final_graph;
    for(auto x :edgelist)
    {
        int u=get<1>(x);
        int v=get<2>(x);
        int w=get<0>(x);
        if(findset(u)!=findset(v)){
            ans+=w;
            final_graph.push_back({u,v});
            unionset(u,v);
        }
    }
    cout<<"Total Weight: "<<ans<<endl;
    for(auto x:final_graph){
        cout<<x.first<<" "<<x.second<<endl;
    }
    
}