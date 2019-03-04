#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;


class Vertex
{
public: int number; // инвивидуальный номер вершины
        bool visited = false;
        vector<pair <int ,int >> neighbourhood; // !!!пара. первый int - с кем связана данная вершина,
                                                // !!!      второй int - сколько стоит туда ребро
};



/// сам алгоритм
void boruvka(vector<Vertex*>& vertexes,  vector<Edge>& edges) {
    for (int i = 0; i < vertexes.size(); ++i) { // идем в лексикографическом порядке
        for (int j = 0; j < vertexes[i]->neighbourhood.size(); ++j) { // бежим по соседям
            // я искренне сочуствую человеку который будет проверять следующее условие, но ничего не могу поделать
            //
            if (vertexes[i]->neighbourhood[j].second )/*берем первый, тк уже отсортировали*/
                //&& !vertexes[vertexes[i]->neighbourhood[j].first]->visited) // если есть связь мы не были еще в вершине , в которую собираемся
            {
                //vertexes[vertexes[i]->neighbourhood[j].first]->visited = true; // то ставим вершину посещенной
                vertexes[i]->neighbourhood[j];
            }
        }
    }

    // return;
}





void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result) {
    vector<Vertex*> vertexes; // создаем вектор вершин

    /// присваиваем  элементы Vertex, присваиваем им номера
    for (int j = 0; j < N; ++j) {
        Vertex *a = new Vertex();
        a->number = j;
        vertexes.push_back(a);
    }


    /// присваиваем элемантам Vertex соседей
    int counter = 0; // с какой вершиной работаем
    for (int i = 0; i < M;) {       // бежим по соседям
        int start = edges[i].A;     // запоминаем
        while (edges[i].A == start && i < M) // пока элемент не поменялся
        {
            vertexes[edges[i].B]->neighbourhood.emplace_back(make_pair(edges[i].A, edges[i].W )); // записываем откуда куда и за сколько
            vertexes[edges[i].A]->neighbourhood.emplace_back(make_pair(edges[i].B, edges[i].W ));
            ++i; //двигаем
        }
        counter++;
    }


    /// сортируем пары во возрастанию
    for (int k = 0; k < vertexes.size(); ++k) {
        sort(vertexes[k]->neighbourhood.begin(),vertexes[k]->neighbourhood.end() ,
             []( auto& left,  auto& right){ return left.second < right.second; }
        );
    }

    boruvka(vertexes, edges);


    for (int k = 0; k < vertexes.size(); ++k) {
        for (int i = 0; i < vertexes[k]->neighbourhood.size(); ++i) {
            cout << "vertex \t"<< vertexes[k]->number << " got neighbourhood \t" << vertexes[k] ->neighbourhood[i] .first <<
                 "\t for \t" << vertexes[k] ->neighbourhood[i] .second << endl;
        }
        cout << "new" << endl;
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



/*
    edges

    0 1 1
    0 2 7
    0 3 9
    0 4 3

    1 2 10
    1 3 4
    1 4 5

    2 3 6
    2 4 8

    3 4 2
 */


