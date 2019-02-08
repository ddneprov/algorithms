#include "ReadWriter.cpp"

//Можно добавлять любые методы для решения задачи.

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node>& graph, int start, std::vector<std::string>& result){
    //TODO
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
