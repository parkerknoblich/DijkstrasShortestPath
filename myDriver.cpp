#include <iostream>
#include <fstream>
#include "graphm.h"
#include "graphl.h"
using namespace std;

int main() {

    // part 1
    ifstream infile1("data31.txt");
    if (!infile1) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    for (;;) {
        GraphM G;
        G.buildGraph(infile1);
        if (infile1.eof()) {
            break;
        }
        G.findShortestPath();
        G.displayAll();
        for (int i = 1; i < 6; i++) {
            for (int j = 1; j < 6; j++) {
                G.display(i, j);
            }
        }
        G.removeEdge(1, 5);
        G.display(1, 5);
        G.insertEdge(2, 3, 30);
        G.display(2, 3);
    }

    // part 2
    ifstream infile2("data32.txt");
    if (!infile2) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    for (;;) {
        GraphL G;
        G.buildGraph(infile2);
        if (infile2.eof()) {
            break;
        }
        G.displayGraph();
        G.depthFirstSearch();
    }
    cout << endl;
    return 0;
}