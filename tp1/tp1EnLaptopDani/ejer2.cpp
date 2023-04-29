#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<long long> v = {};
long long R = 1;
long long modulo = 1;

vector<vector<long long>> cache(v.size() + 1, vector<long long>(modulo + 1, -1)); // row: |v|, colum: w

long long mod(long long a, long long b)
{
	long long res = a % b;
	if (res < 0)
	{
		res = res + b;
	}
	return res;
}

long long modex(long long x, long long y, long long n){
	if(y==0){
		return 1;
	}
	if(mod(y,2) == 0){
		long long temp = modex(x, y/2, n);
		return mod(temp*temp, n);
	}else{
		int temp = modex(x, y/2, n);
		return mod(mod(temp*temp, n)*x, n);

	}
}

bool opLento(int i, int acum)
{

	if (i == v.size())
	{
		return (mod(acum, modulo) == R);
	}
	bool temp = opLento(i + 1, (acum + v[i])) or opLento(i + 1, (acum * v[i])) or opLento(i + 1, modex(acum, v[i], modulo)) or opLento(i + 1, (acum - v[i]));

	return temp;
}


bool op(long long i, long long acum)
{

	if (i == v.size())
	{
		return cache[i][acum] = (acum == R);
	}

	if (cache[i][acum] != -1)
	{
		return cache[i][acum];
	}

bool temp1 = op(i + 1, mod((acum + v[i]), modulo));
bool temp2 = op(i + 1, mod((acum * v[i]), modulo));
bool temp3 = op(i + 1, modex(acum, v[i], modulo));
bool temp4 = op(i + 1, mod((acum - v[i]), modulo));// algo aca-==--=[[ ]] dios odio el teclado en ingles
bool ultratemp =  temp1 || temp2  || temp3  || temp4 ;

	return cache[i][acum] = ultratemp;
}



int main()
{

	long long N = 0;
	cin >> N >> R >> modulo;
	v.resize(N);
    cache = {};
	cache.resize(N + 1, vector<long long>(modulo + 1, -1));

	for (int i = 0; i < N; i++)
	{
		long long k_i;
		cin >> k_i;
		v[i] = k_i;
	}


	// cout << "res fast dice:";
	// if (cache[N][R] == 1)
	if(op(1, mod(v[0], modulo)))
	{
		cout << "Si" << endl;
	}
	else
	{
		cout << "No" << endl;
	}


	// cout << "" << endl;
	// bool resLenta = opLento(1, v[0]);
	// cout << "res lenta dice:";
	//  if(resLenta == true){
	//  	cout << "Si" << endl;
	//  }else{
	// 	cout << "No" << endl;
	//  }

	// vector<int> r = algunIndiceEnNegativo(cache);
	// cout << "en fila " << r[0] << endl;
	// cout << "en columna " << r[1] << endl;

	// vector<vector<int>> aber = cache;

	return 0;
}

/*
26 10 11
3 10 3 10 3 10 3 10 3 10 3 10 3 3 10 3 10 3 10 3 10 3 10 3 10 3
*/

