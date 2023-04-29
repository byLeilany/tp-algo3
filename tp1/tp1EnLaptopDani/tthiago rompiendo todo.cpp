#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

// vector<int> v = {4,4,7};
vector<int> v = {7,10,10,50};

//pruebas sin resta
// vector<int> v = {3,1,5,2,1}; //lo recibe x cin
// int w = pow(pow(3,5), 2) + 6;
// int w = 33;
// int w = 17;
// int w = 9;
int w = 10;	
int M = 5;

vector<vector<bool>> cache(v.size()+1, vector<bool>(w+1, false)); //row: |v|, colum: w

bool opant(int i, int acum){    


	if(i == v.size()){
		return (w == acum);
	}

    return opant(i+1, acum + v[i]) or opant(i+1, acum * v[i]) or opant(i+1,  pow(acum, v[i])) or opant(i+1,acum - v[i]) ;

}


bool opantM(int i, int acum){    


	if(i == v.size()){
		return (w == acum);
	}

    return opant(i+1, (acum + v[i]) % M) or opant(i+1, (acum * v[i]) % M) or opant(i+1,  int(pow(acum, v[i]))% M) or opant(i+1,(acum - v[i]) % M) ;

}



/*
bool op(int i, int acum){    


	if(i == v.size() && acum >= 0){
		return cache[i][acum] = (w == acum);
	}
	if(i == v.size() && acum < 0 ){
		return false;//(w == acum);
	}

	if(acum > w){
		return false;
	}

	if(acum >= 0 ){
		if(cache[i][acum] != false){
			return cache[i][acum];
		}	
    	
		return cache[i][acum] = op(i+1, acum + v[i]) or op(i+1, acum * v[i]) or op(i+1,  pow(acum, v[i])) or op(i+1,acum - v[i]);

	}else {
		return 	op(i+1, acum + v[i]) or op(i+1, acum * v[i]) or op(i+1,  pow(acum, v[i])) or op(i+1,acum - v[i]); 
	}

}
*/

int main() {

	// cout << opant(1, v[0]) << endl;

	bool res = opant(1, v[0]);
	bool resM = opantM(1, v[0]);


	cout << "sin Mod ...";
	if(res){
		cout << "se puede calcular! :-)" << endl;
	}else{
		cout << "noooooooooo" << endl;
	}

	cout << "con Mod "<< M <<" ...";
	if(resM){
		cout << "se puede calcular! :-)" << endl;
	}else{
		cout << "noooooooooo" << endl;
	}


  return 0;
}