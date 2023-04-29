#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


vector<int> v = {3,1,5,2,1}; //lo recibe x ci
// int w = pow(pow(3,5), 2) + 6;  
// int w = 33;
int w = 17;
vector<vector<bool>> cache(v.size()+1, vector<bool>(w+1, false)); //row: |v|, colum: w

bool op(int i, int acum){    


	if(i == v.size()){
		return cache[i][acum] = (w == acum);
	}

	if(acum > w){
		return false;
	}
	
	if(cache[i][acum] != false){
		return cache[i][acum];
	}	


    return cache[i][acum] = op(i+1, acum + v[i]) or op(i+1, acum * v[i]) or op(i+1,  pow(acum, v[i]));

}

int main() {
	cout << op(0, 0) << endl;
  return 0;
}