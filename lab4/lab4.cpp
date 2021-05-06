#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;


int Schrage(int N, int* R, int* P, int* Q, int* X) {
    
    int t = 0, cmax = 0;
    int F[100];
    for (int i = 0; i < N; i++)
    {
        F[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        
        int k = 0;
        for (int j = 0; j < N; j++)
        {
            if ((R[j] <= t) && (F[j] != 2))
            {
                F[j] = 1;
                k++;
            }
        }
        if (k == 0)
        {
            t = 999999;
            for (int j = 0; j < N; j++)
            {
                if (F[j] == 0)
                {
                    t = min(t, R[j]);
                }
            }
            for (int j = 0; j < N; j++)
            {
                if ((R[j] <= t) && (F[j] != 2))
                {
                    F[j] = 1;
                }
            }

        }
        int maxQ = -99999999;
        for (int j = 0; j < N; j++)
        {
            if ((F[j] == 1) && (maxQ < Q[j]))
            {
                maxQ = Q[j];
                k = j;
            }
        }
        X[i] = k;
        F[k] = 2;
        t += P[k];
        cmax = max(cmax, t + Q[k]);
    }
    return cmax;
}

int main()
{
    stringstream ss;
    string data = "data.", numer, dump;
    int N, R[100], P[100], Q[100], X[1000];
    int wynikSCH;
    double czasTotal = 0;

    ifstream plik("schr.data.txt");

    for (int i = 0; i <= 8; i++) {

        ss.str(string());
        ss << setw(3) << setfill('0') << i;
        numer = ss.str();

        while (dump != data + numer + ":")
            plik >> dump;

        plik >> N;

        for (int j = 0; j < N; j++)
            plik >> R[j] >> P[j] >> Q[j];

        auto start = chrono::high_resolution_clock::now();
        wynikSCH = Schrage(N, R, P, Q, X);
        auto end = chrono::high_resolution_clock::now();
        double czasns = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "data." << numer << ": CMAX: " << wynikSCH << ", czas: " << czasns << "us\n";
        cout << "Kolejnosc: ";
        for (int j = 0; j < N; j++) {
            cout << X[j]+1 << " ";
        }
        cout << endl;
        czasTotal += czasns;
    }
    cout << "\nCały czas: " << czasTotal << "us\n";
}

