#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;


struct Node
{
    Node()
    {
        value = -1;
        id = -1;
    }

    Node(int value, int id, int index)
    {
        this->value = value;
        indexes.push_back(id);
        this->id = id;
    }

    Node& concat(const Node& obj, int id)
    {
        this->value += obj.value;
        this->id = id;
        indexes.insert(indexes.end(), obj.indexes.begin(), obj.indexes.end());

        return *this;
    }

    struct less
    {
        bool operator()(const Node& first, const Node& second)
        {
            if(first.value == second.value)
                return first.id < second.id;
            return first.value > second.value;
        }
    };

    int value;
    vector<int> indexes;
    int id;
};


class Huffman
{
public:

    void build()
    {
        Node a, b;
        while(probabilities.size() > 1)
        {
            //Достаем минимальный элемент
            a = probabilities.top();
            probabilities.pop();

            //Достаем минимальный элемент
            b = probabilities.top();
            probabilities.pop();

            //записываем код для символа
            vector<int>::iterator it = a.indexes.begin();
            for(; it != a.indexes.end(); ++it)
                codes[*it] = '0' + codes[*it];

            //записываем код для символа
            it = b.indexes.begin();
            for(; it != b.indexes.end(); ++it)
                codes[*it] = '1' + codes[*it];

            //Суммируем элементы и кладем их в priority queue
            probabilities.push(a.concat(b, empty++));
        }
    }

    void addChance (int chance)
    {
        codes.emplace_back("");
        probabilities.push(Node(chance, empty, empty));
        ++empty;
    }


    string get (int i)
    {
        return codes[i];
    }

private:
    priority_queue<Node, vector<Node>, Node::less> probabilities;
    vector<string> codes;
    int empty = 0;

};


int main() {

    int n;
    Huffman * huff = new Huffman();
    fstream fin;
        fin.open("input.txt",ios::in);
        if(fin.is_open()) {
            fin >> n;
            for (int i = 0; i < n; i++) {
                int x;
                fin >> x;
               huff->addChance (x);
            }
    
            fin.close();
       
        huff->build();
        fstream fout;
        fout.open("output.txt",ios::out);
            for (int i = 0; i < n; i++){
                fout << huff->get(i) << (i==n-1?"":" ");
                }
        fout.close();
        delete huff;
            
        }
  
        return 0;

}

