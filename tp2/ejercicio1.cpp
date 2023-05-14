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


 void quitararista(vector<set<int>>g, nodo u, nodo w){
  // g[u][w] = 0;
  g[u].erase(w);
  g[w].erase(u);
 }

void ponerarista(vector<set<int>> g, nodo u, nodo w){
 // g[u][w] = 1;
g[u].insert(w);
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
} else if (u != padre[v]) {
backConExtremoInferiorEn[v]++;
backConExtremoSuperiorEn[u]++;
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
vector<bool> visitado;
void cantpuentes(vector<set<int>> g){
for (int i = 0;i < visitado.size();i++) {
if (!visitado[i]) {
dfs(i, -1);

}
}

for (int i = 0;i < visitado.size();i++) {
if (cubren(i) == 0) {
aristaspuente.push_back(make_tuple(i,padre[i]));

}
}


vector< tuple<int,int>> debug = aristaspuente;
for(int i = 0; i < aristaspuente.size(); i++){
quitararista(g, get<0>(aristaspuente[i]) , get<1>(aristaspuente[i])); 

}

}







vector<bool> visitadov2;
vector<int> estadov2;
vector<set<int>> componentesconnodo; 



void dfsv2(int v, int p, int comp) {
estadov2[v] = EMPECE_A_VER;
for (int u : grafo[v]) {
if (estadov2[u] == NO_LO_VI) {
componentesconnodo[comp].insert(u);
dfsv2(u, v,comp);

}
estado[v] = TERMINE_DE_VER;
} 
}




void componentesseparadas(vector<set<int>> g){
 int cantcomp = 0;    
for (int i = 0;i < visitado.size();i++) {
if (!visitadov2[i]) {
dfsv2(i,-1, cantcomp);    // ver como entra tipo orden capaz bug
cantcomp ++;
}

}
}



vector<int> memfac;
int factorial(int n ){
if( n == 1){
    return 1;
}
 if (memfac[n] != -1){
 return memfac[n];

 }

int temp = factorial(n-1)*n;
memfac[n] = temp;

return temp;
} 

int cuentaparaprobabilidad(vector<set<int>> componentes){
int formasdganar = 0;
for (int i = 0;i < componentes.size();i++){
    if ( componentes[i].size() >= 2 ){
 formasdganar = factorial(componentes[i].size())/2*factorial(componentes[i].size()-2) + formasdganar;
    }
}

return formasdganar;
}





int main(){
  
  
  
    cin >> N; 

 vector<int> copia(N,-1);
  memo = copia;   // para la prgramacion dinamica
 vector<set<int>> grafo1(N);
 componentesconnodo = grafo1;
 vector<int> copia2(N + 1,-1);
 memfac = copia2;


    cin >> M;
 

  

 vector <bool> vistcopia(N,0);
visitadov2 = vistcopia;
visitado = vistcopia;

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
int p = 0;
p = cuentaparaprobabilidad(componentesconnodo);
    
    
    cout << p;
   cout << 1 - p;
}