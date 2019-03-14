#include "ReadWriter.h"
using namespace std;

int static Komponent_number = 0;

class Vertex
{
public: int number; // инвивидуальный номер вершины
    int komponent_number = -1; /// номер компоненты связности, которому принадлежит данная Vertex
    vector<pair <int ,int >> neighbourhood; // !!!пара. первый int - с кем связана данная вершина,
                                            // !!!      второй int - сколько стоит туда ребро
};


/// сам алгоритм
vector<Edge> boruvka(vector<Vertex*>& vertexes,  vector<Edge>& edges,  vector<Edge>& result) {
    vertexes[0]->komponent_number = Komponent_number;

    for (int i = 0; i < vertexes.size(); ++i) { // бежим в лексикографическом
        if (vertexes[i]->neighbourhood[0].second != 99999) {

            Edge* new_edge = new Edge();
            new_edge->A = vertexes[i]->number;
            new_edge->B = vertexes[i]->neighbourhood[0].first;
            new_edge->W = vertexes[i]->neighbourhood[0].second;
            if (vertexes[new_edge->B]->komponent_number == -1) // если то куда мы идем не принадлежит никакой КС
            {
                vertexes[new_edge->B]->komponent_number = vertexes[i]->komponent_number;
            }
            else
            {
                Komponent_number++;

            }
            result.push_back(*new_edge);




            int j = 0;
            bool flag = true;
            while(j < vertexes[new_edge->B]->neighbourhood.size() && flag) {
                if (vertexes[new_edge->B]->neighbourhood[j].second == new_edge->W && vertexes[new_edge->B]->neighbourhood[j].first == new_edge->A) {
                    vertexes[new_edge->B]->neighbourhood[j].second = 99999;
                    vertexes[new_edge->B]->neighbourhood[j].first = 99999;
                    flag = false;
                }
            }
        }
    }
    return result;
}



void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result) {
    vector<Vertex*> vertexes; // создаем вектор вершин


    /// присваиваем  элементы Vertex, присваиваем им номера
    for (int j = 0; j < N; ++j) {
        Vertex *new_vertex = new Vertex();
        new_vertex->number = j;
        vertexes.push_back(new_vertex);
    }

    /// бегу по заданным ребрам и присваиваю элемантам Vertex соседей
    for (int i = 0; i < edges.size(); ++i) {       // бежим по соседям
        edges[i].number = -1; // обнуляю значение, тк буду использовать его иначе в boruvka()
        // ноль будет означать что ребро не входит на данный момент в остовное дерево
        // любое другое чисто будет означать номер компоненты связности к которому данное ребро принадлежит
        vertexes[edges[i].A]->neighbourhood.emplace_back(make_pair(edges[i].B, edges[i].W )); // ну и в другую сторону, тк ребро ,а не дуга
        vertexes[edges[i].B]->neighbourhood.emplace_back(make_pair(edges[i].A, edges[i].W )); // записываем откуда куда и за сколько
    }

    /// сортируем пары во возрастанию
    for (int k = 0; k < vertexes.size(); ++k) {
        sort(vertexes[k]->neighbourhood.begin(),vertexes[k]->neighbourhood.end() ,
             []( pair < int, int > & left,  pair < int, int>& right){ return left.second < right.second; }
        );
    }

    result = boruvka(vertexes, edges, result);
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