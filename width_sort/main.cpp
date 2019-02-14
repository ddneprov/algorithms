#include "ReadWriter.cpp"

#include <fstream>
#include <exception>




/*///сортирует имена в линии
std::vector<Node> tort(std::vector<Node>& queue, std::vector<Node>& line, std::vector<Node>& result)
{
    std::vector<std::string> names;
    for (Node n : line)
        names.emplace_back(n.name);

    sort(names.begin(), names.end());
    result.insert(result.end(), names.begin(), names.end()); // сразу в ответ имена
    return line;
}*/


//Можно добавлять любые методы для решения задачи.

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node>& graph, int start, std::vector<std::string>& result) {

    std::vector<Node> queue; /// заводим вектор ( очередь )

    result.push_back(graph[start].name); /// выводим в ответ исток
    queue.push_back(graph[start]); /// запихиваем в очередь
    graph[start].visited = true; /// помечаем посещенным

    while (!queue.empty()) {
        std::vector<Node> line; //

        for (Node man : queue) /// бежим по главному стеку
        {
            for (Node *n2 : man.neighbours)  /// бежим по соседням стека
            {
                if (n2->visited == false) /// если не посещали ( не батя ) , то пушим и помечаем
                {
                    line.push_back(*n2);
                    n2->visited = true;
                }
            }

            //queue = tort(queue, line ,result);// что не так?

            std::vector<std::string> names;
            for (Node n : line)
                names.emplace_back(n.name);

            sort(names.begin(), names.end());
            result.insert(result.end(), names.begin(), names.end()); // сразу в ответ имена
            queue = line;
        }

    }
}



int main() {
    std::vector<Node> graph;
    std::vector<std::string> result;
    int start;

    ReadWriter rw;
    rw.readGraph(graph, start);
    solve(graph, start, result);
    rw.writeAnswer(result);
    return 0;
}





