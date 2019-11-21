#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void alg_list() {
    const int inf = 100;
    const int empty = 0;
    const int not_visited = -1;

    int n;
    int source;
    int destination;
    ifstream inFile;

    inFile.open("C:\\Users\\Marcel\\CLionProjects\\algorytmy\\lab2\\test.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> n;
    inFile >> source;
    inFile >> destination;
    int** capacities = new int*[n];
    int arc = 0;
    int start;

    while (inFile >> start) {
        capacities[arc] = new int[3];
        capacities[arc][0] = start;
        inFile >> capacities[arc][1];
        inFile >> capacities[arc][2];
        arc++;
    }

    inFile.close();

    int max = 0;
    int flows[7][7] = {
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
    };

    while (true) {
        int bfs_previous_nodes[7] = {not_visited, not_visited, not_visited, not_visited, not_visited, not_visited, not_visited};
        bfs_previous_nodes[source] = -2;
        int extending_path[7] = {inf, inf, inf, inf, inf, inf, inf};
        queue<int> bfs_path;
        bfs_path.push(source);
        bool stop = true;
        while (!bfs_path.empty()) {
            int x = bfs_path.front();
            bfs_path.pop();
            for (int i = 0; i < n; i++) {
                if (capacities[i][0] == x) {
                    int y = capacities[i][1];
                    int value = capacities[i][2];
                    int cp = value - flows[x][y];
                    if (cp != 0 && bfs_previous_nodes[y] == not_visited) {
                        bfs_previous_nodes[y] = x;
                        extending_path[y] = min(extending_path[x], cp);
                        if (y == destination) {
                            max += extending_path[destination];
                            while (y != source) {
                                x = bfs_previous_nodes[y];
                                flows[x][y] += extending_path[destination];
                                flows[y][x] -= extending_path[destination];
                                y = x;
                            }
                            stop = false;
                            break;
                        }
                        bfs_path.push(y);
                    }
                }
            }
        }
        if (stop) {
            break;
        }
    }

    cout << "list algorithm" << "\n";
    cout << max << endl;

    for (int i = 0; i < n; i++) {
        int x = capacities[i][0];
        int y = capacities[i][1];
        int value = capacities[i][2];
        cout << x << " -> " << y << " " << flows[x][y] << ":" << value << endl;
    }
}

void alg_array() {
    const int inf = 100;
    const int empty = 0;
    const int not_visited = -1;
    int n = 7;
    int source = 2;
    int destination = 4;
    int capacity[7][7] = {
            {empty, 7,     empty, 3,     empty, empty, empty},
            {empty, empty, empty, 4,     6,     empty, empty},
            {9,     empty, empty, empty, empty, 9,     empty},
            {empty, empty, empty, empty, 9,     empty, 2},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, 3,     empty, empty, 6},
            {empty, empty, empty, empty, 8,     empty, empty},
    };
    int max = 0;
    int flows[7][7] = {
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty},
    };

    while (true) {
        int bfs_previous_nodes[7] = {not_visited, not_visited, not_visited, not_visited, not_visited, not_visited, not_visited};
        bfs_previous_nodes[source] = -2;
        int extending_path[7] = {inf, inf, inf, inf, inf, inf, inf};
        queue<int> bfs_path;
        bfs_path.push(source);
        bool stop = true;
        while (!bfs_path.empty()) {
            int x = bfs_path.front();
            bfs_path.pop();
            for (int y = 0; y < n; y++) {
                int cp = capacity[x][y] - flows[x][y];
                if (cp != 0 && bfs_previous_nodes[y] == not_visited) {
                    bfs_previous_nodes[y] = x;
                    extending_path[y] = min(extending_path[x], cp);
                    if (y == destination) {
                        max += extending_path[destination];
                        while (y != source) {
                            x = bfs_previous_nodes[y];
                            flows[x][y] += extending_path[destination];
                            flows[y][x] -= extending_path[destination];
                            y = x;
                        }
                        stop = false;
                        break;
                    }
                    bfs_path.push(y);
                }
            }
        }
        if (stop) {
            break;
        }
    }

    cout << "array algorithm" << "\n";
    cout << max << endl;

    for (int x = 0; x < n; x++)
        for(int y = 0; y < n; y++)
            if(capacity[x][y]) cout << x << " -> " << y << " " << flows[x][y] << ":" << capacity[x][y] << endl;
}

int main() {
    alg_list();
    alg_array();
    return 0;
}