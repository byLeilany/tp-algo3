#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <tuple>
// #include <bits/stdc++.h>

using namespace std;

int dameS( tuple<int,int,int> a){
    return get<0>(a);
}

int dameF( tuple<int,int,int> a){
    return get<1>(a);
}

int dameI( tuple<int,int,int> a){
    return get<2>(a);
}

void ordenar(vector<tuple<int,int,int>> s){

}


// bool ordenarporsegundacomponente( tuple<int,int,int> &a , tuple<int,int,int> &b){

//     return (get<1>(a) < get<1>(b));
// }

vector<int> actividadesiter( vector<tuple<int,int,int>> s){
     
    vector<int> res;
    res.push_back(dameI(s[0]));
    int k = 0 ; 
    for (int m = 1; m < s.size() ; m++){
            if(dameS(s[m]) >= dameF(s[k])){
                res.push_back(get<2>(s[m]));    
                k = m;
            }

    }
    return res; 
}




int main (){
    int n = 0;
    cin >> n ;  
    int k =0;
    int j = 0 ; 
    vector<tuple<int,int,int>> s = {};

    vector<vector<tuple<int,int,int>>> baldes(2*n+1, vector<tuple<int,int,int>>(0)); //dani

    for(int i = 1; i <= n ; i++){
        cin >> j ;
        cin >> k ;
        // s.push_back(make_tuple(j,k,i));

        baldes[k].push_back(make_tuple(j,k,i));//dani
    }

    time_t start, end;
 time(&start);
    for(int i = 0; i < baldes.size(); i++){

        for(int j=0; j < baldes[i].size(); j++){
            s.push_back(baldes[i][j]);
        }


    }


    vector<int> res = actividadesiter( s);

    cout<< res.size() << endl;
    for( int i = 0 ; i< res.size()-1 ; i++){
        cout << res[i] << " ";

    }
    cout << res[res.size()-1];
}

/*
5 
6 7
1 4
0 3
4 10
3 6
*/
