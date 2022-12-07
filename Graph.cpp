//
// Created by Dallin on 12/1/22.
//

#include "Graph.h"


string Graph::toStringDependency() {
    stringstream out;

    out << "Dependency Graph" << endl;
    for ( auto node : dependencies ) {
        out << "R" << node.first << ":";
        int counter = 0;
        for ( auto depends : node.second ) {
            out << "R" << depends;
            if (counter < node.second.size() - 1) { out << ","; }
            counter++;
        }
        out << endl;
    }

    return out.str();
}

void Graph::loadMap(int size) {
    for (unsigned int i = 0; i < size; i++) {
        dependencies.insert({i, set<int>()});
        visited.push_back(false);
    }
    return; //your mum
}

void Graph::dfs(int node) {
    markVisted(node);
    auto edges = dependencies.at(node);
    for (auto edge : edges) {
        if(!isVisted(edge)) { dfs(edge); }
    }
    postorder.push_back(node);
    return;
}

vector<int> Graph::dfsForestPostOrder() {
    clearVisited();
    if (!postorder.empty()) { throw "Calling dfsForestPostOrder() after postorder already filled out"; }
    for (unsigned int i = 0; i < dependencies.size(); i++) {
        if (!isVisted(i)) { dfs(i); }
    }
    return postorder;
}

void Graph::clearVisited() {
    for (unsigned int i = 0; i < visited.size(); i++ ) {
        visited.at(i) = false;
    }
    return;
}

string Graph::postorderString() {
    stringstream out;
    out << "Postorder: ";
    for (auto x : postorder) {
        out << x << " ";
    }
    out << endl;
    return out.str();
}

vector<set<int>> Graph::dfsForestSCC( vector<int> thePostOrder ) {
    reverse(thePostOrder.begin(), thePostOrder.end());


    vector<set<int>> returnList;
    clearVisited();
    if (!postorder.empty()) { throw "Calling dfsForestSCC() after postorder already filled out"; }
    for (auto i : thePostOrder) {
        if (!isVisted(i)) {
            dfs(i);
            set<int> currentSCC;
            for (auto node : postorder) { currentSCC.insert(node); }
            postorder.clear();
            returnList.push_back(currentSCC);
        }
    }
    return returnList;
}

bool Graph::onlyHasSelfLoop(int node) {
    auto steve = dependencies.at(node);
    for (auto x : steve){
        return (steve.size() == 1) && (x == node);
    }
    return false;
}


