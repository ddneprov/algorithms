#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;


struct Node
{
    
    Node() {
        value = -1;
        id = -1;
    }


    Node(int value, int id) {
        this->value = value;
        vec_indexes.push_back(id);
        this->id = id;
    }

    struct min {
        bool operator()(const Node& first,const Node& second)
        {
            if(first.value == second.value)
                return first.id < second.id;
            else
                return first.value > second.value;
        }
    };

    Node& Сhange(const Node& node,int id) {
        this->value += node.value;
        this->id = id;


        vec_indexes.insert(vec_indexes.end(), node.vec_indexes.begin(), node.vec_indexes.end());
        return *this;
    }


    int value; // значение ноды
    int id; // порядковый номер
    vector<int> vec_indexes;

    
};





class Huffman
{
public:

    void build()
    {
        Node a, b;
        while(probabilities.size() > 1)
        {

            /// берем верхние
            a = probabilities.top();
            probabilities.pop();
            //cout <<  "\t a = " << a.value;
            //cout <<  "\t b = " << b.value;

            b = probabilities.top();
            probabilities.pop();

            vector<int>::iterator W = a.vec_indexes.begin();
            while(W != a.vec_indexes.end()) { // непосредственно запись
                codes[*W] = '0' + codes[*W];
                ++W;
            }

            W = b.vec_indexes.begin();
            while(W != b.vec_indexes.end()) {
                codes[*W] = '1' + codes[*W];
                ++W;
            }


            Node node = a.Сhange(b, ++empty);
            probabilities.push(node);
        }
    }

    void addChance (int chance)
    {
        codes.emplace_back("");
        //cout << "chance" << chance;
        //cout << " ---- " << endl;
        probabilities.push(Node(chance, empty));
        ++empty;
    }


    string get (int i)
    {
        return codes[i];
    }

private:
    priority_queue<Node, vector<Node>, Node::min> probabilities;
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

