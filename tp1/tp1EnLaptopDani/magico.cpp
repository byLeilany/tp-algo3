#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

using namespace std;

int N = 3;

int nM = (pow(N,3) + N)/2;

int RES = 0;
vector<int> ve (N*N, 0); 


bool esmagico(vector<int> TT){
	int ene = sqrt(TT.size()); //deberia ser 3 o 4 (el orden del cuadrado magico) 
	bool es = true;

    int tempfila = 0;
	int tempcolumna = 0;
	int tempdiagonal = 0; 
	
	int numMagico = 0;
	for(int i = 0; i < ene; i++){
		numMagico += TT[i];
	}


	int digNeg = 0;
	for(int i = 0; i<ene*ene; i += (ene+1)){
		digNeg += TT[i];
	}
	if(digNeg != numMagico){
		es = false;
	}


	int digPos = 0;
	for(int i = (ene-1); i<(ene*ene)-1; i += (ene-1)){
		digPos += TT[i];
	}
	if(digPos != numMagico){
		es = false;
	}

	for( int i = 0 ; i< ene ; i++){ 
			tempfila = 0;
			tempcolumna = 0;
			for(int j = 0 ; j < ene ; j++){
				tempfila = tempfila + TT[ene*(i) + j]; //anda

				tempcolumna = tempcolumna + TT[i+(ene*j)];  //anda
			}

			
			if(tempfila != numMagico || tempcolumna != numMagico ){
				es = false;
			}

	}

	return es;
}

bool sumaFilaElnM(vector<int> TT){
	int numMagico = 0;
	for(int i = 0; i < N; i++){
		numMagico += TT[i]+1;
	}
	// int secCol = 0;
	// for(int i = N; i < 2*N; i++){
	// 	secCol += TT[i];
	// }
	return numMagico == nM;

}

void imprimeCuadrado(vector<int> TT){
	cout << TT[0]+1 << "," << TT[1]+1 << "," << TT[2]+1 << endl;
	cout << TT[3]+1 << "," << TT[4]+1 << "," << TT[5]+1 << endl;
	cout << TT[6]+1 << "," << TT[7]+1 << "," << TT[8]+1 << endl;
}


void cantMagic(vector<int> TT, vector<int> v){
	if( N*N == TT.size()){
		if(esmagico(TT)){
			RES++;
			cout << "el cuadrado: " << RES << endl;
			imprimeCuadrado(TT);
			cout << "---------------" << endl;
		}
    }
	
    for(int k = 0; k < v.size(); k++){
        if(v[k] == 0){

			TT.push_back(k);
			v[k] = 1; 
		
			cantMagic(TT , v);

			v[k] = 0;
			TT.pop_back();
            
	    }
    }
	// cout<<RES<<endl;
	// return res;
}

int main() {
    vector<int> nums = {2,6,9,5,1,4,3,8};
    // vector<int> nums = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    if(esmagico(nums)){
	    cout << "siiii, es magico" << endl;
    }else{
	    cout << "troste :(" << endl;
    }

	
    vector<int> thiagoBB(0);
    cantMagic(thiagoBB, ve);


    cout << RES << endl; 
	// 

  return 0;
}

/*
el cuadrado: 1
2,7,6
9,5,1
4,3,8
---------------
el cuadrado: 2
2,9,4
7,5,3
6,1,8
---------------
el cuadrado: 3
4,3,8
9,5,1
2,7,6
---------------
el cuadrado: 4
4,9,2
3,5,7
8,1,6
---------------
el cuadrado: 5
6,1,8
7,5,3
2,9,4
---------------
el cuadrado: 6
6,7,2
1,5,9
8,3,4
---------------
el cuadrado: 7
8,1,6
3,5,7
4,9,2
---------------
el cuadrado: 8
8,3,4
1,5,9
6,7,2
---------------
*/