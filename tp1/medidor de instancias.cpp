#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;
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

vector<int> read_input(int size) {
    vector<int> input(2*size + 1); 
    string file_name = "/home/thiago/Desktop/prueba/inputsord/inputord" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name, ifstream::in);
    for (int i=0; i<2*size + 1; i++) {
        int casa;

        read_file >> casa;

        input[i] = casa;
    }
    read_file.close();
    return input;
}

double measure(vector<int> s) {
    auto start = chrono::high_resolution_clock::now();

    int cantFrajas = s[0];
    vector<tuple<int,int,int>> triplas;
    vector<vector<tuple<int,int,int>>> baldes(2*cantFrajas+1, vector<tuple<int,int,int>>(0));
    bool ord = true;
    int fAnt = s[2];

    for(int i = 1; i < s.size(); i += 2){
        int indice = (i+1)/ 2;
        tuple<int, int, int> datos = make_tuple(s[i], s[i+1], indice);

        triplas.push_back(datos);
        baldes[s[i+1]].push_back(datos);

        if(fAnt > s[i+1]){
            ord = false;
        }
        fAnt = s[i+1]; 
    }

    if(!ord){
        vector<tuple<int,int,int>> triplaOrd;
        for(int i = 0; i < baldes.size(); i++){ //O(n)
            for(int j=0; j < baldes[i].size(); j++){
                triplaOrd.push_back(baldes[i][j]);
            }
        }
        triplas = triplaOrd;
    }


    vector<int> res;
    res.push_back(dameI(triplas[0]));
    int k = 0 ; 
    for (int m = 1; m < triplas.size() ; m++){
            if(dameS(triplas[m]) >= dameF(triplas[k])){
                res.push_back(get<2>(triplas[m]));    
                k = m;
            }

    }

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
    
}
/*
*/

int main() {

    
    int repeat = 18;
    ofstream output_file; output_file.open("runtimeordenados.csv");
    output_file << "n,time\n";
    
    int limit = (1<<18)+1;
    for (int n=2; n<limit; n*=2) {
        vector<int> input = read_input(n);

        double counter = 0;
        for (int ignore=0; ignore<repeat; ignore++) counter += measure(input);
        
        output_file << n << "," << counter / repeat << endl;
    }

    output_file.close();
    /**/
    return 0;
}
