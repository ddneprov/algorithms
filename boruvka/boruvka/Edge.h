#include <string>

class Edge
{
public:
    int A;
    int B;
    int W;
    int number; // если -1 то не посещали ребро
    std::string print()
    {
        //short way to do it, without stringstream
        return std::to_string(A) + " " + std::to_string(B) + " " + std::to_string(W);
    }
};


