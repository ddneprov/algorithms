#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;


int find(int v, vector<int>& trees)
{
    if (v == trees[v]) //если дерево не менялось
        return v;
    return trees[v] = find(trees[v], trees);
}


void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    vector <int> trees(N);
    for (int k = 0; k < trees.size(); ++k) // первый шаг
        trees[k] = k;



    sort(edges.begin(), edges.end(), // второй
            [] ( Edge left, Edge right ) { return left.W < right.W ;});



    for(int i = 0; i < M; ++i)
    {
        /// запоминаем откуда и куда
        int from = edges[i].A, where = edges[i].B ;
        if( find(from, trees) != find(where, trees))
        {
            result.emplace_back(edges[i]);

            from = find(from, trees);
            where = find(where, trees);
            if (from != where)
            {
                if (rand() & 1)
                    swap(from, where);
                trees[from] = where;
            }
        }
    }
}



int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}