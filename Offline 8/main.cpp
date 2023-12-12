#include "bits/stdc++.h"
using namespace std;
#define pb push_back
#define vi vector<int>
#define vii vector<pair<int, int>>
#define vll vector<ll>
#define FastIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
#define INF 2000000000
#define FOR(i, a, b) for (int i = a; i < b; i++)

class Graph
{
public:
    int siz;
    vector<vector<pair<int, int>>> g;
    Graph(int a)
    {
        siz = a;
    }
    void Create_Random_Graph(int v)
    {
        siz = v;
        g.assign(v, vector<pair<int, int>>());

        vector<pair<int, int>> cords(v);
        for (int i = 0; i < v; i++)
        {
            cords[i].first = rand() % 200;
            cords[i].second = rand() % 200;
        }

        for (int i = 0; i < v; i++)
        {
            for (int j = i + 1; j < v; j++)
            {
                int x1 = cords[i].first;
                int y1 = cords[i].second;
                int x2 = cords[j].first;
                int y2 = cords[j].second;
                int d = (int)(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))) % 200;

                g[i].push_back({j, d});
                g[j].push_back({i, d});
            }
        }
    }

    pair<int, vector<int>> Exact_TSP()
    {
        int n = siz;
        vector<vector<int>> dp(1 << n, vector<int>(n, INF));
        dp[1][0] = 0;

        for (int msk = 1; msk < (1 << n); msk++)
        {
            for (int u = 0; u < n; u++)
            {
                if (msk & (1 << u))
                {
                    for (auto e : g[u])
                    {
                        int v = e.first;
                        int w = e.second;
                        if (v != u && (msk & (1 << v)))
                        {
                            dp[msk][u] = min(dp[msk][u], dp[msk ^ (1 << u)][v] + w);
                        }
                    }
                }
            }
        }

        int mincst = INF;
        int node = -1;
        for (int u = 0; u < n; u++)
        {
            int cost = dp[(1 << n) - 1][u] + g[u][0].second;
            if (cost < mincst)
            {
                mincst = cost;
                node = u;
            }
        }

        vector<int> path;
        int msk = (1 << n) - 1;
        int curr = node;
        path.push_back(curr);
        while (path.size() != n)
        {
            for (auto i : g[curr])
            {
                if (msk & (1 << i.first))
                {
                    if (dp[msk][curr] == dp[msk ^ (1 << curr)][i.first] + i.second)
                    {
                        path.push_back(i.first);
                        msk ^= (1 << curr);
                        curr = i.first;
                        break;
                    }
                }
            }
        }

        return {mincst, path};
    }

    //     If size of S is 2, then S must be {1, i},
    //  C(S, i) = dist(1, i)
    // Else if size of S is greater than 2.
    //  C(S, i) = min { C(S-{i}, j) + dis(j, i)} where j belongs to S, j != i and j != 1.
    int min_val(vector<int> &vals, vector<bool> &taken)
    {
        int mn = INF;
        int idx = -1; // Initialize min_index to -1

        for (int v = 0; v < siz; v++)
        {
            if (!taken[v] and vals[v] < mn)
            {
                mn = vals[v];
                idx = v;
            }
        }

        return idx;
    }

    vector<vector<pair<int, int>>> primMST()
    {
        vector<int> parent(siz, -1);
        vector<int> vals(siz, INF);
        vector<bool> taken(siz, false);

        vals[0] = 0;

        for (int count = 0; count < siz - 1; count++)
        {
            int u = min_val(vals, taken);
            taken[u] = true;

            for (auto e : g[u])
            {
                int v = e.first;
                int w = e.second;
                if (!taken[v] and w < vals[v])
                {
                    parent[v] = u;
                    vals[v] = w;
                }
            }
        }

        vector<vector<pair<int, int>>> tree(siz);
        for (int i = 1; i < siz; i++)
        {
            int u = parent[i];
            int v = i;
            int w = vals[i];
            tree[u].push_back({v, w});
        }

        return tree;
    }

    vector<int> approximateTSP()
    {
        vector<vector<pair<int, int>>> tree = primMST();
        vector<int> v;
        preOrder(tree, 0, v);
        v.push_back(0);
        return v;
    }
    void preOrder(vector<vector<pair<int, int>>> tree, int current, vector<int> &path)
    {
        path.push_back(current);
        for (auto i : tree[current])
        {
            preOrder(tree, i.first, path);
        }
    }
    int Calculate_Tour_Cost(vector<int> path)
    {
        int cost = 0;
        for (int i = 0; i < path.size() - 1; i++)
        {
            for (auto j : g[path[i]])
            {
                if (j.first == path[i + 1])
                {
                    cost += j.second;
                    break;
                }
            }
        }
        return cost;
    }
};
int main()
{
    int x;
    cin >> x;
    vi exact_len;
    vi approx_len;
    while (x--)
    {
        Graph g(20);
        g.Create_Random_Graph(20);

        int exact = g.Exact_TSP().first;
        exact_len.push_back(exact);
        auto path = g.approximateTSP();

        int approx = g.Calculate_Tour_Cost(path);
        approx_len.push_back(approx);
    }
    for (int i = 0; i < exact_len.size(); i++)
    {
        int exact = exact_len[i];
        int approx = approx_len[i];
        double ratio = (double)(approx)*1.0 / (double)(exact)*1.0;
        cout << "(" << i + 1 << "," << ratio << ")" << endl;
    }
}