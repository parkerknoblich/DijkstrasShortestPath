//#include <iostream>
//#include <fstream>
//#include "graphm.h"
//#include "graphl.h"
//using namespace std;
//
//int main() { 
//
//    // part 1
//    ifstream infile1("data31.txt");
//    if (!infile1) {
//        cout << "File could not be opened." << endl;
//        return 1;
//    }
//    for (;;) { 
//        GraphM G;
//        G.buildGraph(infile1);
//        if (infile1.eof()) {
//            break;
//        }
//        G.findShortestPath();
//        G.displayAll();
//        G.display(3, 1);
//        G.display(1, 2);
//        G.display(1, 4);
//    }
//
//    // part 2
//    ifstream infile2("data32.txt");
//    if (!infile2) {
//        cout << "File could not be opened." << endl;
//    }
//    for (;;) {
//        GraphL G;
//        G.buildGraph(infile2);
//        if (infile2.eof()) {
//            break;
//        }
//        G.displayGraph();
//        G.depthFirstSearch();
//    }
//    cout << endl;
//    return 0;
//}
