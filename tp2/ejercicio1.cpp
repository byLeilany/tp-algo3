#include <bits/stdc++.h>

using namespace std;



using nodo = int;

int N;
int M;

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







int NO_LO_VI = 0; 
int EMPECE_A_VER = 1;
int TERMINE_DE_VER = 2;
vector<int> estado(0); //init en NO_LO_VI



vector<int> backConExtremoInferiorEn(0);
vector<int> backConExtremoSuperiorEn(0);
vector<set<nodo>> grafo(0);
vector<nodo> padre(0);
vector<set<nodo>> treeEdges(0); //init en []

void dfs(nodo v, nodo p) {
    estado[v] = EMPECE_A_VER;
    for (nodo u : grafo[v]) {
        if (estado[u] == NO_LO_VI) {
            treeEdges[v].insert(u);
            padre[u] = v;
            dfs(u, padre[u]);
        } else if (u != padre[v] && estado[u] == EMPECE_A_VER) {
            backConExtremoInferiorEn[u]++;
            backConExtremoSuperiorEn[v]++;
        }
    }
   
    estado[v] = TERMINE_DE_VER;
} 


vector<int> memo(0); //init en -1
int cubren(nodo v, nodo p = -1) {

    if (memo[v] != -1) return memo[v];
    int res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];

    for (nodo hijo : treeEdges[v]) if (hijo != p) {
        res += cubren(hijo, v);
    }

    memo[v] = res;
    return res;
}



vector<tuple<nodo,nodo>> aristaspuente(0);

void cantpuentes(vector<set<nodo>>& g){
    for (int i = 0;i < estado.size();i++) {
        if (estado[i] != TERMINE_DE_VER) {
            padre[i] = i;
            dfs(i, -1);

        }
    }

    for (int i = 1;i < estado.size();i++) {
        if (cubren(i) == 0) {
            aristaspuente.push_back(make_tuple(i,padre[i]));
        }   
    }

    for(int i = 0; i < aristaspuente.size(); i++){
        quitararista(g, get<0>(aristaspuente[i]) , get<1>(aristaspuente[i])); 
    }

}








vector<int> estadov2(0);
vector<set<nodo>> componentesconnodo(0); 



void dfsv2(vector<set<nodo>>& g ,nodo v, nodo p, nodo comp) {
    estadov2[v] = EMPECE_A_VER;
    for (nodo u : g[v]) {
        if (estadov2[u] == NO_LO_VI) {
            componentesconnodo[comp].insert(u);
            dfsv2(g, u, v,comp);
        }
        estadov2[v] = TERMINE_DE_VER;
    } 
}




void componentesseparadas(vector<set<nodo>>& g){
    int cantcomp = 0;    
    for (int i = 0;i < estadov2.size();i++) {
        if (estadov2[i] == NO_LO_VI) {
            componentesconnodo.push_back({});
            componentesconnodo[cantcomp].insert(i);
            dfsv2(g ,i,-1, cantcomp);    // ver como entra tipo orden capaz bug
            cantcomp ++;
        }
    }
}



vector<double> memfac(0);
double factorial(double n ){
    if( n == 1){
        return 1;
    }
    if (memfac[n] != -1){
        return memfac[n];
    }

    double temp = factorial(n-1)*n;
    memfac[n] = temp;

    return temp;
} 


long long probaParaGanar(vector<set<nodo>> componentes){
     long long formasdganar = 0;
    for (int i = 0; i < componentes.size();i++){
        long long tamano = componentes[i].size(); 
        if (tamano >= 2){
            formasdganar += (tamano*(tamano-1))/2;
        }
    }

    return formasdganar;
}





int main(){

    cin >> N; 


    memo = vector<int>(N, -1);   // para la prgramacion dinamica
    grafo = vector<set<nodo>>(N);
    treeEdges = grafo;

    cin >> M;

  
    estado = vector<int>(N,0);
    estadov2 = vector<int>(N,0);
    backConExtremoInferiorEn = vector<int>(N,0);
    backConExtremoSuperiorEn = vector<int>(N,0);
    padre = vector<nodo>(N,0);


    nodo u = 0;
    nodo w = 0;
    for(int i = 0; i < M ; i++){   //esta mal inicializado capaz nose aiuda nose contar
        cin >> u;
        cin >> w;
        grafo[u - 1].insert(w - 1);
        grafo[w - 1].insert(u - 1);
    }
    cantpuentes(grafo);   //saco los puntes
    componentesseparadas(grafo);

    long long p = probaParaGanar(componentesconnodo);       
    long long cantnodos = grafo.size();

    double formasdejjugar =  (cantnodos*(cantnodos-1))*0.5;
   
    double res = 1 - ((p*1.0)/formasdejjugar) ; 
    std::cout << std::fixed;
    std::cout << std::setprecision(5) << res ;
}

/* el del coso quimico anda4 4
10 11 1 2 1 7 1 10 10 9 7 8 8 9 2 3 2 6 6 5 5 4 4 3


4 4 1 2 1 3 1 4 2 4

*/
