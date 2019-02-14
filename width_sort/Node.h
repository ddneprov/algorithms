//
// Created by Kirill Golovko on 06/02/2019.
//

#include <string>
#include <vector>


class Node {
public:
    std::string name;              /// название вершины
    std::vector<Node*> neighbours; /// список соседей
    bool visited = false;          /// была ли посещена
    Node(std::string& name) : name(name){};
};