// --------------------------------- graphm.h ---------------------------------
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

#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h" 

// the maximum number of nodes in a graph
// (will actually only be 100 because indexing starts at 1)
const int MAXNODES = 101; 

class GraphM {

public:

    // constructor
    GraphM();

    // builds graph node information and adjacency matrix
    void buildGraph(ifstream&);

    // inserts an edge into the graph
    void insertEdge(int, int, int);

    // removes an edge from the graph
    void removeEdge(int, int);

    // finds the shortest path from every node to every other node
    void findShortestPath();

    // displays shortest path for every node
    void displayAll();

    // displays path for one node
    void display(int, int);

private:

    // builds graph node information
    bool createNodes(ifstream&);

    // creates the graph as an adjacency matrix
    void createAdjacencyMatrix(ifstream&); 

    // displays shortest path for one node
    void displayPath(int, int);

    // displays the node name in a path
    void displayLocations(int, int);

    // clears visited, distance, and path for all nodes
    void clearTable();

    // stores visited, distance, and path for one node
    struct TableType {
        bool visited;
        int dist;
        int path;
    };

    // data for graph nodes
    NodeData data[MAXNODES];

    // adjacency matrix that stores costs
    int cost[MAXNODES][MAXNODES];

    // number of nodes in the graph
    int size;

    // stores visted, distance, and path for all nodes
    TableType table[MAXNODES][MAXNODES];
};
#endif