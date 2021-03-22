#ifndef NODEDATA_H
#define NODEDATA_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class NodeData {   

    // overloaded<<: prints the data of a node
    friend ostream& operator<<(ostream&, const NodeData&);

public:

    // default constructor 
    NodeData();

    // destructor
    ~NodeData();

    // parameterized constructor
    NodeData(const string&);

    // copy constructor
    NodeData(const NodeData&);

    // assigns one nodedata equal to another nodedata
    NodeData& operator=(const NodeData&);

    // set class data from data file and returns if successful or not
    bool setData(istream&);

    // checks if two nodedatas are equal
    bool operator==(const NodeData&) const;

    // checks if two nodedatas are not equal
    bool operator!=(const NodeData&) const;

    // checks if this nodedata is less than another nodedata
    bool operator<(const NodeData&) const;

    // checks if this nodedata is greater than another nodedata
    bool operator>(const NodeData&) const;

    // checks if this nodedata is less than or equal to another nodedata
    bool operator<=(const NodeData&) const;

    // checks if this nodedata is greater than or equal to another nodedata
    bool operator>=(const NodeData&) const;

private:

    // the data of a node
    string data;
};
#endif