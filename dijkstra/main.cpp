#include "ReadWriter.h"
#include <queue>
#include <algorithm>



using namespace std;

void relax(Edge edge,vector<int>& result)
{
    if (result[edge.B] > result[edge.A] + edge.W)
        result[edge.B] = result[edge.A] + edge.W;
}


vector<int> initialize(int N, vector<int>& result)
{
    for (int i = 0; i < N; ++i)
        result.push_back(30001);
    return result;
}

void solve(int N, int M, vector<Edge>& edges, vector<int>& result)
{
    initialize(N, result);
    vector<bool> was_used(N); // помогает определить использовали ли мы вершину?
    was_used[0] = true;
    result[0] = 0;

    vector<int> Q;
    Q.push_back(0);

    while (!Q.empty())
    {
        bool flag = false;// показывает нужно ли идти дальше по edges
        ///vector <int> selected;

        for (int i = 0; i < M; ++i) {
            if (edges[i].A == Q[0]) {            /// отбираем нужные ребра
                relax(edges[i], result);
                if (std::find(Q.begin(), Q.end(), edges[i].B) == Q.end() && !was_used[edges[i].B])// сейчас не в Q и не испоьзовали?
                {
                    flag = true; // мы считываем уже нужные ребра => когда выйдем - break, тк в нашем случае ребра идут в упорядоченном порядке
                    was_used[edges[i].B] = true;
                    Q.push_back(edges[i].B);
                    ///selected.push_back(edges[i].B); /// добавляем новые вершины
                }
            }
            else if (flag)
                break;
        }

        Q.erase(Q.begin()); // удаляем отработанный эл-те


        /*/// вставляем в нужное место
        for (int j = 0; j < selected.size(); ++j)
        {
            if (Q.empty())
                Q.push_back(selected[j]);
            else {
                for (int k = 0; k < Q.size(); ++k) {
                    if (result[selected[j]] < result[Q[k]])
                    {
                        if (k==0)
                            Q.insert(Q.begin(), selected[j]);
                        else
                            Q.insert(Q.begin() + k - 1 , selected[j]);
                        break;
                    }
                    else if(k == Q.size())
                    {
                        Q.push_back(selected[j]);
                    }
                }
            }
        }

        selected.clear();
*/
        // эта штуковина медленно работает, тк как сортирует все
        std::sort(Q.begin(), Q.end(), [result](int left, int right){return result[left] < result[right];});
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



