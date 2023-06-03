#include <bits/stdc++.h>

using namespace std;
using ll = int;

double resU;
double resV;

/*
W = #modems
N = #oficinas
sabemos W < N

U = costo UTP
V = costo fibraOptica

R = maxEstricto distancia hasata donde puedo usar UTP

respuestas:
Caso #i: "costo de # de UTP usado?"(con 3 decimales) "costo de # de fibraOptica usado?"(3decimales)

asumimos U <= V



idea: para el krusal cuando #bosques = #modems
*/

ll fst(tuple<ll, ll> e){
    return get<0>(e);
}
ll snd(tuple<ll, ll> e){
    return get<1>(e);
}

double dist(tuple<ll,ll> d1, tuple<ll,ll> d2){
    ll a = fst(d1) - fst(d2);
    ll b = snd(d1) - snd(d2);
    return sqrt( a*a + b*b);
}


vector<tuple<double, int, int>> E(0); // (dist, UTP?, i, f)

int cantCasos;
int N; double R; int W; double U; double V;


//jaja gracias julian, sos un capo
//funciones para hacer kruskal
struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

void kruskal(int Wi){
    sort(E.begin(),E.end());
    int aristas = 0;
    DSU dsu(N);
    for(tuple<double, int, int> e : E){ //duv
        if(Wi > W){
            double d = get<0>(e);
            int u = get<1>(e);
            int v = get<2>(e);
            //si (u,v) es arista segura
            if(dsu.find(u) != dsu.find(v)){
                // agregar
                dsu.unite(u,v);
                aristas++;
                if(d <= R){
                    resU += d;
                }else{
                    resV += d;
                }
                Wi--;
            }
        }else{
            break;
        }
    }
}

int main(){
      cin >> cantCasos;
      int itCasos = 1;
      while(itCasos <= cantCasos){
        resU = 0;
        resV = 0;
        E = vector<tuple<double, int, int>>(0);

        cin >> N >> R >> W >> U >> V;
        
        ll x,y;
        vector<tuple<ll, ll>> coord;

        for(int i = 0; i < N; i++){
            cin >> x >> y;
            tuple<ll, ll> dActual = {x,y};
            coord.push_back(dActual);
        } 

        for(int k = 0; k < coord.size() - 1; k++){
            tuple<ll, ll> dActual = coord[k];

            for(int h = k + 1; h < coord.size(); h++){
                tuple<ll, ll> dSig = coord[h];
                double d = dist(dSig, dActual);
                E.push_back({d, k, h});

            }
        }

        kruskal(N);
        resU = resU*U;
        resV = resV*V;
        std::cout << std::fixed;
        // if(itCasos == cantCasos){
        //     cout<<"Caso #" << itCasos <<": "<< std::setprecision(3) << double(resU) << " " << std::setprecision(3) << double(resV);
        // }else{
            cout<<"Caso #" << itCasos <<": "<< std::setprecision(3) << resU << " " << std::setprecision(3) << resV <<endl;
        // }
        itCasos++;
      }
}

//2 3 1 1 1 1 0 0 1 0 0 1 6 1 3 2 3 0 0 0 2 2 0 3 2 2 3 3 3
// 6 1 3 2 3 
// 0 0 , 0 2 , 2 0 , 3 2 , 2 3 , 3 3
//  0     1     2     3     4     5