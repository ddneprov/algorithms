#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

stack <int> order;
vector<bool> used;
static int COUNT;
vector<vector<string>> total_list;
vector<string> block;

void dfs(int v, vector<vector<bool>>& relations, int n) {
	used[v] = true; // помечаем вершину как посещенную
	for(int i = 0; i < n; ++i) // бежим по матрице смежности
    {
        if (relations[v][i] && !used[i]) // если есть связь где мы еще не были
            dfs(i, relations, n); // рекурсивно вызываем метод
    }
	order.push(v); // записываем вершины в стек в порядке убывания пост значения
}



void rev_dfs(int v, vector<vector<bool>>& relations, int n, vector<string>& names)
{
	vector<string> block;
	used[v] = true; // помечаем вершину как посещенную
	for(int i = 0; i < n; ++i) // бежим по матрице смежности
	{
		if (relations[i][v] && !used[i]) // если есть связь где мы еще не были
			rev_dfs(i, relations, n, names); // рекурсивно вызываем метод
	}
	order.pop();
	block.push_back(names[v]);
	COUNT++;
	//cout << names[v] << endl;
}

vector<vector<string>> getList(vector<string>& names, vector<vector<bool>>& relations)
{
	int n = names.size();
	used.assign(n, false); // заполняем false
	dfs(0, relations, n); // получил по пост значениям
	used.assign(n, false); // опять заполняем false
	block.assign(12," ");

	while (COUNT < n)
	{
		rev_dfs(order.top(), relations, n, names);
		total_list.push_back(block);
		COUNT++;
		block.clear();
		//cout<<" "<<endl;
	}


	for (int i = 0; i < total_list.size(); ++i) {
		for (int j = 0; j < total_list[i].size(); ++j) {
			cout<<total_list[i][j];
		}
		cout<<"-"<<endl;
	}
	return total_list;
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

		///заполняем "нулями"
		for (int i = 0; i < names.size(); i++)
		{
			relations[i] = vector<bool>(names.size());
			for (int j = 0; j < names.size(); j++)
				relations[i][j] = false;
		}

		getline(fin, str);

		///таблица смежности
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