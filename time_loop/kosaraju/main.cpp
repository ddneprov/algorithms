#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;


static int COUNT;  ///��������� ������� ( ������� )
/*
 *  ����� � �������, ��� 1
 */
void dfs(int v, vector<vector<bool>>& relations,  stack<int>& order, vector<bool>& used) {
		used[v] = true; // �������� ������� ��� ����������
		for(int i = 0; i < relations.size(); ++i) // ����� �� ������� ���������
			if (relations[v][i] && !used[i]) // ���� ���� ����� ��� �� ��� �� ����
				dfs(i, relations, order, used); // ���������� �������� �����

		order.push(v); // ���������� ������� � ���� � ������� �������� ���� ��������
}


/*
 *  ����� � ������� ������������������ ������, ��� 2-3
 */
void rev_dfs(int v, vector<vector<bool>>& relations, vector<string>& names , stack<int>& order, vector<bool>& used, vector<string>& block) {

		used[v] = true; // �������� ������� ��� ����������
		for(int i = 0; i < relations.size(); ++i) // ����� �� ������� ���������
			if (relations[i][v] && !used[i]) // ���� ���� ����� ��� �� ��� �� ����
				rev_dfs(i, relations, names, order, used, block); // ���������� �������� �����

		//order.pop(); // ���������� �������
		block.emplace_back(names[v]); /// ��������� � ���� �����
		++COUNT;
}


vector<vector<string>> getList(vector<string>& names, vector<vector<bool>>& relations) {

	vector<vector<string>> total_list; /// ������ ��������, ��������� � output.txt

	vector<bool> used (names.size(), false); /// ������ ��� �������� ����������������
	stack <int> order; /// ����, �������������� � dfs � rev_dfs ��� ������� ...
					   /// ...������ ������ � ������� �������� ����-��������


	for(int i = 0; i < relations.size(); ++i)
		if (!used[i])
			dfs(i, relations, order, used); // �������  ���� ��������

	used.assign(names.size(), false); // ����� ��������� false



	while (COUNT < names.size()) //������� ������� ������ �� ��������
	{
		if (!used[order.top()])
		{
			vector<string> block; /// ���� ����, ������� ���� ����� �������������
			rev_dfs(order.top(), relations, names , order, used, block); /// ��������� dfs-2
			sort(block.begin(), block.end()); /// ������������� ����� ������ �����
			total_list.emplace_back(block); /// �������� ���� � ������ ��������
			order.pop();
		}
		else
		{
			//++COUNT;
			order.pop(); // ���������� �������
		}
	}


	/// ��������� ����� �� ������� ��������
	sort(total_list.begin(), total_list.end(), [](vector<string> &left, vector<string> &right) {
		return left.front() < right.front();
	});

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

		///��������� "������"
		for (int i = 0; i < names.size(); i++)
		{
			relations[i] = vector<bool>(names.size());
			for (int j = 0; j < names.size(); j++)
				relations[i][j] = false;
		}

		getline(fin, str);

		///������� ���������
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