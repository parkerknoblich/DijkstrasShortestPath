// --------------------------------- graphm.cpp ---------------------------------
// Parker Knoblich CSS 343 A
// Created on July 19, 2020
// Last modified on August 1, 2020
// ----------------------------------------------------------------------------
// Purpose - to create a graph class capable of performing Dijkstra's Algorithm
// ----------------------------------------------------------------------------
// Specifications/Assumptions - each line in data file is formatted properly
//                            - each line in data file has valid data
//                            - node descriptions are 50 chars max
//                            - each graph has at most 100 nodes
//                            - uses an adjacency matrix to represent the graph

#include "graphm.h"
#include <iostream>      // to display input/output
#include <fstream>       // to read contents of a text file
#include <iomanip>       // to use setw()
#include <limits>        // to skip to next line of text file
#include <climits>       // to use INT_MAX
using namespace std;

bool makingGraph = false;   // global bool that determines if the graph is
                            // currently being built

// ------------------------------- constructor --------------------------------
// description: constructs an adjacency matrix graph filled with "null" values
// preconditions: a user has requested to build a graph
// postconditions: a "null" valued adjacency matrix graph has been
//                   constructed; all edge costs are originally infinity
GraphM::GraphM() {
    for (int row = 1; row < MAXNODES; row++) {
        for (int col = 1; col < MAXNODES; col++) {
            table[row][col].dist = INT_MAX;
            table[row][col].visited = false;
            table[row][col].path = 0;
            cost[row][col] = INT_MAX; 
        }
    }
    size = 0; 
}

// -------------------------------- buildGraph --------------------------------
// description: builds graph node information and fills the adjacency matrix
// preconditions: an adjacency matrix graph has been constructed
// postconditions: the adjacency matrix graph will be full of the correct data
void GraphM::buildGraph(ifstream& infile) {
    bool success = createNodes(infile);
    if (success) {
        createAdjacencyMatrix(infile);
    }
}

// ------------------------------- createNodes --------------------------------
// description: builds graph node information
// preconditions: a user has requested to build a graph
// postconditions: all node names will be stored in an array
bool GraphM::createNodes(ifstream& infile) {
    infile >> size;
    if (size == 0 || infile.eof()) {
        return false;
    }
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 1; i <= size; i++) {
        data[i].setData(infile);
    }
    return true;
}

// -------------------------- createAdjacencyMatrix ---------------------------
// description: fills adjacency matrix graph with correct data
// preconditions: a positive number of nodes have been created
// postconditions: the adjacency matrix graph will be full of the correct data
void GraphM::createAdjacencyMatrix(ifstream& infile) {
    makingGraph = true;
    int from, to, distance;
    infile >> from >> to >> distance;
    for (;;) {
        if (from == 0 && to == 0 && distance == 0) {
            break;
        }
        insertEdge(from, to, distance);
        infile >> from >> to >> distance;
    }
    makingGraph = false;
}

// -------------------------------- insertEdge --------------------------------
// description: inserts an edge into the graph
// preconditions: the adjacency matrix graph has been made; data is valid
//                  (i.e. no error checking is required)
// postconditions: an edge has been successfully inserted into the graph;
//                   if the graph is not being built, the shortest paths
//                   are re-found
void GraphM::insertEdge(int from, int to, int distance) {
    cost[from][to] = distance;
    if (!makingGraph) {
        findShortestPath();
    }
}

// -------------------------------- removeEdge --------------------------------
// description: removes an edge from the graph
// preconditions: the adjacency matrix graph has been made; data is valid
//                  (i.e. no error checking is required)
// postconditions: an edge has been successfully removed from the graph;
//                   the edge costs are reset; the shortest paths are re-found
void GraphM::removeEdge(int from, int to) {
    cost[from][to] = INT_MAX;
    clearTable();
    findShortestPath();
}

