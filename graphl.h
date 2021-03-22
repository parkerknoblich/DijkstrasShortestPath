// --------------------------------- graphl.h ---------------------------------
// Parker Knoblich CSS 343 A
// Created on July 19, 2020
// Last modified on August 1, 2020
// ----------------------------------------------------------------------------
// Purpose - to create a graph class capable of performing a 
//           Depth-First Search Traversal
// ----------------------------------------------------------------------------
// Specifications/Assumptions - each line in data file is formatted properly
//                            - each line in data file has valid data
//                            - node descriptions are 50 chars max
//                            - each graph has at most 100 nodes
//                            - uses an adjacency list to represent the graph

#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include "graphm.h" 

class GraphL {

public:
    
    // constructor
    GraphL();

    // destructor
    ~GraphL();

    // builds graph node information and adjacency list
    void buildGraph(ifstream&);

    // displays node information and its edges
    void displayGraph();

    // performs a depth-first search traversal of the graph
    void depthFirstSearch();  

private:

    // an edge in the graph
    struct EdgeNode {
        int adjGraphNode;
        EdgeNode* nextEdge;
    };

    // a node in the graph
    struct GraphNode {
        EdgeNode* edgeHead;
        NodeData* data;
        bool visited;
    };

    // builds graph node information
    bool createNodes(ifstream&);

    // adds edges to the graph
    void createEdges(ifstream&);

    // displays each node's edges
    void displayEdges(EdgeNode*, int);

    // prints the next node in the DFS traversal
    void depthFirstSearchHelper(int);

    // performs the actual DFS
    void depthFirstSearchRecursive(EdgeNode*);

    // removes all edges from the graph
    void deleteEdges(EdgeNode*);

    // an array of nodes
    GraphNode nodeArray[MAXNODES];

    // number of nodes in the graph
    int size;
};
#endif 