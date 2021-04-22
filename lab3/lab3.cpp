#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace std;

int cmax(int N, int M, int* P, int* X)
{
    int T[100];
    for (int i = 0; i <= M; i++)
    {
        T[i] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            T[j] = max(T[j], T[j - 1]) + P[(j - 1) + X[i] * M];
        }
    }
    return T[M];
}
int NEH(int N, int M, int* P, int* X) {
    
    int* W = new int[N];
    for (int i = 0; i < N; i++) {
        W[i] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            W[i] += P[i * M + j];
        }
    }
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            if (W[j] < W[j + 1])
            {
                swap(W[j], W[j + 1]);
                swap(X[j], X[j + 1]);
            }
        }
    }
    delete[]W;
    for (int n = 0; n < N; n++)
    {
        int bestP = -1, bestCmax = 999999999;
        for (int p = n; p >= 0; p--)
        {
            int tmp = cmax(n + 1, M, P, X);
            if (bestCmax >= tmp)
            {
                bestCmax = tmp;
                bestP = p;
            }
            if (p)
            {
                swap(X[p], X[p - 1]);
            }
        }
        for (int i = 0; i < bestP; i++)
        {
            swap(X[i], X[i + 1]);
        }
    }
    return cmax(N, M, P, X);
}

int main()
{
    stringstream ss;
    string data="data.", numer, dump;
    int N, M, P[10000], X[1000];
    int wynikNEH;
    double czasTotal = 0;

    ifstream plik("neh.data.txt");

    for (int i = 0; i <= 120; i++) {
        
        ss.str(string());
        ss << setw(3) << setfill('0') << i;
        numer = ss.str();
    
        while (dump != data + numer + ":")
            plik >> dump;

        plik >> N >> M;

        for (int j = 0; j < N * M; j++)
            plik >> P[j];
        for (int j = 0; j < N; j++)
            X[j] = j;

        auto start = chrono::high_resolution_clock::now();
        wynikNEH = NEH(N, M, P, X);
        auto end = chrono::high_resolution_clock::now();
        double czasns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        cout << "data." << numer << ": CMAX: " << wynikNEH << ", czas: " << czasns*1e-9 << "s\n";
        czasTotal += czasns;
    }
    cout << "\nCały czas: " << czasTotal * 1e-9 << "s\n";

}