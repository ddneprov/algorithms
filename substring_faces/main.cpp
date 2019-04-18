#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void getBorders(string &s, string& res)
{
    int n = s.length();
    int p[n];
    p[0] = 0;
    int j;

    for(int i = 1; i < n; ++i)
    {
        j = p[i - 1];
        while(s[i] != s[j] && j > 0)
            j = p[j - 1];

        if (s[i] == s[j])
            p[i] = j + 1;
        else
            p[i] = j;
    }


    int l = -1;
    int i = p[n - 1];
    int arr[i];
    while(i != 0)
    {
        ++l;
        arr[l] = i;
        i = p[i - 1];
    }

    //складываем всё в одну строку
    for(int j = l; j >= 0; --j)
        res += s.substr(0, arr[j]) + "\n";
}


//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
	string input;
	string res;

	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		getline(fin, input);
		fin.close();
	}

	getBorders(input, res);

	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res;
	fout.close();

	return 0;
}
