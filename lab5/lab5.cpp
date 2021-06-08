#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;

int Schrage(int N, int* R, int* P, int* Q, int* X) 
{
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
        int maxQ = -1;
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

int SchrageZP(int N, int* R, int* P, int* Q)
{
    int t = 0, cmax = 0;
    int F[100], pomoc[100];

    for (int i = 0; i < N; i++)
    {
        F[i] = 0;
        pomoc[i] = P[i];
    }
    for (int i = 0; i < 2 * N; i++) {

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
        int maxQ = -999999;
        for (int j = 0; j < N; j++)
        {
            if ((F[j] == 1) && (maxQ < Q[j]))
            {
                maxQ = Q[j];
                k = j;
            }
        }

        int minR = 999999, p;
        for (int j = 0; j < N; j++)
        {
            if (F[j] == 0)
            {
                minR = min(minR, R[j]);
            }
        }
        if (pomoc[k] + t <= minR) {
            F[k] = 2;
            t += pomoc[k];
            cmax = max(cmax, t + Q[k]);
        }
        else {
            p = minR - t;
            pomoc[k] -= p;
            t += p;
        }
    }
    return cmax;
}

void Blok(int N, int* R, int* P, int* Q, int* X, int& cI, int& cR, int& cQ)
{
    int posB = -1, m = 0, cmax = 0;
    int tmp[100];
    for (int i = 0; i < N; i++)
    {
        int j = X[i];
        tmp[i] = (m >= R[j]);
        m = max(m, R[j]) + P[j];
        if (cmax < m + Q[j])
        {
            cmax = m + Q[j];
            posB = i;
        }
    }
    int i = posB, j = -1;
    int bQ = Q[X[posB]];
    int bR = R[X[posB]];
    int bP = P[X[posB]];
    while (tmp[i])
    {
        if (Q[X[--i]] < bQ)
        {
            j = X[i];
            break;
        }
        bR = min(bR, R[X[i]]);
        bP += P[X[i]];
    }
    cI = j;
    cR = bR + bP;
    cQ = bQ + bP;
}

void Carlier(int N, int* R, int* P, int* Q, int* X, int& UB)
{
    if (SchrageZP(N, R, P, Q) >= UB)    return;

    int sCmax = Schrage(N, R, P, Q, X);

    if (sCmax < UB)     UB = sCmax;

    int j, jr, jq;

    Blok(N, R, P, Q, X, j, jr, jq);

    if (j < 0)      return;

    int tmpR = R[j];
    int tmpQ = Q[j];
    R[j] = jr;
    Carlier(N, R, P, Q, X, UB);
    R[j] = tmpR;
    Q[j] = jq;
    Carlier(N, R, P, Q, X, UB);
    Q[j] = tmpQ;
}

int main()
{
    stringstream ss;
    string data = "data.", numer, dump;
    int N, R[100], P[100], Q[100], X[1000];
    double czasTotal = 0;

    ifstream plik("carl.data.txt");

    for (int i = 0; i <= 8; i++) {

        ss.str(string());
        ss << setw(3) << setfill('0') << i;
        numer = ss.str();
        cout << numer << endl;
        while (dump != data + numer + ":")
            plik >> dump;

        plik >> N;

        for (int j = 0; j < N; j++)
            plik >> R[j] >> P[j] >> Q[j];

        auto start = chrono::high_resolution_clock::now();
        int UB = Schrage(N, R, P, Q, X);
        Carlier(N, R, P, Q, X, UB);
        auto end = chrono::high_resolution_clock::now();

        double czasms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "data." << numer << ": CMAX: " << UB << ", czas: " << czasms << "ms\n";
        cout << "Kolejnosc: ";
        for (int j = 0; j < N; j++) {
            cout << X[j] + 1 << " ";
        }
        cout << endl;
        czasTotal += czasms;
    }
    cout << "\nCały czas: " << czasTotal << "ms\n";
}