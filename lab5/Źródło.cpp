#include <iostream>
#include <fstream>
using namespace std;
int szrage(int N, int* R, int* P, int* Q, int* X)
{
    int t = 0, cmax = 0;
    int F[100];
    for (int i = 0; i < N; i++) {
        F[i] = 0;
    }
    for (int n = 0; n < N; n++)
    {
        int k = 0;
        for (int i = 0; i < N; i++)
        {
            if ((R[i] <= t) && (F[i] != 2))
            {
                F[i] = 1;
                k++;
            }
        }
        if (k == 0)
        {
            t = 999999;
            for (int i = 0; i < N; i++)
            {
                if (F[i] == 0)
                {
                    t = min(t, R[i]);
                }
            }
            for (int i = 0; i < N; i++)
            {
                if ((R[i] <= t) && (F[i] != 2))
                {
                    F[i] = 1;
                }
            }

        }
        int maxQ = -1;
        for (int i = 0; i < N; i++)
        {
            if ((F[i] == 1) && (maxQ < Q[i]))
            {
                maxQ = Q[i];
                k = i;
            }
        }
        X[n] = k;
        F[k] = 2;
        t += P[k];
        cmax = max(cmax, t + Q[k]);
    }
    return cmax;
}
int szrage_z_podzialem(int N, int* R, int* P, int* Q)
{
    int t = 0, cmax = 0;
    int F[100], Pp[100];
    for (int i = 0; i < N; i++) {
        Pp[i] = P[i];
    }
    for (int i = 0; i < N; i++) {
        F[i] = 0;
    }
    for (int n = 0; n < 2 * N; n++)
    {
        int k = 0;
        for (int i = 0; i < N; i++)
        {
            if ((R[i] <= t) && (F[i] != 2))
            {
                F[i] = 1;
                k++;
            }
        }
        if (k == 0)
        {
            t = 999999;
            for (int i = 0; i < N; i++)
            {
                if (F[i] == 0)
                {
                    t = min(t, R[i]);
                }
            }
            for (int i = 0; i < N; i++)
            {
                if ((R[i] <= t) && (F[i] != 2))
                {
                    F[i] = 1;
                }
            }

        }
        int maxQ = -1;
        for (int i = 0; i < N; i++)
        {
            if ((F[i] == 1) && (maxQ < Q[i]))
            {
                maxQ = Q[i];
                k = i;
            }
        }

        int Rk2 = 99999, p;
        for (int i = 0; i < N; i++)
        {
            if (F[i] == 0)
            {
                Rk2 = min(Rk2, R[i]);
            }
        }
        if (Pp[k] + t <= Rk2) {
            F[k] = 2;
            t += Pp[k];
            cmax = max(cmax, t + Q[k]);
        }
        else {
            p = Rk2 - t;
            Pp[k] -= p;
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
    if (szrage_z_podzialem(N, R, P, Q) >= UB)
    {
        return;
    }
    int sCmax = szrage(N, R, P, Q, X);
    if (sCmax < UB)
    {
        UB = sCmax;
    }
    int j, jr, jq;
    Blok(N, R, P, Q, X, j, jr, jq);
    if (j < 0)
    {
        return;
    }
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
    int N, R[100], P[100], Q[100], X[100];
    ifstream f("data.txt");
    string s;
    string data[] = { "data.000:", "data.001:", "data.002:", "data.003:","data.004:","data.005:","data.006:","data.007:","data.008:" };
    for (int x = 0; x < 9; x++)
    {
        while (s != data[x]) {
            f >> s;
        }

        f >> N;
        for (int i = 0; i < N; i++)
        {
            f >> R[i] >> P[i] >> Q[i];
        }
        /*    cout << "\n\nschr:\n" << Schrage(N, R, P, Q, X) << endl;
            for (int i = 0; i < N; i++)
                cout << X[i] + 1 << " ";

            cout << "\nschrpmtn:\n" << szrage_z_podzialem(N,R,P,Q) << endl;*/

        int UB = szrage(N, R, P, Q, X);
        Carlier(N, R, P, Q, X, UB);
        cout << "\ncarljer:\n" << UB << endl;

        for (int i = 0; i < N; i++)
        {
            cout << X[i] + 1 << " ";
        }

        cout << "\nuwaga prosze czekaæ liczy sie dugo\n";
        cout << endl;
    }

    return 0;
}