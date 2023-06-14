#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e18;

using nodo = tuple<ll, ll>;        // peso, nombre
using grafo = vector<set<nodo>>;   // peso, nombre
using calleBi = tuple<ll, ll, ll>; // peso, nombre

ll N, M;
int k, s, t;

grafo Grafo;
grafo GrafoT;

vector<ll> d;
vector<ll> dT;

// funciones de grafos

ll cantnodos(grafo g)
{
    return g.size();
}

ll nombre(auto n)
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

/*
class comparoD
{
    vector<ll>* dPun;
    public:
    comparoD(vector<ll>* param=&d){dPun=param;}
    bool operator() (const int& lhs, const int&rhs) const
    {
        return ((*dPun)[lhs]>(*dPun)[rhs]); //SI FUNCIONA MAL, CAMBIAR EL > por un <
    }
};
// typedef std::priority_queue<ll,std::vector<ll>,mycomparison> miTipo;
*/
// DIJKSTRA
void init(grafo &g, ll s, vector<ll> &d)
{
    for (int i = 0; i < d.size(); i++)
    {
        d[i] = inf;
    }
    d[s] = 0;
}


int minimo(vector<ll> &d, vector<bool> &procesado)
{
    ll min = inf;

    int indice;
    for (int v = 0; v < d.size(); v++)
    {
        if (procesado[v] == false && d[v] <= min)
        {
            min = d[v], indice = v;
        }
    }
    return indice;
}

void relax(ll u, nodo v, vector<ll> &d)
{
    if (d[nombre(v)] > d[u] + peso(v))
    {
        d[nombre(v)] = d[u] + peso(v);
    }
}
// idea usar vector visto o procesado y saber el minimo globalmente
void dijkstra(grafo &g, ll s, vector<ll> &d)
{
    init(g, s, d);
    // priority_queue<ll,std::vector<ll>,comparoD> q; // (mycomparison(d));
    vector<bool> procesado(g.size(), false);

    for (int i = 0; i < g.size(); i++)
    {
        int u = minimo(d, procesado);
        procesado[u] = true;
        for (nodo v : g[u])
        {
            relax(u, v, d); /* code */
        }

        //   q.pop();er1_calles.cpp:8:26: error: ‘nodo’ was not declared in this scope
        // 8 | using grafo = vector<set<nodo>>; //peso, nombre
        //|
    }
}

// priority_queue <int, vector<int>, greater<int>> gq; //Hago min heap
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

        if (minimo >= (ida + costo + vuelta))
        {
            minimo = (ida + costo + vuelta);
        } else if(minimo >= (ida2 + costo + vuelta2)){
            minimo = (ida2 + costo + vuelta2);
        }

    }
    return minimo;
}

int main()
{
    int cant;
    cin >> cant;
    while (cant > 0)
    {
        cin >> N >> M >> k >> s >> t;

        Grafo = grafo(N);
        GrafoT = grafo(N);

        d = vector<ll>(N);
        dT = vector<ll>(N);

        ll di, ci, li;
        for (int i = 0; i < M; i++)
        {
            cin >> di >> ci >> li;

            Grafo[di - 1].insert(make_tuple(li, ci - 1));
            GrafoT[ci - 1].insert(make_tuple(li, di - 1));
        }

        vector<calleBi> nuevasCalles = {};
        ll ui, vi, qi;
        for (int i = 0; i < k; i++)
        {
            cin >> ui >> vi >> qi;
            nuevasCalles.push_back(make_tuple(qi, ui - 1, vi - 1));
        }

        dijkstra(Grafo, s - 1, d);
        dijkstra(GrafoT, t - 1, dT);

        ll res = minimores(nuevasCalles);

        cout << res;
        cant--;
    }

    // std::cout << std::fixed;
    // std::cout << std::setprecision(5) << res;
}