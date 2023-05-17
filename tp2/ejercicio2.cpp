#include <bits/stdc++.h>
#include <algorithm>    // std::sort

using namespace std;

/*
ideas:
1. identificar c.c. (ponerles un nombre a cada una)
2. para cada c.c. X quiero saber cuales son las flechas que salen de X que lleguen a alguien !=X  ~ kosaraju

cuando tengo las c.c FA = {1,2,3}, FB = {5, 6}, FC = {4}
                     cfcParaCadaNodo = [A,A,A,C,B,B]

3. y ver que arista NO sigue la "cadenita" +++ las componentes disjuntas?

loTumbaAlguien? = [0, 1, 1, 0, 1, 0] y tu conjunto min es los que quedaron en 0
6 cfc
ojo ver caso "tengo una cadenita", "tengo "
EdeCFC = (F1, F2)(F1, F3)(F4, F5) ordenado con radixSort "si estoy de 2da componente, entonces alguien me tumba"
*/



using nodo = int;
vector<set<nodo>> grafo;


//funciones de grafos

set<nodo> vecinos(vector<set<nodo>> g, nodo n){
    return g[n];
}

int cantnodos(vector<set<nodo>> g){
    return g.size();
}

void quitararista(vector<set<nodo>>& g, nodo u, nodo w){
    // g[u][w] = 0;
    g[u].erase(w);
    g[w].erase(u);
}

void ponerarista(vector<set<nodo>> g, nodo u, nodo w){
    // g[u][w] = 1;
    g[u].insert(w);
    g[w].insert(u);
}

//

//init para dfs
int NO_LO_VI = 0; 
int EMPECE_A_VER = 1;
int TERMINE_DE_VER = 2;
vector<int> estado; //init en NO_LO_VI
vector<set<int>> treeEdges; //init en []
list<int> orden;


void dfs(int v) {       //me guarda el orden pavo
    estado[v] = EMPECE_A_VER;
    for (int u : grafo[v]) {
        if (estado[u] == NO_LO_VI) {
            treeEdges[v].insert(u);
            dfs(u);
        }
    }
    orden.push_front(v);
    estado[v] = TERMINE_DE_VER;
}


int CFC_NONE = -1; 
vector<int> losF;       // [3, , , ]
vector<int> cfc4eachNodo; //[-1,-1,-1,-1,-1,-1]

void dfsParaT(int v, int ccInx) {      //me hace componentes, solo entra a partir de un nodo que termina en un ciclo
    estado[v] = EMPECE_A_VER;
    cfc4eachNodo[v] = ccInx;
    for (int u : grafo[v]) {
        if (estado[u] == NO_LO_VI) {
            if(losF[ccInx] > u){
                losF[ccInx] = u;
            }
            treeEdges[v].insert(u);
            dfsParaT(u, ccInx);
        }
    }
    estado[v] = TERMINE_DE_VER;
} 

int fst(tuple<int, int> e){
    return get<0>(e);
}
int snd(tuple<int, int> e){
    return get<1>(e);
}


int N;
int M;

int main(){
    cin >> N; 
    cin >> M;

    vector<tuple<int, int>> E;    //G^t = (V,E)

    vector<set<nodo>> G(N);     //G = (V,E)
    vector<set<nodo>> GT(N);    //G^t = (V,E)

    int u = 0;
    int w = 0;
    for(int i = 0; i < M ; i++){
        cin >> u;
        cin >> w;

        E.push_back(make_tuple(u-1, w-1));

        G[u - 1].insert(w - 1);
        
        GT[w - 1].insert(u - 1);
    }



    estado = vector<nodo>(N, NO_LO_VI);
    treeEdges = vector<set<int>>(N); 
    grafo = G;      //para hacer DFS en G
    for(int v = 0; v < N; v++){
        if(estado[v] == NO_LO_VI){
            dfs(v);
        }
    }

    losF = vector<int>(0);          //empieza con NINGUNA cfc
    estado = vector<nodo>(N, NO_LO_VI);
    cfc4eachNodo = vector<int>(N, CFC_NONE); //CC_NONE significa que NO esta en NINGUNA c.c.
    grafo = GT;     //para hacer DFS en G^t
    int contadorCFC = 0;


    list<int> debuggg = orden;
    vector<int> debug1 = cfc4eachNodo;
    vector<nodo> debug  = estado; //BORRAR DESPUESSSSSSSSSSSSSSSSSs
    vector<nodo> debug2 = losF; 

    for (list<int>::iterator i = orden.begin(); i != orden.end(); ++i){
        if(estado[*i] == NO_LO_VI){
            losF.push_back(*i);
            dfsParaT(*i, contadorCFC);
            contadorCFC++;
        }
    }

    debuggg = orden;
    debug1 = cfc4eachNodo;
    debug  = estado; //BORRAR DESPUESSSSSSSSSSSSSSSSSs
    debug2 = losF; 
    
    //ahora debo ver para cada arista e=(u,v) si sucede que cfc4eachNodo[u]!=cfc4eachNodo[v], para guardamela como flechita, 
    // vector<tuple<int, int>> Ecfc;
    vector<bool> aQuienTumban(losF.size(), false);
    for(tuple<int, int> e : E){
        if(cfc4eachNodo[fst(e)] != cfc4eachNodo[snd(e)]){
            // Ecfc.push_back(e);
            aQuienTumban[cfc4eachNodo[snd(e)]] = true;
        }
    }
    
    vector<int> res;
    for(int i = 0; i < aQuienTumban.size(); i++){
        if(!aQuienTumban[i]){
            res.push_back(losF[i] + 1); // + 1 xq los estabamos representando los nodos del 0 al n-1
        }
    }

    sort(res.begin(), res.end()); //asumo que esto es O(|res|*log(|res|))
    
    cout << res.size() <<endl;
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }
}

/*  
6 7
1 2 2 3 3 1
2 4 6 4
6 5 5 6
*/
