#include <iostream>
#include <math.h>
#include <vector>

#include<cstdlib>

using namespace std;

int64_t N;
int64_t R;
int64_t modulo;

vector<vector<int64_t>> cache;
vector<int64_t> v;

int64_t mod(int64_t a, int64_t b)
{
	return (a % b) + b*((a % b)<0);
}

int64_t modex(int64_t x, int64_t y, int64_t n){
	int64_t temp;
	int64_t dos = 2;

	if(y==0){
		return 1;
	}
	if(mod(y,2) == 0){
	
		temp = modex(x, y/dos, n);
		int64_t a = mod(temp*temp, n);
		return a;
	}else{
	
		temp = modex(x, y/dos, n);
		int64_t a = mod(mod(temp*temp, n)*x, n);
		return a;
	}
}

int64_t sumaMod(int64_t a, int64_t b){
	a = mod(a, modulo);
	b = mod(b, modulo);
	
	return mod( a+b, modulo );
}

int64_t restarMod(int64_t a, int64_t b){
	a = mod(a, modulo);
	b = mod(-b, modulo);
	
	return mod(a + b, modulo );
}

int64_t multMod(int64_t a, int64_t b){
	a = mod(a, modulo);
	b = mod(b, modulo);

	return mod( a*b, modulo );
}

bool op(int i, int64_t acum)
{

	if (i == v.size())
	{
		return cache[i][acum] = (acum == R);
	}

	if (cache[i][acum] != -1)
	{
		return cache[i][acum];
	}

	return cache[i][acum] = op(i + 1, sumaMod(acum, v[i])) || op(i + 1, restarMod(acum, v[i])) 
							|| op(i + 1, multMod(acum, v[i])) || op(i + 1, modex(acum, v[i], modulo));
}

/*
void dameTest(){

	// Providing a seed value
	srand((unsigned) time(NULL));

	for(int i = 0; i< N; i++){
		int random = rand() / 1000;
		cout<<random<< " ";
	}
	

}
*/

int main()
{
	// srand((unsigned) time(NULL));
	// int random = mod(rand(), 100);

	// cout<< random << " " << 111 << " " << 110<< " " ;
	int cantidad= 0;
	cin >>cantidad;

	for(int k =1; k<=cantidad; k++){

		v = {};
		cin >> N >> R >> modulo;
		
		// dameTest();



		int64_t k_i;
		for (int i = 0; i < N; i++) 
		{
			cin >> k_i;
			v.push_back(k_i);
		}
  cache = {};
	cache.resize(N + 1, vector<int64_t>(modulo, -1));
		//vector<vector<int64_t>> aber(N+1, vector<int64_t>(modulo, -1));
		//cache = aber;
		
		if(R >= modulo){
			cout<< "No" <<endl;
		}else{

			bool res = op(1, mod(v[0], modulo));

			if(res)
			{
				cout << "Si" << endl;
			}
			else
			{
				cout << "No" << endl;
			}

		}



	}
	return 0;
}

/*
13 0 11881
5 589589 589589 10 5 10 589589 10 5 10 5 10 57
*/

