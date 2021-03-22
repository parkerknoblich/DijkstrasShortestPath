// --------------------------------- graphl.cpp ---------------------------------
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

#include "graphl.h"
#include <iostream>    // to display input/output
#include <fstream>     // to read contents of a text file
#include <iomanip>     // to use setw()
#include <limits>      // to skip to next line of text file
#include <climits>     // to use INT_MAX
#include <map>         // to check for duplicate edges
using namespace std;

// ------------------------------- constructor --------------------------------
// description: constructs an adjacency list graph filled with "null" values
// preconditions: a user has requested to build a graph
// postconditions: a "null" valued adjacency list graph has been constructed
GraphL::GraphL() {
    for (int i = 1; i < MAXNODES; i++) {
        nodeArray[i].edgeHead = nullptr;
        nodeArray[i].data = new NodeData();
        nodeArray[i].visited = false;
    }
}

// -------------------------------- destructor --------------------------------
// description: destructs an adjacency list graph
// preconditions: an adjacency list graph has been constructed
// postconditions: all memory of an adjacency list graph has been deallocated
GraphL::~GraphL() {
    for (int i = 1; i < MAXNODES; i++) {
        EdgeNode* curr = nodeArray[i].edgeHead;
        if (curr != nullptr) {
            deleteEdges(curr);
        }
        delete nodeArray[i].data;
    }
}

// -------------------------------- deleteEdges -------------------------------
// description: deletes/deallocates all edges of an adjacency list graph
// preconditions: an adjacency list graph has been constructed
// postconditions: all edge memory of an adjacency list graph has been
//                    deallocated
void GraphL::deleteEdges(EdgeNode* curr) {
    if (curr->nextEdge != nullptr) {
        deleteEdges(curr->nextEdge);
    }
    delete curr;
    curr = nullptr;
}

// -------------------------------- buildGraph --------------------------------
// description: builds graph node information and adjacency list
// preconditions: an adajcency list graph has been constructed
// postconditions: the adjacency list graph will be full of the correct data
void GraphL::buildGraph(ifstream& infile) {
    bool success = createNodes(infile);
    if (success) {
        createEdges(infile);
    }
}

// -------------------------------- createNodes -------------------------------
// description: builds graph node information
// preconditions: a user has requested to build a graph
// postconditions: all node names will be stored in the adjacency list
bool GraphL::createNodes(ifstream& infile) {
    infile >> size;
    if (size == 0 || infile.eof()) {
        return false;
    }
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 1; i <= size; i++) {
        nodeArray[i].data->setData(infile);
    }
    return true;
}

// -------------------------------- createEdges -------------------------------
// description: adds edges to the adjacency list graph in the correct location;
//                does not add duplicate edges
// preconditions: the adjacency list graph has been constructed
// postconditions: non-duplicative edges are added to the adjacency list in
//                   reverse order for each node (i.e. in ascending order)
void GraphL::createEdges(ifstream& infile) {
    multimap<int, int> pairs;
    int from, to;
    infile >> from >> to;
    for (;;) {
        if (from == 0 && to == 0) {
            break;
        }
        bool exists = false;
        for (pair<int, int> pair : pairs) {
            if (pair.first == from && pair.second == to) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            pairs.insert(pair<int, int>(from, to));
            EdgeNode* newNode = new EdgeNode();
            newNode->adjGraphNode = to;
            newNode->nextEdge = nullptr;
            if (nodeArray[from].edgeHead == nullptr) {
                nodeArray[from].edgeHead = newNode;
            }
            else {
                newNode->nextEdge = nodeArray[from].edgeHead;
                nodeArray[from].edgeHead = newNode;
            }
        }
        infile >> from >> to;
    }
}

// ------------------------------- displayGraph -------------------------------
// description: displays each node information and its edges
// preconditions: the adjacency list graph has been filled
// postconditions; each node name and its edges are displayed on screen
void GraphL::displayGraph() {
    cout << "Graph:" << endl;
    for (int i = 1; i <= size; i++) {
        cout << "Node" << i << "       " << *nodeArray[i].data << endl << endl;
        EdgeNode* curr = nodeArray[i].edgeHead;
        displayEdges(curr, i);
    }
}

// ------------------------------- displayEdges -------------------------------
// description: displays each edge coming from a node to another node
// preconditions: the adjacency list graph has been filled
// postconditions: each edge of a node is displayed on screen
void GraphL::displayEdges(EdgeNode* curr, int from) {
    if (curr == nullptr) {
        return;
    }
    else {
        cout << "  edge  " << from << "  " << curr->adjGraphNode << endl;
        displayEdges(curr->nextEdge, from);
    }
}

// ----------------------------- depthFirstSearch -----------------------------
// description: performs a depth-first search traversal of the graph
// preconditions: the adjacency list graph has been constructed
// postconditions: the depth-first search ordering is displayed on screen
void GraphL::depthFirstSearch() {
    cout << endl << "Depth-first ordering:";
    for (int i = 1; i <= size; i++) {
        if (nodeArray[i].edgeHead != nullptr && nodeArray[i].visited 
                                                           == false) {
            depthFirstSearchHelper(i);
        }
    }
    cout << endl << endl;
}

// -------------------------- depthFirstSearchHelper --------------------------
// description: marks an unvisted node as "true" and prints its name
// preconditions: this node has not been visited yet in the DFS
// postconditions: this node has now been visited
void GraphL::depthFirstSearchHelper(int currNode) {
    nodeArray[currNode].visited = true;
    cout << " " << currNode;
    EdgeNode* currEdge = nodeArray[currNode].edgeHead;
    depthFirstSearchRecursive(currEdge);
}

// ------------------------ depthFirstSearchRecursive -------------------------
// description: recursively visits each unvisited node in the DFS
// preconditions: the current node has been visited and possibly has
//                  unvisited neighbors
// postconditions: the next unvisited neighbor has been added to the DFS
void GraphL::depthFirstSearchRecursive(EdgeNode* currEdge) {
    if (currEdge == nullptr) {
        return;
    }
    else {
        if (nodeArray[currEdge->adjGraphNode].visited == false) {
            depthFirstSearchHelper(currEdge->adjGraphNode);
        }
        depthFirstSearchRecursive(currEdge->nextEdge);
    }
}  