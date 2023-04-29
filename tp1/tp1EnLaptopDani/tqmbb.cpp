#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

using namespace std;

//global:

int RES = 8; 
int N = 3;
int nM= (pow(N,3) + N)/2;

vector<vector<int>> cuadrado(N, vector<int>(N, 0));


bool esMagicoDiag(vector<vector<int>> TT){
	/*bool es = true;
	
	for (int i = 0; i < N; i++){
		int tempF = 0;
		int tempC = 0;
		for (int j = 0; j < N; j++){
			tempF += TT[i][j];
			tempC += TT[j][i];
		}
		if(tempF != nM || tempC != nM){
			es = false;
		}
	}

	
1,2,15,16,
12,14,3,5,
13,7,10,4,
8,11,6,9,
	*/

	int temp = 0;
	int tempD = 0;

	for(int i= 0; i < N; i++){
		temp += TT[i][i];
		tempD += TT[i][N-1 - i];
	}

	// if(!(temp == nM && tempD == nM)){
	// 	es = false;
	// }

	return temp == nM && tempD == nM;
	// return es;
}



void imprimeCuadrado(vector<vector<int>> TT){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cout << TT[i][j]<< ",";
		}
		cout<<endl;
	}

}


void cantMagicAux(vector<vector<int>> TT, vector<int> v, int i, int j, int sumaparcial, vector<int> sumParCol){

	if( i == N - 1  && j == N){
		if(esMagicoDiag(TT)){
			RES--;
			if(RES == 0){
				// imprimeCuadrado(TT);
				cuadrado = TT;
			}
		}
    }


	if( i == 2 && j == 1 ){
		int r = 3;      
	}

    for(int k = 0; k < v.size() && RES > 0; k++){

        if(v[k] == 0){
			if ( sumaparcial + (k+1) > nM){
				break;
			}

			if(sumParCol[j] + (k+1) > nM){
				break;
			}

			v[k] = 1; 
			TT[i][j] = k+1;


			// if( i == N - 1  && j == N - 1 ){
			// 	cantMagicAux(TT , v, i, j , 0, sumParCol);  // fuerzo el caso base 
			// }

			
			if(j < N-1 && i < N){ // j < 3, i < 4
				
				sumParCol[j] += k+1;

				if(i==N-1 && sumParCol[j] == nM){
					cantMagicAux(TT , v, i, j+1 , sumaparcial + (k+1), sumParCol);

				}else if(i<N-1){
					cantMagicAux(TT , v, i, j+1 , sumaparcial + (k+1), sumParCol);
				}
				
				sumParCol[j] -= k+1;
				
				

			}else {

				if(j == N - 1 && i < N){
					
					sumParCol[j] += k+1;
					
					if(j==N-1 && i == N-1 && sumParCol[j] == nM){
						cantMagicAux(TT , v, i, j+1, sumaparcial, sumParCol);
					}

					if (sumaparcial + (k+1) == nM){
						cantMagicAux(TT , v, i+1 , 0, 0, sumParCol);							
					}

					sumParCol[j] -= k+1;


				}
	    	}
			v[k] = 0;
			TT[i][j] = 0;
			
    	}
	}


}

int main() {


	
	
	vector<int> ve (N*N, 0); 


    cout << "el nM es : " << nM << endl;
    

	cantMagicAux(cuadrado, ve, 0, 0, 0, vector<int> (N,0));

	if(RES == 0){
		cout << "el cuadrado k es :" << endl;
		imprimeCuadrado(cuadrado);
	}else{
		cout << "oopsi" << endl;	
	}

  return 0;
}



