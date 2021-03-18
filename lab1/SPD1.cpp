#include <iostream>
#include <fstream>

using namespace std;

int ilerazy;

int cmax(int n, int* R, int* P, int* Q, int* X) {
	int m = 0, c = 0;
	for (int i = 0; i < n; i++) {
		m = max(m, R[X[i]]) + P[X[i]];
		c = max(c, m + Q[X[i]]);
	} return c;
}

//void A(int n, int* R, int* P, int* Q, int* X) {
//
//	for (int i = 0; i < n; i++) X[i] = i;
//	int d = 0; 
//	for (int i = 1; i < n; i++) 
//		if (R[i] < R[d]) 
//			d = i;
//	swap(X[0], X[d]);
//	d = 0;
//	for (int i = 1; i < n; i++)
//		if (Q[i] < Q[d])
//			d = i;
//	swap(X[d], X[n - 1]);
//}

void ustaf(int n, int* R, int* P, int* Q, int* X)
{
	for (int i = 0; i < n; i++) X[i] = i;
	ilerazy = 0;
	int czasNajK = cmax(n, R, P, Q, X);					//ustaw domyslny czas jako najkrotszy
	int czas2; bool zamiana=true; //zmienne pomocnicze
	while (zamiana) {									//dopoki wykonuja sie zmiany
		zamiana = false;
		ilerazy++;
		for (int i = 0; i < n; i++)						//dla ka¿dego miejsca w kolejce
		{
			for (int j = 0; j < n; j++)					//znajdz kolejne miejsce w kolejce
			{
				if (i != j)								//rozne od tego pierwszego
				{
					swap(X[i], X[j]);					//zamien je miejscami
					czas2 = cmax(n, R, P, Q, X);		//zmierz czas
					if (czas2 > czasNajK)				//jesli czas jest dluzszy
					{
						swap(X[i], X[j]);				//ustaw tak jak bylo
					}
					else if (czas2 == czasNajK);		//zignoruj jesli rowne
					else
					{
						czasNajK = czas2;				//zapisz nowy czas jako najkrotszy
						zamiana = true;					//zapamietaj, ze dokonano zmiany
					}
				}
			}
		}
	}
}

int main() {

	int n, R[100], P[100], Q[100], X[100], caladlugosc=0;
	ifstream plik("rpq.data.txt");
	string stringi[] = { "data.1", "data.2", "data.3", "data.4"};
	string s;
	for(int k=0; k<4; k++){
		while (s != stringi[k]) plik >> s;
		plik >> n;
		for (int i = 0; i < n; i++) plik >> R[i] >> P[i] >> Q[i];

		//A(n, R, P, Q, X);
		ustaf(n, R, P, Q, X);
		cout << "\nKolejnosc zestawu danych nr "<<k+1<<":\n";
		for (int i = 0; i < n; i++) cout << X[i] + 1 << " ";
		caladlugosc += cmax(n, R, P, Q, X);
		cout << "\ncmax zestawu danych nr " << k + 1 << ":" << cmax(n, R, P, Q, X) << ". Algorytm wykonal sie "<< ilerazy-1<<" raz(y).\n";
	}
	cout << "Cala dlugosc: " << caladlugosc << endl;
}