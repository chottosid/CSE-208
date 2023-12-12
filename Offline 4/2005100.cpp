#include "bits/stdc++.h"
using namespace std;
#define pb push_back
#define vi vector<int>
#define vii vector<pair<int,int>>
#define vll vector<ll>
#define vvi vector<vector<int>>
#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define endl '\n' 
typedef long long ll;
typedef unsigned long long ull;
#define INF 2000000000
#define FOR(i,a,b) for(int i=a;i<b;i++)
int n;

vector<string> team_names;
vector<tuple<int,int,int>> team_data;
vector<vector<int>> g;

int BFS(vvi& adj,vvi& cap,int source,int sink,vvi& res,vi& parent){
    queue<int> q;
    q.push(source);
    vi M(cap.size(),0);
    M[source]=INF;
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v:adj[u]){
            {
                if(cap[u][v]-res[u][v]>0 and parent[v]==-1){
                    parent[v]=u;
                    M[v]=min(M[u],cap[u][v]-res[u][v]);
                    if(v!=sink){
                        q.push(v);
                    }
                    else
                        return M[sink];
                }

            }
        }
    }
    return 0;
    
}

int Edmonds_Karp(int source,int sink,vector<vector<int>>& adj,vector<vector<int>>& cap){
    int flow=0;
    int max_nodes=cap.size();
    vector<vector<int>> res(max_nodes,vector<int>(max_nodes,0));
    while (true)
    {   vector<int> parent(max_nodes,-1);
        parent[source]=-2;
        int M=BFS(adj,cap,source,sink,res,parent);
        if(M==0) break;
        flow+=M;
        int v=sink;
        while(v!=source){
            int u=parent[v];
            res[u][v]+=M;
            res[v][v]-=M;
            v=u;
        }
    }
    return flow;    
}

bool is_elim(int idx){
    int maxw=0;
    for(int i=0;i<n;i++){
        maxw=max(maxw,get<0>(team_data[i]));
    }
    int currw=get<0>(team_data[idx])+get<2>(team_data[idx]);
    if(currw<maxw){
        return true;
    }
    int max_nodes=n*n+2;
    vector<vector<int>> adj(max_nodes);
    vector<vector<int>> cap(max_nodes,vector<int>(max_nodes,0));
    int source=n*n;
    int sink=n*n+1;
    int cnt=n+1;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(i==idx or j==idx){
                cnt++;
                continue;
            }
            adj[source].push_back(cnt);
            cap[source][cnt]=g[i][j];
            adj[cnt].push_back(i);
            adj[cnt].push_back(j);
            cap[cnt][i]=INF;
            cap[cnt][j]=INF;
            if(adj[i].size()==0){
                adj[i].push_back(sink);
                cap[i][sink]=currw-get<0>(team_data[i]);
            }
            if(adj[j].size()==0){
                adj[j].push_back(sink);
                cap[j][sink]=currw-get<0>(team_data[j]);
            }
            cnt++;
        }
    }
    int max_flow=Edmonds_Karp(source,sink,adj,cap);
    int total_games = 0;
    for (int i = 0; i < n; ++i) {
        if (i == idx) continue;
        for (int j = i + 1; j < n; ++j) {
            if (j == idx) continue;
            total_games += g[i][j];
        }
    }

    return max_flow < total_games;
}

vector<string> elimination(){
    vector<string> eliminated;
    for(int i=0;i<n;i++){
        if(is_elim(i)){
            eliminated.push_back(team_names[i]);
        }
    }
    return eliminated;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin>>n;
    g.resize(n,vector<int>(n));
    for(int i=0;i<n;i++){
        string team_name;
        int w,l,r;
        cin>>team_name>>w>>l>>r;
        team_names.push_back(team_name);
        team_data.push_back({w,l,r});
        for(int j=0;j<n;j++){
            cin>>g[i][j];
        }
    }
    vector<string> eliminated=elimination();
    for(auto x:eliminated){
        cout<<x<<" is eliminated"<<endl;
    }
}