// -------------------------------- clearTable --------------------------------
// description: resets all values of TableType to "null" values
// preconditions: an edge is being removed from the graph
// postconditions: TableType is cleared so that there are no conflicts when
//                   edges are reassigned when finding shortest path
void GraphM::clearTable() {
    for (int row = 1; row < MAXNODES; row++) {
        for (int col = 1; col < MAXNODES; col++) {
            table[row][col].dist = INT_MAX;
            table[row][col].visited = false;
            table[row][col].path = 0;
        }
    }
}

// ----------------------------- findShortestPath -----------------------------
// description: finds the shortest path from every node to every other node
// preconditions: the adjacency matrix graph has been made
// postconditions: the shortest path from every node to every other node is
//                   found and stored
void GraphM::findShortestPath() {
    for (int source = 1; source <= size; source++) {
    table[source][source].dist = 0;
    table[source][source].visited = true;
    for (int i = 1; i <= size; i++) {
        if (cost[source][i] != INT_MAX) {
            table[source][i].dist = cost[source][i];
            table[source][i].path = source;
        }
    }
    for (;;) {
        int smallestNeighborAmount = INT_MAX;
        int currNeighbor = 0;
        for (int n = 1; n <= size; n++) {
            if ((table[source][n].visited == false) && (table[source][n].dist
                                                   < smallestNeighborAmount)) {
                smallestNeighborAmount = table[source][n].dist;
                currNeighbor = n;
            }
        }
        if (currNeighbor == 0) {
            break;
        }
        table[source][currNeighbor].visited = true;
        for (int w = 1; w <= size; w++) {
            if ((table[source][w].visited == false) && 
                    (cost[currNeighbor][w] != INT_MAX) && 
                                      (currNeighbor != w)) {
                if (table[source][w].dist > table[source][currNeighbor].dist
                                                     + cost[currNeighbor][w]) {
                    table[source][w].dist = table[source][currNeighbor].dist
                                                       + cost[currNeighbor][w];
                    table[source][w].path = currNeighbor;
                }
            }
        }
    }
}
}

// -------------------------------- displayAll --------------------------------
// description: displays shortest path for every node
// preconditions: the shortest path information has been found
// postconditions: the shortest path has been displayed on screen for each node
void GraphM::displayAll() {
    cout << "Description" << setw(20) << "From node" << setw(10) << 
                                 "To node" << setw(14) << "Dijkstra's" 
                                            << setw(7) << "Path" << endl;
    for (int i = 1; i <= size; i++) {
        cout << data[i] << endl << endl;
        for (int j = 1; j <= size; j++) {
            if (i != j) {
                cout << setw(27) << i << setw(10) << j << setw(12);
                if (table[i][j].dist != INT_MAX) {
                    cout << table[i][j].dist << setw(10);
                    displayPath(i, j);
                }
                else {
                    cout << "----";
                }
                cout << endl;
            }
        }
    }
}

// --------------------------------- display ----------------------------------
// description: displays shortest path for one node
// preconditions: the shortest path information has been found
// postconditions: the shortest path has been displayed on screen for one node
void GraphM::display(int start, int end) {
    cout << start << setw(4) << end << setw(5);
    if (table[start][end].dist != INT_MAX) {
        cout << table[start][end].dist << setw(6);
        displayPath(start, end);
        cout << endl << endl;
        displayLocations(start, end);
    }
    else {
        cout << "   ----" << endl << endl;
    }
    cout << endl;
}

// ------------------------------- displayPath --------------------------------
// description: performs the actual displaying of the shortest path for a node
// preconditions: the shortest path information has been found
// postconditions: the shortest path has been displayed on screen for one node
void GraphM::displayPath(int start, int end) {
    if (start != end) {
        displayPath(start, table[start][end].path);
    }
    cout << end << " ";
}

// ----------------------------- displayLocations -----------------------------
// description: displays the names of the nodes in a shortest path
// preconditions: the shortest path information has been found
// postconditions: the name of the each node in a shortest path is displayed
void GraphM::displayLocations(int start, int end) {
    if (start != end) {
        displayLocations(start, table[start][end].path);
    }
    cout << data[end] << endl << endl;
}   