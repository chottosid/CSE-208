#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000
#define INF 1000000

int distant[MAXN][MAXN];
int n,m;
vector<vector<int>> floyd_warshall()
{
    vector<vector<int>> d(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            d[i][j]=distant[i][j];
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(d[i][k]<INF and d[k][j]<INF)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]); 
            }
        }
    }
    return d;
}
vector<vector<int>> extend_shortest_path(vector<vector<int>> L,vector<vector<int>> W){
    vector<vector<int>> L2(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            L2[i][j]=INF;
            for(int k=1;k<=n;k++){
                L2[i][j]=min(L2[i][j],L[i][k]+W[k][j]);
            }
        }
    }
    return L2;
}
vector<vector<int>> all_pair_shortest_path(){
    vector<vector<int>> L(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            L[i][j]=distant[i][j];
        }
    }
    int m=1;
    while (m<n-1)
    {
        vector<vector<int>> L2;
        L2=extend_shortest_path(L,L);
        L=L2;
        m*=2;
    }
    return L;
    
}

int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            distant[i][j]=INF;
            if(i==j) distant[i][j]=0;
        }
    }
    for(int i=0;i<m;i++){
        int a,b,w;cin>>a>>b>>w;
        distant[a][b]=w;
    }

    vector<vector<int>> ans=all_pair_shortest_path();
    cout<<"Shortest distance matrix\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(ans[i][j]==INF) cout<<"INF ";
            else cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }

}
