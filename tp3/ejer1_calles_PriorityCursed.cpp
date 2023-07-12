#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e18;

using nodo = tuple<ll,ll>; //peso, nombre
using grafo = vector<set<nodo>>; //peso, nombre
using calleBi = tuple<ll,ll, ll>; //peso, nombre

ll N, M;
int k, s, t;

grafo Grafo;
grafo GrafoT;

vector<ll> d;
vector<ll> dT;

//funciones de grafos

ll cantnodos(grafo g)
{
    return g.size();
}

ll nombre(auto  n)
{
    return get<1>(n);
}

ll peso(auto n)
{
    return get<0>(n);
}

ll llegada(auto n)
{
    return get<2>(n);
}

//



void relax(ll u, nodo v, vector<ll>& d){
    if(d[nombre(v)] > d[u] + peso(v)){
        d[nombre(v)] = d[u] + peso(v);
        // DECREsEKEY?DEL QUEUEUUE
    }
}

void dijkstra(grafo& g, ll s, vector<ll>& d){
    //init(g, s, d);
    d[s] = 0;
   priority_queue<nodo,std::vector<nodo>,greater<nodo>> q;
    q.push(make_tuple(0,s)) ;

    while(!q.empty()){
       nodo u = q.top();
        q.pop();
        ll peso1 = peso(u);
        if(d[nombre(u)]< peso1) continue ;
        for(nodo v: g[nombre(u)]){
            if(d[nombre(v)] > d[nombre(u)] + peso(v)){
                d[nombre(v)] = d[nombre(u)] + peso(v);
                q.push(make_tuple(d[nombre(v)], nombre(v)));
                // DECREsEKEY?DEL QUEUEUUE
            }
        }
    }
}

ll minimores(vector<calleBi> &nuevasCalles)
{
    ll minimo = d[t - 1];

    for (int i = 0; i < nuevasCalles.size(); i++)
    {
        ll costo = peso(nuevasCalles[i]);

        ll ida = d[nombre(nuevasCalles[i])];
        ll vuelta = dT[llegada(nuevasCalles[i])];

        ll ida2 = dT[nombre(nuevasCalles[i])];
        ll vuelta2 = d[llegada(nuevasCalles[i])];

        minimo = min(minimo, min(ida + costo + vuelta, ida2 + costo + vuelta2));
    }
    return minimo;
}


int main(){
    int loop;
    cin >> loop;

    while(loop>0){

        cin >> N >> M >> k >> s >> t;
        Grafo.clear();         Grafo = vector<set<nodo>>(N);
        GrafoT.clear();        GrafoT = vector<set<nodo>>(N);
        d.clear();             d = vector<ll>(N, inf);
        dT.clear();            dT = vector<ll>(N, inf);

        ll di, ci, li;
        for(int i = 0; i < M ; i++){
            cin >> di >> ci >> li;

            Grafo[di -1].insert(make_tuple(li, ci - 1));
            GrafoT[ci -1].insert(make_tuple(li, di - 1));
        }

        dijkstra(Grafo, s - 1, d);
        dijkstra(GrafoT, t - 1, dT);

       vector<calleBi> nuevasCalles = {};
        ll ui, vi, qi;
        for(int i = 0; i < k ; i++){
            cin >> ui >> vi >> qi;
            nuevasCalles.push_back(make_tuple(qi, ui-1, vi-1));
        }

        ll res = minimores(nuevasCalles);
        if(res == inf){
            res = -1;
        }

        nuevasCalles.clear();

        cout << res << endl;

        loop--;
    }
    // std::cout << std::setprecision(5) << res;
}
