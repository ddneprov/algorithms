#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>
using namespace std;







static int b = 12;


vector<int> order;
vector<bool> used;



void dfs(int v, vector<vector<bool>>& relations)
{
	used[v] = true;
	for(int i = 0; i < 12 /*relations[v].size()*/; ++i)
    {
	    bool a = !used[v];
	    bool b = relations[v][i];
        if (relations[v][i])
            dfs(v, relations);
    }

	order.push_back(v);
	cout << "vertex "<< v <<"\t"<<endl;
}





vector<vector<std::string>> getList(vector<string>& names, vector<vector<bool>>& relations)
{
	//int *pre = new int[names.size()];

    int n = relations[1].size();
    used.assign(n, false);
    //order.assign(n, 0);

    dfs(1, relations);
}

int main()
{
	vector<string> names = vector<string>();
	vector<vector<bool>> relations;
	int startIndex;

	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		string str = "";
		getline(fin, str);

		while (str != "#")
		{
			names.emplace_back(str.substr(str.find(' ') + 1));
			getline(fin, str);
		}

		relations = vector<vector<bool>>(names.size());

		for (int i = 0; i < names.size(); i++)
		{
			relations[i] = vector<bool>(names.size());
			for (int j = 0; j < names.size(); j++)
				relations[i][j] = false;
		}

		getline(fin, str);

		while (fin)
		{
			int a = stoi(str.substr(0, str.find(' '))) - 1;
			int b = stoi(str.substr(str.find(' '))) - 1;
			relations[a][b] = true;
			getline(fin, str);
		}

		fin.close();
	}

	vector<vector<string>> res = getList(names, relations);

	fstream fout;
	fout.open("output.txt", ios::out);
	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res[i].size(); j++)
			fout << res[i][j] << "\n";
		fout << "\n";
	}
	fout.close();

	return 0;
}