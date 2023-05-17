#include <bits/stdc++.h>

using namespace std;



using nodo = int;

int N;
int M;

//funciones de grafos


 set<int> vecinos(vector<set<int>> g, nodo n){
    //vector<int> v;
    // for (int i = 0 ; i < g[n].size(); i++){
    //   if (g[n][i] == 1){
    //        v.push_back(i);
    //  }
    //}
    return g[n];
}


int cantnodos(vector<set<int>> g){
    return g.size();
}


void quitararista(vector<set<int>>& g, nodo u, nodo w){
    // g[u][w] = 0;
    g[u].erase(w);
    g[w].erase(u);
}

void ponerarista(vector<set<int>> g, nodo u, nodo w){
    // g[u][w] = 1;
    g[u].insert(w);
    g[w].insert(u);
}



//







int NO_LO_VI = 0; 
int EMPECE_A_VER = 1;
int TERMINE_DE_VER = 2;
vector<int> estado; //init en NO_LO_VI



vector<int> backConExtremoInferiorEn;
vector<int> backConExtremoSuperiorEn;
vector<set<int>> grafo;
vector<int> padre;
vector<set<int>> treeEdges; //init en []

void dfs(int v, int p) {
    estado[v] = EMPECE_A_VER;
    for (int u : grafo[v]) {
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


vector<int> memo; //init en -1
int cubren(int v, int p = -1) {

    vector <int> debug = backConExtremoInferiorEn;
    vector <int> debug1 = backConExtremoSuperiorEn;

    if (memo[v] != -1) return memo[v];
    int res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];

    for (int hijo : treeEdges[v]) if (hijo != p) {
        res += cubren(hijo, v);
    }

    memo[v] = res;
    return res;
}



vector< tuple<int,int>> aristaspuente ;

void cantpuentes(vector<set<int>>& g){
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








vector<int> estadov2;
vector<set<int>> componentesconnodo; 



void dfsv2(vector<set<int>>& g ,int v, int p, int comp) {
    estadov2[v] = EMPECE_A_VER;
    for (int u : g[v]) {
        if (estadov2[u] == NO_LO_VI) {
            componentesconnodo[comp].insert(u);
            dfsv2(g, u, v,comp);
        }
        estadov2[v] = TERMINE_DE_VER;
    } 
}




void componentesseparadas(vector<set<int>>& g){
    int cantcomp = 0;    
    for (int i = 0;i < estadov2.size();i++) {
        if (estadov2[i] == NO_LO_VI) {
            componentesconnodo[cantcomp].insert(i);
            dfsv2(g ,i,-1, cantcomp);    // ver como entra tipo orden capaz bug
            cantcomp ++;
        }
    }
}



vector<double> memfac;
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

double cuentaparaprobabilidad(vector<set<int>> componentes){
    double formasdganar = 0;
    for (int i = 0;i < componentes.size();i++){
        double tamano = componentes[i].size(); 
        if ( tamano >= 2 ){
           
            formasdganar += (tamano*(tamano-1))/2;
        }
    }

    // double formasdejjugar =  double(cantnodos*(cantnodos-1))*0.5;


    return formasdganar;
}





int main(){
    for(int i = 1; i < 100; i++){
        cout << i << " " << i+1 << "   ";
    }
    cout << 100 << " " << 1 << " ";
    for(int i = 101; i < 200; i++){
        cout << i << " " << i+1 << " ";
    }
    cout << 101 << " " << 200 << " ";


    cin >> N; 

    vector<int> copia(N,-1);
    memo = copia;   // para la prgramacion dinamica
    vector<set<int>> grafo1(N);
    componentesconnodo = grafo1;
    vector<int> copia2(N + 1,-1);
    vector<double> copiad(N + 1,-1);
    memfac = copiad;


    cin >> M;




    vector <bool> vistcopia(N,0);
  
    vector <int> estcopia(N,0);
    estado = estcopia;
    estadov2 = estcopia;
    padre = estcopia;
    backConExtremoInferiorEn = estcopia;
    backConExtremoSuperiorEn = estcopia;


    treeEdges = grafo1;



    int u = 0;
    int w = 0;
    for(int i = 0; i < M ; i++){   //esta mal inicializado capaz nose aiuda nose contar
        cin >> u;
        cin >> w;
        grafo1[u - 1].insert(w - 1);
        grafo1[w - 1].insert(u - 1);
    }
    grafo = grafo1;
    cantpuentes(grafo1);   //saco los puntes
    componentesseparadas(grafo1);

    vector<set<int>> debug = componentesconnodo;
    double p = 0;
    p = cuentaparaprobabilidad(componentesconnodo);
        
        

    int cantnodos = grafo.size();

    double formasdejjugar =  double(cantnodos*(cantnodos-1))/2;
   
    double res = 1 - (p/formasdejjugar) ; 
    std::cout << std::fixed;
    std::cout << std::setprecision(5) << res;
}

/* el del coso quimico anda
10 11 1 2 1 7 1 10 10 9 7 8 8 9 2 3 2 6 6 5 5 4 4 3
*/
