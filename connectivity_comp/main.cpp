#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;





void dfs(int v, vector<vector<bool>>& relations, vector<bool>& used, vector<string>& answer, vector<string>& names) {

    used[v] = true; // �������� ������� ��� ����������
    vector <int> layer;

    for(int i = 0; i < relations.size(); ++i)
        if(relations[v][i])
            layer.emplace_back(i);


    sort(layer.begin(), layer.end(), [&names](int &left, int &right) {
        return names[left] < names[right];
    });

    /*for(int i = 0; i < layer.size(); ++i) // ����� �� ������� ���������
        if (!used[i]) // ���� ���� ����� ��� �� ��� �� ����
            dfs(i, relations, used, answer, names); // ���������� �������� �����*/

    for(int i : layer)
        if(!used[i])
            dfs(i, relations, used, answer, names);

    answer.emplace_back(names[v]);
}



vector<string> getList(vector<string>& names, vector<vector<bool>>& relations) {


    vector<string> answer;
    vector<bool> used (names.size(), false);
    stack <int> order;

    vector <int> sources(names.size());
    bool sourse;

    /// ���������� ������
    for (int i = 0; i < relations.size(); ++i) {
        sourse = true;
        for (int j = 0; j < relations.size(); ++j) {
            if (relations[j][i])
                sourse = false;

        }
        if (sourse)
            sources.push_back(i);
    }




    /// �������� ������
    sort(sources.begin(), sources.end(), [names](int &left, int &right) {
        return names[left] < names[right];
    });




   /// ��������� dfs-1

    for(int& i : sources)
        if (!used[i])
            dfs(i, relations, used, answer, names);

    reverse(answer.begin(), answer.end());
    return answer;

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

    vector<string> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();

    return 0;
}