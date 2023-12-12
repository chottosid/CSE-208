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
int main()
{
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
        distant[a+1][b+1]=w;
    }
    vector<vector<int>> ans=floyd_warshall();
    bool cycle_found=false;
    for(int i=1;i<=n;i++){
        if(ans[i][i]<0){
            cycle_found=true;
            break;
        }
    }
    if(cycle_found) cout<<"Yes\n";
    else cout<<"No\n";
}