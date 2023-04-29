#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

using namespace std;

//global:
int cant = 0;

int RES; 
int N = 1 ;
int nM= 0;

vector<vector<int>> cuadrado(N, vector<int>(N, 0));


void imprimeCuadrado(vector<vector<int>> TT){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(j==N-1){
				cout << TT[i][j];
			}else{
				cout << TT[i][j]<< " ";
			}
		}
		cout<<endl;
	}
}


void cantMagicAux(vector<vector<int>> TT, vector<int> v, int i, int j, int sumaparcial, vector<int> sumParCol, 
int sumDiagNeg, int sumDiagPos){

	if( i == N - 1  && j == N){
		// if(sumaparcial==nM && sumDiagNeg == nM && sumDiagPos == nM ){
			RES--;
			if(RES == 0){
				cuadrado = TT;
			}
//		 }
    }

    for(int k = 0; k < v.size() && RES > 0; k++){
		
		/*
		- veo que este disponible el numero k+1
		- si estoy en j>=n-2 => en mi sumFila + (k+1)'el numero que quiero poner' <= maxNumeroPosibleN*N 
		- YYYYyYyy el numero que falta por poner(nM - sumFila), esta disponible
		*/
        if(v[k] == 0 && (!(j>=N-2) || (nM-(sumaparcial+k+1) <= N*N && v[nM -(sumaparcial+k+1) -1 ] == 0 ) ) 
					 && (!(i>=N-2) || (nM - (sumParCol[j]+k+1) <= N*N && v[nM - (sumParCol[j]+k+1) -1 ] == 0 )) ){
			if ( sumaparcial + (k+1) > nM || sumParCol[j] + (k+1) > nM || (j == i && sumDiagNeg + (k+1) > nM) || (j == N-1 - i && sumDiagPos + (k+1) > nM) ){
				break;
			}
			
			v[k] = 1; 
			TT[i][j] = k+1;

			
			//forzar caso base
			if(j==N-1 && i == N-1 && sumParCol[j] + k+1 == nM && sumDiagNeg + (k+1) == nM && sumDiagPos == nM){
				cantMagicAux(TT , v, i, j+1, sumaparcial, sumParCol, sumDiagNeg + (k+1), sumDiagPos);
			}
			
			if(j < N-1){ 
                sumParCol[j] += k+1;

				if(i==N-1){ //ultima fila, y nM de col anda

					if(sumParCol[j] == nM){
						if(j==0 && sumDiagPos + (k+1) == nM){
							cantMagicAux(TT , v, i, j+1 , sumaparcial + (k+1), sumParCol, sumDiagNeg, sumDiagPos + (k+1)*(j == N-1 - i));
						}else if(j>0){
							cantMagicAux(TT , v, i, j+1 , sumaparcial + (k+1), sumParCol, sumDiagNeg, sumDiagPos);
						}
					}
					

				}else if(i<N-1){
					cantMagicAux(TT , v, i, j+1 , sumaparcial + (k+1), sumParCol, sumDiagNeg + (k+1)*(j == i), sumDiagPos + (k+1)*(j == N-1 - i));
				}

				sumParCol[j] -= k+1;
				

			}else { // estoy en caso (j == N - 1){
					
				sumParCol[j] += k+1;

				if (sumaparcial + (k+1) == nM){
					cantMagicAux(TT , v, i+1 , 0, 0, sumParCol, sumDiagNeg + (k+1)*(j == i), sumDiagPos + (k+1)*(j == N-1 - i));							
				}

				sumParCol[j] -= k+1;

	    	}
			v[k] = 0;
			TT[i][j] = 0;
			
    	}
		
	}


}

int main() {
	cin >> N >> RES; 
	nM = (pow(N,3) + N)/2; 



	vector<vector<int>> vectorresultante(N, vector<int>(N, 0));

	vector<int> ve (N*N, 0); 
	

	cantMagicAux(vectorresultante, ve, 0, 0, 0, vector<int> (N,0),0,0);

	if(RES == 0){
		//  cout << "el cuadrado k es :" << endl;
		imprimeCuadrado(cuadrado);
	}else{
		cout << -1 << endl;	
	}

    // cout<< "ve "<< cant << " iteraciones" <<endl;

  return 0;
}