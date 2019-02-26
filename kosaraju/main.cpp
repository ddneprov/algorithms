#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;


static int COUNT;  ///возможный костыль ( счетчик )
/*
 *  поиск в глубину, ШАГ 1
 */
void dfs(int v, vector<vector<bool>>& relations,  stack<int>& order, vector<bool>& used) {
		used[v] = true; // помечаем вершину как посещенную
		for(int i = 0; i < relations.size(); ++i) // бежим по матрице смежности
			if (relations[v][i] && !used[i]) // если есть связь где мы еще не были
				dfs(i, relations, order, used); // рекурсивно вызываем метод

		order.push(v); // записываем вершины в стек в порядке убывания пост значения
}


/*
 *  поиск в глубину транспонированного дерева, ШАГ 2-3
 */
void rev_dfs(int v, vector<vector<bool>>& relations, vector<string>& names , stack<int>& order, vector<bool>& used, vector<string>& block) {

		used[v] = true; // помечаем вершину как посещенную
		for(int i = 0; i < relations.size(); ++i) // бежим по матрице смежности
			if (relations[i][v] && !used[i]) // если есть связь где мы еще не были
				rev_dfs(i, relations, names, order, used, block); // рекурсивно вызываем метод

		//order.pop(); // вытаскиваю вершину
		block.emplace_back(names[v]); /// записываю в блок имена
		++COUNT;
}


vector<vector<string>> getList(vector<string>& names, vector<vector<bool>>& relations) {

	vector<vector<string>> total_list; /// вектор векторов, выводимых в output.txt

	vector<bool> used (names.size(), false); /// вектор для проверки использованности
	stack <int> order; /// стек, использующийся в dfs и rev_dfs для удобной ...
					   /// ...записи вершин в порядке убывания пост-значений


	for(int i = 0; i < relations.size(); ++i)
		if (!used[i])
			dfs(i, relations, order, used); // получил  пост значения

	used.assign(names.size(), false); // опять заполняем false



	while (COUNT < names.size()) //считает сколько вершин мы посетили
	{
		if (!used[order.top()])
		{
			vector<string> block; /// блок имен, которые надо будет отсортировать
			rev_dfs(order.top(), relations, names , order, used, block); /// запускаем dfs-2
			sort(block.begin(), block.end()); /// отсортировали имена внутри блока
			total_list.emplace_back(block); /// записали блок в вектор векторов
			order.pop();
		}
		else
		{
			//++COUNT;
			order.pop(); // вытаскиваю вершину
		}
	}


	/// сортируем блоки по первому элементу
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
