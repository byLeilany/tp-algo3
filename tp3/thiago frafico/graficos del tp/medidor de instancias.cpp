#include <chrono>
#include <iostream>
#include <fstream>

#include <bits/stdc++.h>

using namespace std;
using namespace std;




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
        //   decreasekey(Q,v);
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
        ll ida = d[nombre(nuevasCalles[i])];
        ll vuelta = dT[llegada(nuevasCalles[i])];
        ll costo = peso(nuevasCalles[i]);

        ll ida2 = dT[nombre(nuevasCalles[i])];
        ll vuelta2 = d[llegada(nuevasCalles[i])];

      if (minimo >= (ida + costo + vuelta))
        {
            minimo = (ida + costo + vuelta);
        } else if( minimo >= (ida2 + costo + vuelta2)){
            minimo = (ida2 + costo + vuelta2);

        }


    }
    return minimo;
}





vector<int> read_input(int size ) {
    vector<int> input(0);
    string file_name = "/home/dani/Documents/uba/algo3/tp-algo3/tp3_estoSeTerminaHoy/thiago frafico/graficos del tp/input/input" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name, ifstream::in);
   
    while(true) {
        int casa;

        read_file >> casa;

        if(casa == 0 ){
            break;

        }

input.push_back(casa);

    }

    read_file.close();
    return input;
}

double measure(vector<int> s) {
    auto start = chrono::high_resolution_clock::now();

    Grafo = grafo(s[0]);
    GrafoT = grafo(s[0]);

    d = vector<ll>(s[0]);
    dT = vector<ll>(s[0]);

   
    for (int i =  0 ; i < s[1]*3; i = i + 3)
    {
        

        Grafo[s[i+ 5]- 1].insert(make_tuple(s[i + 2 + 5], s[i + 1 + 5] - 1));
        GrafoT[s[i + 1 + 5] - 1].insert(make_tuple(s[i + 2 + 5], s[i + 5] - 1 ));
    }

    vector<calleBi> nuevasCalles = {};
    ll ui, vi, qi;
    for (int j  = 0; j < s[2] * 3; j = j + 3)
    {
        
        nuevasCalles.push_back(make_tuple(s[j + 1 + 5 + 3* M ], s[j + 5 + 3*M], s[j + 1 + 5 + 3*M]));
    }

    dijkstra(Grafo, s[3] - 1, d);
    dijkstra(GrafoT, s[4] - 1, dT);

    ll res = minimores(nuevasCalles);

    cout << res;

// 2 2 2 1 1      1 1 2   2 2 1  1 2 3  1 2 4









    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
    
}
/*
*/

int main() {

    
    int repeat = 11;
    ofstream output_file; output_file.open("runtimeoptimizado.csv");
    output_file << "n,time\n";
    ofstream respuestas; respuestas.open("respuestas2.csv");
    respuestas <<" respuestas \n ";

    int limit = 4096+1;
    for (int n=4; n<limit; n*=2) {
        vector<int> input = read_input(n);

        double counter = 0;
       for (int ignore=0; ignore<repeat; ignore++) counter += measure(input);
        
      output_file << n << "," << counter / repeat << endl;
  
    }
    respuestas.close(); 
    output_file.close();
    /**/
    return 0;
}
