#include <chrono>
#include <iostream>
#include <fstream>

#include <bits/stdc++.h>

using namespace std;
using namespace std;




using namespace std;
using ll = int;

double resU;
double resV;


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

void kruskal(int Wi, vector <int> s){
    sort(E.begin(),E.end());
    int aristas = 0;
    DSU dsu(s[0]);
    for(tuple<double, int, int> e : E){ //duv
        if(Wi > s[2]){ //cortamos el kruskal
            double d = get<0>(e); int u = get<1>(e); int v = get<2>(e);
            //si (u,v) es arista segura
            if(dsu.find(u) != dsu.find(v)){
                // agregar
                dsu.unite(u,v);
                aristas++;
                if(d <= s[1]){ //guarda info distinto
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





vector<int> read_input(int size) {
    vector<int> input(2*size + 5); 
    string file_name = "/home/thiago/Desktop/New Folder/tp-algo3/tp2/graficos del tp/input/input" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name, ifstream::in);
   
    for (int i=0; i<2*size + 5; i++) {
        int casa;

        read_file >> casa;

        input[i] = casa;
    }
    read_file.close();
    return input;
}

double measure(vector<int> s) {
    auto start = chrono::high_resolution_clock::now();

        resU = 0;
        resV = 0;
        E = vector<tuple<double, int, int>>(0);

        
        ll x,y;
        vector<tuple<ll, ll>> coord;

        for(int i = 0; i < s[0]; i++){
            tuple<ll, ll> dActual = {s[i + 5],s[ i + 6]};
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

        kruskal(s[0], s);
        resU = resU* s[3];
        resV = resV* s[4];
        std::cout << std::fixed;
        // if(itCasos == cantCasos){
        //     cout<<"Caso #" << itCasos <<": "<< std::setprecision(3) << double(resU) << " " << std::setprecision(3) << double(resV);
        // }else{
            cout<< std::setprecision(3) << resU << " " << std::setprecision(3) << resV <<endl;
        // }



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
