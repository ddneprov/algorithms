// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <cmath>

#include <iostream>
#include <iomanip>
#include <fstream>

#include <list>
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h



using namespace std;


void dfs2(int vertex, bool *&visited, int ** residue_graph, int N, int parent[])
{
    visited[vertex] = true;

    // Повторяется для всех вершин смежных с этой вершиной
    for(int i = 0; i != N; ++i)
        if(!visited[i] && residue_graph[vertex][i] > 0)
        {
            parent[i] = vertex;
            dfs2(i, visited, residue_graph, N, parent);
        }
}

// The function to do DFS traversal. It uses recursive DFSUtil()
bool dfs(int N, int ** residue_graph, int s, int t, int parent[])
{
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    // начиная с истока запускаем рекрусивную функцию
    dfs2(s, visited, residue_graph, N, parent);
    return visited[t];
}




bool bfs(int N, int ** residue_graph, int s, int t, int parent[]) {
    bool visited[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
    }

    // Создать очередь, ставим в очередь исходную вершину и отметить исходную вершину как посещенную
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front(); // берем первый элемент
        q.pop();
        for (int v=0; v < N; v++)
        {
            if (!visited[v] && residue_graph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                //cout << "parent " << v << " is " << u << endl;
                visited[v] = true;
            }
        }
    }

    // если есть связь то возвращаем тру, иначе фолс
    return (visited[t]);
}

int algorithm(int N, int ** graph, int s, int t, bool is_it_original) {
    int u, v;

    // создаем остаточный граф residue_graph и заполняем его исходными мощностями каждого ребра
    int ** residue_graph;
    residue_graph = new int*[N];
    for (int i = 0; i<N; i++)
        residue_graph[i] = new int[N];
    for (u = 0; u < N; u++)
        for (v = 0; v < N; v++)
            residue_graph[u][v] = graph[u][v];

    int parent[N];  // заполняется дфс и хранит путь
    int max_flow = 0;

    // пока существует путь увеличиваем поток
    while (is_it_original ? dfs(N, residue_graph, s, t, parent): bfs(N, residue_graph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) // раз есть путь идем
        {
            u = parent[v];
            path_flow = min(path_flow, residue_graph[u][v]); // если получилось меньше то берем меньшее
        }

        // обновляем остаточные емкости ребер
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            residue_graph[u][v] -= path_flow;
            residue_graph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }
    return max_flow;
}




