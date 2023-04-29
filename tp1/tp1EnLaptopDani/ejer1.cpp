#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

using namespace std;

//global:
int cant = 0;

int RES; 
int N = 1 ;
int nM= (pow(N,3) + N)/2;

vector<vector<int>> cuadrado(N, vector<int>(N, 0));



bool esMagicoDiag(vector<vector<int>> TT){
	 int temp = 0;
	int tempD = 0;

	for(int i= 0; i < N; i++){
		 temp += TT[i][i];
		tempD += TT[i][N-1 - i];
	}
	return tempD == nM; //temp == nM && 
}



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
		cant++;

//		 if(esMagicoDiag(TT)){
//        cout<<"este es el cuadrado "<< cant<<endl;
//        imprimeCuadrado(TT);
//        cout<<"................."<<endl;
		// if(sumaparcial==nM && sumDiagNeg == nM && sumDiagPos == nM ){
			RES--;
			if(RES == 0){
				cuadrado = TT;
			}
//		 }
    }

    for(int k = 0; k < v.size() && RES > 0; k++){

        if(v[k] == 0){
			if ( sumaparcial + (k+1) > nM){
				break;
			}

			if(sumParCol[j] + (k+1) > nM){
				break;
			}

			if(j == i && sumDiagNeg + (k+1) > nM){
				break;
			}
			if(j == N-1 - i && sumDiagPos + (k+1) > nM){
				break;
			}

			v[k] = 1; 
			TT[i][j] = k+1;
			
			if(j < N-1 && i < N){ // j < 3, i < 4
                sumParCol[j] += k+1;

				if(j == i){
					sumDiagNeg += k+1;
				}
				if(j == N-1 - i){
					sumDiagPos += k+1;
				}
//capaz hay que utilizar el *bool, para pasarle o no el valor de sumDiagonales. en vez de agregar y quitar el valor k+1
				if(i==N-1 && sumParCol[j] == nM){
					if(j==0 && sumDiagPos == nM){
						cantMagicAux(TT , v, i, j+1 , sumaparcial + (k+1), sumParCol, sumDiagNeg, sumDiagPos);
					}else if(j>0){
						cantMagicAux(TT , v, i, j+1 , sumaparcial + (k+1), sumParCol, sumDiagNeg, sumDiagPos);
					}
				}else if(i<N-1){
					cantMagicAux(TT , v, i, j+1 , sumaparcial + (k+1), sumParCol, sumDiagNeg, sumDiagPos);
				}
				


				sumParCol[j] -= k+1;
				if(j == i){
					sumDiagNeg -= k+1;
				}

				if(j == N-1 - i){
					sumDiagPos -= k+1;
				}
				

			}else {

				if(j == N - 1 && i < N){
					
					sumParCol[j] += k+1;
					if(j == i){
						sumDiagNeg += k+1;
					}
					if(j == N-1 - i){
						sumDiagPos += k+1;
					}
					
					
					if(j==N-1 && i == N-1 && sumParCol[j] == nM && sumDiagNeg == nM){
						cantMagicAux(TT , v, i, j+1, sumaparcial, sumParCol, sumDiagNeg, sumDiagPos);
					}

					if (sumaparcial + (k+1) == nM){
						cantMagicAux(TT , v, i+1 , 0, 0, sumParCol, sumDiagNeg, sumDiagPos);							
					}

					sumParCol[j] -= k+1;
					if(j == i){
						sumDiagNeg -= k+1;
					}
					if(j == N-1 - i){
						sumDiagPos -= k+1;
					}

				}
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

    cout<< "ve "<< cant << " cuadrados" <<endl;

  return 0;
}




/*
 * 1
2 7 6
9 5 1
4 3 8

3 2
2 9 4
7 5 3
6 1 8


 3 3
4 3 8
9 5 1
2 7 6


*/