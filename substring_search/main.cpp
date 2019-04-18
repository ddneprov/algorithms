#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
void getSubstrings(string& source, string& substring, vector<int>& res)
{
    int a = substring.length();
    int n = a + source.length() + 1;
    string s = substring + "\n" + source;

    if(a == 0)
        return;

    int arr[n];
    arr[0] = 0;
    int j;
    for(int i = 1; i < n; ++i)
    {
        j = arr[i - 1];
        while(s[i] != s[j] && j > 0)
            j = arr[j - 1];


        if (s[i] == s[j])
            arr[i] = ++j;
        else
            arr[i] = j;
        
        if(j == a) // если встретили то добавляем индекс
            res.push_back(i - 2 * a);
    }
}


//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
	string t;
	string p;
	vector<int> res;

	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		getline(fin, t);
		getline(fin, p);
		fin.close();
	}

	getSubstrings(t, p, res);

	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res.size() << "\n";
	for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
		fout << *i << "\n";
	fout.close();

	return 0;
}
