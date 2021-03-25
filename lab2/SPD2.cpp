#include <iostream>
#include <fstream>
//#include <bitset>

using namespace std;

int main()
{

    int n, P[100], W[100], D[100]/*, X[100]*/;
    ifstream plik("witi.data.txt");
    string stringi[11] = { "data.10:", "data.11:", "data.12:", "data.13:", "data.14:",
                        "data.15:", "data.16:", "data.17:", "data.18:", "data.19:",
                        "data.20:" };
    string s;
    for (int razy = 0; razy < 11; razy++) {
        while (s != stringi[razy]) plik >> s;
        plik >> n;
        for (int i = 0; i < n; i++) plik >> P[i] >> W[i] >> D[i];
        //for (int i = 0; i < n; i++) cout << "P: " << P[i] << " W: " << W[i] << " D: " << D[i] << endl;

        int N = 1 << n;
        //cout << "N: " << N << endl;
        int* F = new int[N];
        F[0] = 0;

        for (int set = 1; set < N; set++) {
            int c = 0;
            for (int i = 0, b = 1; i < n; i++, b *= 2)
                if (set & b)   c += P[i];
            //cout << "C: " << c << endl;
            F[set] = 999999999;
            for (int i = 0, b = 1; i < n; i++, b *= 2) {
                if (set & b) {
                    F[set] = min(F[set], F[set - b] + max(W[i] * (c - D[i]), 0));
                    //tu miało miejsce szukanie sposobu zapamiętania permutacji optymalnej
                    //niestety zakończone niepowodzeniem
                    /*if (F[set] > (F[set - b] + max(W[i] * (c - D[i]), 0))) {

                        cout << "i: " << i << "    set: " << set;
                        cout << "    set:" << bitset<4>(set) << endl;
                        F[set] = (F[set - b] + max(W[i] * (c - D[i]), 0));
                        cout << "F[set-b]:" << F[set - b] << "    F[set]: " << F[set] << endl;
                    }*/
                }
            }
        }
        cout << "FN dla " << stringi[razy] << " ";
        cout << F[N - 1] << endl;
        cout << endl;
        /*for (int i = 0; i < N; i++)
            cout << "F[" << i << "]: " << F[i] << endl;*/
    }

    cin.get();
}

