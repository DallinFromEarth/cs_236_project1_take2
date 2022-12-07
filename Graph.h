//
// Created by Dallin on 12/1/22.
//

#ifndef PROJECT_1_GRAPH_H
#define PROJECT_1_GRAPH_H
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Graph {
private:
    map<int, set<int>> dependencies;
    vector<bool> visited;
    vector<int> postorder;
    vector<set<int>> listOfSCC;

public:
    Graph() {}

    void markVisted(int input) { visited.at(input) = true; }
    bool isVisted(int input) { return visited.at(input); }
    void clearVisited();

    void loadMap(int size);
    void addEdge(int origin, int destination) { dependencies.at(origin).insert(destination); }

    string toStringDependency();

    void dfs(int node);
    vector<int> dfsForestPostOrder();
    vector<set<int>> dfsForestSCC( vector<int> thePostOrder );

    string postorderString();

    bool onlyHasSelfLoop(int node);
};


#endif //PROJECT_1_GRAPH_H
