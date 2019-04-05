#include "ReadWriter.h"
using namespace std;


void relax(Edge edge, vector<int>& result)
{
    if (result[edge.B] > result[edge.A] + edge.W)
        result[edge.B] = result[edge.A] + edge.W;
}


vector<int> initialize(vector<Edge> &edges, int N, vector<int>& result)
{
    for (int i = 0; i < N; ++i)
        result.push_back(30001);
    result[0] = 0;
    return result;
}



void solve(int N, int M, vector<Edge>& edges, vector<int>& result)
{
    result = initialize(edges, N, result);
    for (int i = 1; i < N-1; ++i) {
        for(Edge edge : edges)
            relax(edge, result);
    }
    result.erase(result.begin());
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
    vector<int> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeIntValues(result);

    return 0;
}