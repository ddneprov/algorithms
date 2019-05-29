#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;


static string get_day(int N,int k)
{
    string str = "";
    int P[N]; // ?


    for (int i = 1; i < N + 1; ++i)
        P[i-1] = i;


    for (int l = 0; l < k - 1; ++l)
    {
        int i = N - 1;
        int j = N - 1;

        while (i > 0 && P[i] < P[i - 1])
            i--;

        while (P[j] < P[i - 1])
            j--;


        // меняем местами
        int s = P[i - 1];
        P[i - 1] = P[j];
        P[j] = s;

        for (int m = 0; m < ((N - i + 1) / 2); ++m)
        {
            int s = P[i + m];
            P[i + m] = P[N - m - 1];
            P[N - m - 1] = s;
        }
    }
    for (int m = 0; m < N; ++m)
        str += to_string(P[m]) + " ";

    str = str.substr(0, str.length() - 1);
    return str;
}






int main(int argc, const char * argv[]) {

    int n,N,K;
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    if(fin.is_open()) {
        string str;
        getline(fin,str);
        N = atoi( str.c_str());

        getline(fin,str);
        K = atoi( str.c_str());
        fout << get_day(N,K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}