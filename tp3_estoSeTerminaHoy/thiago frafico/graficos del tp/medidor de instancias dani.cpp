#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
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

ll nombre(auto n)
{
    return get<1>(n);
}

ll peso(auto n)
{
    return get<0>(n);
}

ll llegada(calleBi n)
{
    return get<2>(n);
}

//


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
void init(grafo &g, ll s, vector<ll> &d)
{
    for(int i  = 0; i < d.size(); i++)
    {
        d[i] = inf;
    }
    d[s] = 0;
}


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


//priority_queue <int, vector<int>, greater<int>> gq; //Hago min heap

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

ll mieleccion(vector<calleBi>nuevasCalles, ll t){
    ll res1 = inf;

    for(int i = 0;  i < nuevasCalles.size() ; i++  ){ 
    res1 = min(d[t],  min(res1, peso(nuevasCalles[i]) + min( d[nombre(nuevasCalles[i])] + dT[llegada(nuevasCalles[i])], d[llegada(nuevasCalles[i])] + dT[nombre(nuevasCalles[i])])));
    }
return res1;
};






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
        nuevasCalles.push_back(make_tuple(s[j + 2 + 5 + 3* M ], s[j  + 5 + 3*M], s[j + 1 + 5 + 3*M]));
    }

    dijkstra(Grafo, s[3] - 1, d);
    dijkstra(GrafoT, s[4] - 1, dT);


        ll res = inf;

        res = mieleccion(nuevasCalles, s[5]);
            //nuevasCalles.push_back(make_tuple(qi, ui-1, vi-1));
     

        //ll res = minimores(nuevasCalles);
        if(res == inf){
            res = -1;
        }
nuevasCalles = {};
        cout << res << endl;


// 2 2 2 1 1      1 1 2   2 2 1  1 2 3  1 2 4









    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
    
}
/*
*/

int main() {

    
    int repeat = 11;
    ofstream output_file; output_file.open("runtimedani.csv");
    output_file << "n,time\n";


    int limit = 4096+1;
    for (int n=4; n<limit; n*=2) {
        vector<int> input = read_input(n);

        double counter = 0;
       for (int ignore=0; ignore<repeat; ignore++) counter += measure(input);
        
      output_file << n << "," << counter / repeat << endl;
  
    }

    output_file.close();
    /**/
    return 0;
}
/*
/*
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

/*
class comparoD
{
    vector<ll>* dPun;
public:
    comparoD(vector<ll>* param=&d){dPun=param;}
    bool operator() (const ll& lhs, const ll&rhs) const
    {
        return ((*dPun)[lhs]<(*dPun)[rhs]); //SI FUNCIONA MAL, CAMBIAR EL > por un <
    }
};

class comparoDT
{
    vector<ll>* dPun;
public:
    comparoDT(vector<ll>* param=&dT){dPun=param;}
    bool operator() (const ll& lhs, const ll&rhs) const
    {
        return ((*dPun)[lhs]<(*dPun)[rhs]); //SI FUNCIONA MAL, CAMBIAR EL > por un <
    }
};
*/

// typedef std::priority_queue<ll,std::vector<ll>,mycomparison> miTipo;

//DIJKSTRA
//void init(grafo &g, ll s, vector<ll> &d)
//{
    //for(int i  = 0; i < d.size(); i++)
    //{
    //    d[i] = inf;
    //}
    //d[s] = 0;
//}

/*
void relax(ll u, nodo v, vector<ll>& d){
    if(d[nombre(v)] > d[u] + peso(v)){
        d[nombre(v)] = d[u] + peso(v);
        // DECREsEKEY?DEL QUEUEUUE
    }
}
/*
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
/*
void dijkstraT(grafo& g, ll s, vector<ll>& d){
    //init(g, s, d);
    d[s] = 0;
    std::priority_queue<ll,std::vector<ll>,comparoDT> q;



    for(ll i  = 0; i < d.size(); i++){
        q.push(i);
    }

    while(q.size() != 0){
        ll u = q.top();
        q.pop();

        for(nodo v: g[u]){
            relax(u,v,d);
        }
    }
}
*/
//priority_queue <int, vector<int>, greater<int>> gq; //Hago min heap
/*
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
                /*
        if (minimo >= (ida + costo + vuelta))
        {
            minimo = (ida + costo + vuelta);
        }
        if(minimo >= (ida2 + costo + vuelta2)){
            minimo = (ida2 + costo + vuelta2);
        }
*/


/*
int main(){
    int loop;
    cin >> loop;

    while(loop>0){

        cin >> N >> M >> k >> s >> t;
        Grafo.clear(); Grafo.resize(N);
        GrafoT.clear(); GrafoT.resize(N);
        d.clear(); d.resize(N, inf);
        dT.clear(); dT.resize(N, inf);

        ll di, ci, li;
        for(int i = 0; i < M ; i++){
            cin >> di >> ci >> li;

            Grafo[di -1].insert(make_tuple(li, ci - 1));
            GrafoT[ci -1].insert(make_tuple(li, di - 1));
        }

        dijkstra(Grafo, s - 1, d);
        dijkstra(GrafoT, t - 1, dT);

//        vector<calleBi> nuevasCalles = {};
        ll ui, vi, qi;
        ll res = inf;
        for(int i = 0; i < k ; i++){
            cin >> ui >> vi >> qi;
            //nuevasCalles.push_back(make_tuple(qi, ui-1, vi-1));
            res = min(d[t-1],  min(res, qi + min( d[ui-1] + dT[vi-1], d[vi-1] + dT[ui-1])));
        }


        //ll res = minimores(nuevasCalles);
        if(res == inf){
            res = -1;
        }

        cout << res << endl;

        loop--;
    }
    // std::cout << std::setprecision(5) << res;
}
*/