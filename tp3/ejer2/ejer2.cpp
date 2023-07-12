#include <bits/stdc++.h>

using namespace std;



const int INF = 0x3FFFFFFF; //Capaz bug?

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<int> parent;
int bfs(int s, int t, vector<int>& parent) { //esta es la implementacion que mando Brian por el campus
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) { //esta es la implementacion que mando Brian por el campus
    int flow = 0;
    vector<int> parent(n);
    int new_flow = 0;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main(){


   
    int m;
    int votos;
    int amigoa;
    int amigob;
 int res;

while(true){
 scanf("%d %d", &n,&m);
    if( n == 0 && m == 0){
        break;
    }
n = n + 2 ;

 adj = vector<vector<int>>(n,vector<int>(n,0));
 capacity = vector<vector<int>>(n,vector<int>(n,0));
int s = 0;
int t = n - 1;


for ( int i = 1; i < n-1; i++ ){
 scanf("%d", &votos);
 if ( votos == 1 ){
adj[s][i] = i ;
capacity[s][i] = 1;
 } else {
    adj[i][t] = t ;
    capacity[i][t] = 1;
 }


}

for ( int i = 0 ; i < m ;i++ ){
 scanf("%d %d", &amigoa , &amigob);

    adj[amigoa][amigob] = amigob ;

    capacity[amigoa][amigob] = 1;

    adj[amigob][amigoa] = amigoa ;

    capacity[amigob][amigoa] = 1;
}
   res = maxflow(s,t);

     printf("%d \n", res);
}





}
