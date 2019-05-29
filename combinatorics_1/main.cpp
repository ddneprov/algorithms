#include "BigIntegerAlgorithms.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;



static BigInteger FactTree(int n)
{
    BigInteger ways = 1;
    for (int i = 1; i < n + 1; ++i)
        ways *= i;

    return ways;
}
static BigInteger C(int n, int k)
{
    BigInteger a = 1;
    BigInteger b = 1;


    BigInteger c_count = 1;


    int nk = n - k + 1;
    for (int i = 1; i < n + 1; ++i)
        c_count *= i;

    for (int i = 1; i < k + 1; ++i)
        a *= i;

    for (int i = 1; i < nk; ++i)
        b *= i;


    return c_count / (a*b);
}



static BigInteger Pair (int n)
{
    BigInteger num = 1;
    for (int i = 1; i < (n - 2); i += 2)
        num *= (i + 2);
    return num;
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
        n = N;
        getline(fin,str);
        K = atoi( str.c_str());
        fout << FactTree(N)<< endl;
        fout << C(N,K)<< endl;
        fout << Pair(N)<< endl;
        fout.close();
        fin.close();
    }
    return 0;
}