///ищет все(!) истоки
vector<int> * getSources(int N, int ** graph) // 4 столбец
{
    int i = 0;
    vector <int> * sources = new vector<int>();
    for (int j = 0; j < N; ++j)
    {
        bool flag = true;
        for (i = 0; i < N; ++i)
        {
            if (graph[i][j] != 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            sources->push_back(j);
    }
    return sources;
}
///ищет все(!) стоки
vector<int> * getSinks(int N, int ** graph) // 1 строка
{
    vector<int> * sinks = new vector<int>();
    int j = 0;
    for (int i = 0; i < N; ++i)
    {
        bool flag = true;
        for (j = 0; j < N; ++j)
        {
            if (graph[i][j] != 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            sinks->push_back(i);
    }
    return sinks;
}









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool dinicBFS(int s, int t, int n, int ** g, int * level) {

    for (int i = 0; i < n; ++i)
        level[i] = -1;

    queue<int> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (level[v] < 0)
            {
                if  (g[u][v] > 0){
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    return level[t] < 0 ? false : true;
}

int dinicDFS(int u, int t, int flow, int n, int ** g, int * level) {
    if (u == t) return flow;
    for (int v = 0; v < n; v++) {
        if (level[v] == level[u]+1 && g[u][v]) {
            int f = min(flow, g[u][v]);
            int gargalo = dinicDFS(v, t, f, n , g, level);
            if (gargalo > 0) {
                g[u][v] -= gargalo;
                g[v][u] += gargalo;
                return gargalo;
            }
        }
    }
    return 0;
}

int dinicFlow(int N, int ** graph, int s, int t) {

    int gargalo;
    int level[N];
    int flow = 0;
    while (dinicBFS(s, t, N, graph, level)) {
        while (gargalo = dinicDFS(s, t, INT_MAX, N, graph, level)) {
            flow += gargalo;
        }
    }
    return flow;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



fstream f;
int main() {

    cout << "-- -- -- -- --  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --" << endl;
    /*vector<string> files{"input_10_0.0.txt", "input_10_0.5.txt", "input_10_1.0.txt", "input_10_disco.txt",
                         "input_310_0.0.txt", "input_310_0.5.txt", "input_310_1.0.txt", "input_310_disco.txt",
                         "input_610_0.0.txt", "input_610_0.5.txt", "input_610_1.0.txt", "input_610_disco.txt",
                         "input_910_0.0.txt", "input_910_0.5.txt", "input_910_1.0.txt", "input_910_disco.txt",
                         "input_1210_0.0.txt", "input_1210_0.5.txt", "input_1210_1.0.txt", "input_1210_disco.txt",
                         "input_1510_0.0.txt", "input_1510_0.5.txt", "input_1510_1.0.txt", "input_1510_disco.txt",
                         "input_1810_0.0.txt", "input_1810_0.5.txt", "input_1810_1.0.txt", "input_1810_disco.txt",
                         "input_2110_0.0.txt", "input_2110_0.5.txt", "input_2110_1.0.txt", "input_2110_disco.txt",
                         "input_2410_0.0.txt", "input_2410_0.5.txt", "input_2410_1.0.txt", "input_2410_disco.txt",
                         "input_2710_0.0.txt", "input_2710_0.5.txt", "input_2710_1.0.txt", "input_2710_disco.txt"};*/
    vector<string> files{"input_10_0.0.txt", "input_10_0.5.txt", "input_10_1.0.txt", "input_10_disco.txt"};

    int block_cheker = 0;
    f.open("out_file.xls", ios::out);

    //cout << "FILE NAME\t\t\t\t" << "  MAXIMUM FLOW OF GHRAPH\n";
    f << "\t" << "FF algorithm  " << "\t" << "  EK algorithm  " << "\t" << "Dinitz's algorithm\t" << endl;



    for (string file : files)
    {
        block_cheker++;
        ifstream in(file);

        if (in.is_open()) {
            //Число пробелов в первой строчке вначале равно 0
            int count_space = 0;
            char symbol;
            while (!in.eof())//на всякий случай цикл ограничиваем концом файла
            {
                in.get(symbol);//считали текущий символ
                if (symbol == '\t') count_space++;//Если это пробел, то число пробелов увеличиваем
                if (symbol == '\n') break;//Если дошли до конца строки, то выходим из цикла
            }

            //Опять переходим в потоке в начало файла
            in.seekg(0, ios::beg);
            in.clear();

            int n = count_space + 1;

            int **x;
            x = new int *[n];
            for (int i = 0; i < n; i++)
                x[i] = new int[n];


            int number;
            int i = 0, j = 0;
            while (in >> number) {
                x[i][j++] = number;
                if (j == n) {
                    i++;
                    j = 0;
                }
            }
            int answer = 0;
            int output[n];


            vector<int> *sources = getSources(n, x); //
            vector<int> *sinks = getSinks(n, x);
            if (!(sources->size() > 0 && sinks->size() > 0)) // если истоки и стоки существуют, то запускаем три алгоритма
                cout << "SOMETHING GONE WRONG" << endl;

            else {
/////////////////////////////////////////| Ford-Fulkerson Algorithm |///////////////////////////////////////////////////
                auto start = std::chrono::high_resolution_clock::now(); // засекаем врем
                for (int i : *sources)
                    for (int j : *sinks)
                        if (dfs(n, x, i, j, output))
                            answer += algorithm(n, x, i, j, true);

                cout << file << "\t\t ---FF---> \t" << answer << endl;
                auto finish = std::chrono::high_resolution_clock::now();
                f << file << "\t" << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();


/////////////////////////////////////////| Edmonds-Carp Algorithm |/////////////////////////////////////////////////////
                answer = 0;
                start = std::chrono::high_resolution_clock::now(); // засекаем врем
                for (int i : *sources)
                    for (int j : *sinks)
                        if (bfs(n, x, i, j, output))
                            answer += algorithm(n, x, i, j, false);

                cout << file << "\t\t ---EC---> \t" << answer << endl;
                finish = std::chrono::high_resolution_clock::now();
                f  << "\t" << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

/////////////////////////////////////////| Dinitz's algorithm |//////////////////////////////////////////////////////////
                answer = 0;
                start = std::chrono::high_resolution_clock::now(); // засекаем врем
                for (int i : *sources)
                    for (int j : *sinks)
                        if (bfs(n, x, i, j, output))
                            answer += dinicFlow(n, x, i, j);

                cout << file << "\t\t ---D---> \t" << answer << endl;
                finish = std::chrono::high_resolution_clock::now();
                f  << "\t" << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << endl;

            }

            /// отделяем каждые 4 файла
            if (block_cheker == 4) {
                f << "\n";
                block_cheker = 0;
            }
        } else
            cout << "file not exist";
    }
    f.close();
    return 0;
}






